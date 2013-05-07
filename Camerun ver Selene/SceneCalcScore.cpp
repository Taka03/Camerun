//*============================================================================
//SceneCalcScore.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneCalcScore.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneCalcScore::CSceneCalcScore( )
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneCalcScore::~CSceneCalcScore(void)
{
	//SAFE_DELETE( pScene );
}

////=============================================================================
////距離スコアの計算
////=============================================================================
//Sint32 CSceneCalcScore::CalcDistScore()
//{
//	int Score = 0;
//	
//	
//	return Score;
//		
//}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneCalcScore::Exec( CScene *pScene )
{
	CSprite *objBack	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("CalcScore") );
	
	CSprite *pPin = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pin") );
	
	CSprite *objNote	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Note") );
	
	CSprite *objSprClear	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("GameClear") );
	
	CSprite *objSprFail	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("GameFailure") );
	
	CMenu *objMenu = dynamic_cast<CMenu *>( pScene->GetGameObject()->FindObjectFromName("PopMenu") );
	
	objMenu->SetVisibleFlag( false );
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{
		objBack->SetVisibleFlag( true );
		
		pPin->SetVisibleFlag( true );
		
		objNote->SetVisibleFlag( true );
	}
	
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );
	
	int PhotoIndex = pMission->GetPhotoIndex();
	
	char Temp[20] = "";
	
	sprintf( Temp, "Photo%d", PhotoIndex );
	
	CPhoto *pSelectPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(Temp) );
	
	pRender->Begin();
	
	objBack->Rendering();
		
	if( pSelectPhoto != NULL )
	{	
		pSelectPhoto->Rendering();
	}
	
	objNote->Rendering();
	
	pPin->Rendering();
	
	//---------------------------------------------------------------------------
	//カメラ評価
	//---------------------------------------------------------------------------
	int TotalScore = 0;//合計スコア
	int ExistScore = 0;//ターゲット存在スコア
	int DistScore = 0;//大きさスコア
	int PosScore = 0;//位置スコア
	int TimeScore = 0;
	
	/*ターゲットが存在していたら、スコアを加算する*/
	if( pSelectPhoto->GetExistFlag() )
	{
		const int MAX_SCORE = 25;//各項目の最大得点
		
		ExistScore = MAX_SCORE;
		
		TotalScore += ExistScore;
		
		float fDistance = pSelectPhoto->GetTargetDistance();
		float fDistanceMin = pMission->GetMissionData().m_DistanceMin;
		float fDistanceMax = pMission->GetMissionData().m_DistanceMax;
		
		/*ターゲットの距離範囲によって、加算スコアを変える*/
		
		if( fDistance >= fDistanceMin && 
			fDistance <= fDistanceMax  )
		{
			float fDelta = fDistanceMax - fDistanceMin;
			
			if( fDistance >= fDistanceMin && fDistance <= fDistanceMin + fDelta / 3 )	
			{
				DistScore = MAX_SCORE;
			}
			
			else if( fDistance > fDistanceMin + fDelta / 3 && fDistance <= fDistanceMin + (2 * fDelta) / 3)
			{
				DistScore = MAX_SCORE - 10;
			}
			
			else if( fDistance > fDistanceMin + (2 * fDelta) / 3  && fDistance <= fDistanceMax )
			{
				DistScore = MAX_SCORE - 5;
			}
			
		}
		
		else
		{
			DistScore = 0;
		}
		
		
		TotalScore += DistScore;
		
		/*ターゲットの位置によって、加算スコアを変える*/
		Math::Vector3D vPos = pSelectPhoto->GetTargetPosition();
		
		float MinPos = pMission->GetMissionData().m_TargetPosMin;
		float MaxPos = pMission->GetMissionData().m_TargetPosMax;
		float DeltaPos = pMission->GetMissionData().m_TargetPosMax - pMission->GetMissionData().m_TargetPosMin;
		
		/*左寄り*/
		if( ( vPos.x >  MinPos && vPos.x <= MinPos + DeltaPos / 3 )  ) 
		{
			PosScore = 15;
		}
		
		/*真ん中*/
		else if( vPos.x > MinPos + DeltaPos / 3 && vPos.x <= MinPos + ( 2 * DeltaPos  / 3 ) )
		{	
			PosScore = 25;
		}
		
		else if( vPos.x > MinPos + (2 * DeltaPos / 3) && vPos.x <= MaxPos )
		{
			PosScore = 15;
		}
		
		else if( vPos.x < MinPos -0.5 || vPos.x > MaxPos + 0.5 )
		{
			PosScore = 0;
		}
		
		TotalScore += PosScore;
		
	}
	
	/*クリア時間を仮に加算する*/
	Sint32 ClearTime = pScene->GetClearTime().Min * 100 + pScene->GetClearTime().Sec;
	Sint32 TimeBorder = pMission->GetTimeBorder().Min * 100 + pMission->GetTimeBorder().Sec;
	
	TimeScore = 25;
	
	/*時間によって、スコアを変える*/
	if( ClearTime <= TimeBorder )
	{
		TimeScore = 25;
	}
	
	else
	{
		int MinusScore = 0;//減点スコア
		
		/*20秒毎に5点減点*/
		if( ClearTime >= TimeBorder + 20 )
		{
			MinusScore = 5;
		}
		
		else if( ClearTime >= TimeBorder + 40 )
		{
			MinusScore = 10;
		}
		
		else if( ClearTime >= TimeBorder + 60 )
		{
			MinusScore = 15;
		}

		else if( ClearTime >= TimeBorder + 80 )
		{
			MinusScore = 20;
		}

		else if( ClearTime >= TimeBorder + 100 )
		{
			MinusScore = 25;
		}
		
		TimeScore -= MinusScore;
			
	}
	
	TotalScore += TimeScore;
	
	
	//---------------------------------------------------------------------------
	//スコア表示
	//---------------------------------------------------------------------------
	
	
	static int count = 0;
	
	count++;
	
	pRender->SetDrawTextFont("MS ゴシック", 30 );
	
	
	pRender->DrawText( Math::Point2DI(350, 220),  CColor( 13, 167, 217 ), pMission->GetMissionName().c_str() );
	
	pRender->SetDrawTextFont("MS ゴシック", 40 );
	
	
	if( count > 60 )
	{	
		pRender->DrawText( Math::Point2DI(531, 275), CColor(194, 194, 194), "%d", ExistScore );
	}
		
	if( count > 110 )
	{	
		pRender->DrawText( Math::Point2DI(531, 335), CColor(194, 194, 194), "%d", DistScore );
	}
	
	if( count > 150 )
	{	
		pRender->DrawText( Math::Point2DI(531, 393), CColor(194, 194, 194), "%d", PosScore );
	}
	
	if( count > 190 )
	{	
		pRender->DrawText( Math::Point2DI(531, 458), CColor(194, 194, 194), "%d", TimeScore );
	}
	
	pRender->SetDrawTextFont("MS ゴシック", 50 );
	
	if( count > 312 )
	{	
		pRender->DrawText( Math::Point2DI(531, 515), CColor(245, 152, 157), "%d", TotalScore );
	}
	
	if( count < 312 )
	{
		CSoundEffect *DrumRoll = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("DrumRoll") );
		
		DrumRoll->GetSEDevice()->Play( 0 );
	}
	
	static bool IsPlayEnd = false;//音の再生が終わったかどうか
	
	static bool IsFade = false;
	
	static bool IsRetry = false;//リトライかどうか
	
	static Sint32 Cursor = 0;
	
	if( count > 400 )
	{
		/*一定得点以上ならばゲームクリア*/
		if( TotalScore >= pMission->GetClearPoint() )
		{
			
			CSoundEffect *pSndMissionClear = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("MissionClear") );
			
			if( !IsPlayEnd )
			{	
				pSndMissionClear->GetSEDevice()->Play( 0 );
				
				IsPlayEnd = true;
			}
			
			objSprClear->Rendering();
			
			objSprClear->SetVisibleFlag( true );
			pMission->SetGameClearFlag( true );
			
			if( count > 550 )
			{
				IsFade = true;
			}
			
			
		}
		
		else
		{
			CSoundEffect *pSndMissionFail = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("MissionFail") );
			
			if( !IsPlayEnd )
			{	
				pSndMissionFail->GetSEDevice()->Play( 0 );
				
				IsPlayEnd = true;
			}
			
			pScene->GetJoyPad()->GetController()->CursorClampUpDown( 0, Cursor, 2 );
			
			objSprFail->Rendering();
		
			objSprFail->SetVisibleFlag( true );
			
			if( count > 520 )
			{
				const int ITEM_MAX = 2;
				
				pRender->SetDrawType( DRAW_TYPE_BLEND );
				
				pRender->FillRect( Math::Rect2DF( 200, 300, 400, 250 ), CColor( 0, 0, 0, 128 ) ); 
				
				for( int i = 0;i < ITEM_MAX;++i )
				{
					if( Cursor == i )
					{	
						pRender->FillRect( Math::Rect2DF( 220 , toF( 360 + i * 100 ), 380, 60 ), CColor( 255, 255, 255, 128 ) );
					}
				}
				
				
				pRender->SetDrawType( DRAW_TYPE_NORMAL );
				
				pRender->DrawTextA( Math::Point2DI( 250, 310 ), CColor( 255, 255, 255 ), "リトライする?" );
				
				const char *pItemName[] =
				{
					"はい",
					"いいえ",
				};
				
				
				for( int i = 0;i < ITEM_MAX;++i )
				{	
					pRender->DrawTextA( Math::Point2DI( 220 , 360 + i * 100 ), CColor( 255, 255, 255 ), pItemName[i] );
				}
				
				if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
				{
					if( Cursor == 0 )
					{
						IsRetry = true;
					}
					
					else
					{
						IsFade = true;
					}
				}
			
			}
			
		}
		
	}
	
	/*初期プレイフラグを倒す*/
	pMission->SetFirstPlayFlag( false );
	
	/*ハイスコアの設定*/
	if( TotalScore > pMission->GetHiScore() )
	{
		pMission->SetHiScore( TotalScore );
	}
	
	
	#if defined( DEBUG ) | (_DEBUG )
	
		pRender->SetDrawTextFont("TT-JTCウインZ10", 10 );
		
		//pRender->DebugPrint( Math::Point2DI( 0, 450 ), CColor( 255, 255, 255 ), "fDistance:%f", pPhoto->GetTargetDistance() );
		pRender->DebugPrint( Math::Point2DI( 0, 480 ), CColor( 255, 255, 255 ), "Score:%d", TotalScore );
		
	#endif
	
	pSelectPhoto->GetSprite()->Begin();
	
	pSelectPhoto->GetSprite()->DrawSquare( Math::Rect2DF( toF( 30 ), toF( 70 ), 
													toF( pScene->GetAppDevice()->GetScreenWidth()/2 ), toF( pScene->GetAppDevice()->GetScreenHeight()/2 ) ),
									 Math::Rect2DF( 0, 0, toF( pSelectPhoto->GetTexture()->GetOriginalSize().x ), toF( pSelectPhoto->GetTexture()->GetOriginalSize().y ) ),
									 CColor( 255, 255, 255 ) );
	
	pSelectPhoto->GetSprite()->End();
	
	pRender->End();
	
	objSprClear->Exec();
	
	objSprFail->Exec();
	
	
	Math::Point2DF Pos[] =
	{
		Math::Point2DF( 536, 189 ),
		Math::Point2DF( 229, 64 ),
	};
	
	Math::Point2DF Anim[] =
	{
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 1, 0 ),
	};
	
	/*複数画像の描画*/
	pPin->DrawMultiGraph( Pos, Anim, 2 );
											
	static Sint32 Alpha	= 0;
	
	static Sint32 Alphacount = 0;
	
	
	if( IsFade )
	{
		Alphacount++;
		
		Alpha = Interpolation::Flat(0, 255, toI(60), Alphacount );

		pRender->SetDrawType( DRAW_TYPE_BLEND );
		
		pRender->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ), toF( pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
		
		//pRender->
		
		if( Alpha >= 255 )
		{
			pPin->SetVisibleFlag( false );
			
			objBack->SetVisibleFlag( false );
				
			objNote->SetVisibleFlag( false );
			
			objSprClear->SetVisibleFlag( false );
			objSprFail->SetVisibleFlag( false );
			
			CSprite *objReady = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Ready") );
			
			objReady->SetVisibleFlag( true );
			
			IsPlayEnd = false;
			
			
			IsFade = false;
			Alpha = 0;
			Alphacount = 0;
			count = 0;
			Cursor = 0;
			
			//if( pScene->GetMissionMgr()->GetMissionNo() == 4 )
			//{	
			//	if( pMission->GetGameClearFlag() )
			//	{
			//		pScene->SetNextScene( SCENE_ENDING );
			//	}
			//}
			//
			//else
			//{
				pScene->SetNextScene( SCENE_MISSIONSELECT );
			//}
			
			pScene->SetSceneState( STATE_STANDBY );
			
			pScene->ChangeScene( SCENE_INIT );
			
			for( int i = 0;i < pMission->GetFilmNum(); ++i )
			{
				char Temp[10] = "";
				
				sprintf( Temp, "Photo%d", i+1 );
				
				string strTemp;
				
				strTemp += Temp;
				
				CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
				
				pScene->Get2DObject()->RemoveObject( pPhoto );
			}
			
			
			//pScene->Get2DObject()->RemoveObject( pTitle );
		}
		
	}
	
	if( IsRetry )
	{
		Alphacount++;
		
		Alpha = Interpolation::Flat(0, 255, toI(60), Alphacount);

		pRender->SetDrawType( DRAW_TYPE_BLEND );
		
		pRender->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ), toF( pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
		
		
		if( Alpha >= 255 )
		{
			pPin->SetVisibleFlag( false );
			
			objBack->SetVisibleFlag( false );
				
			objNote->SetVisibleFlag( false );
			
			objSprClear->SetVisibleFlag( false );
			objSprFail->SetVisibleFlag( false );
			
			CSprite *objReady = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Ready") );
			
			objReady->SetVisibleFlag( true );
			
			pScene->Get3DObject()->Init();
			
			CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
			
			CCharacter *objFlag = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
			
			objFlag->SetVisibleFlag( false );
			
			objCamMain->Init();
			
			tagTime Time;
			
			pScene->SetCurrentTime( Time );
			
			pScene->SetNextScene( SCENE_DEMO );
			
			//pScene->SetSceneState( STATE_STANDBY );
			
			//pScene->ChangeScene( SCENE_DEMO );
			
			pScene->SetFadeTime( 30.0f );
			
			
				
			pScene->SetSceneState( STATE_FADEOUT );
			
			pScene->SetFontSize( 15 );			
			
			//pScene->SetNextScene( SCENE_DEMO );
			
			IsPlayEnd = false;
			IsRetry = false;
			
			Alpha = 0;
			Alphacount = 0;
			
			count = 0;
			Cursor = 0;
			
			pScene->SetNextScene( SCENE_DEMO );
			
			pScene->SetSceneState( STATE_STANDBY );
			
			pScene->ChangeScene( SCENE_DEMO );
			
			
			for( int i = 0;i < pMission->GetFilmNum(); ++i )
			{
				char Temp[10] = "";
				
				sprintf( Temp, "Photo%d", i+1 );
				
				string strTemp;
				
				strTemp += Temp;
				
				CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
				
				pScene->Get2DObject()->RemoveObject( pPhoto );
			}
			
			pScene->SetFilmCount( 0 );
		}
		
		
		//pScene->SetNextScene( SCENE_MISSIONSELECT );
		
	
	}
	//
	//
	//if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_06 ) )
	//{
	//	IsSelectedPic = !IsSelectedPic;
	//}
	//
	//if( !IsSelectedPic )
	//{
	//	eInputButtonType eButtonLeftRight = pScene->GetJoyPad()->GetController()->CursorRepeatLeftRight( 0, Cursor.x, 2 );
	//	
	//	eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor.y, pMission->GetFilmNum() / 2 );
	//}
	//
	//PhotoIndex = Cursor.x + Cursor.y * 2 ;
	//
}

