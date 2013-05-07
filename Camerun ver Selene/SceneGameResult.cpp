//*============================================================================
//SceneGameResult.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameResult.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneGameResult::CSceneGameResult( )
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameResult::~CSceneGameResult(void)
{
	//SAFE_DELETE( pScene );
}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneGameResult::Exec( CScene *pScene )
{
	static bool IsSelectedPic = false;//写真が選択されているかどうか
	
	static int PhotoIndex = 0;//写真のインデックス
	
	static Math::Point2DI Cursor(0, 0);
	
	CSprite *objResult	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Result") );
	
	objResult->SetVisibleFlag( true );
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission(pScene->GetMissionMgr()->GetMissionNo() );
	
	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("GameBGM") );
	
	pGameMusic->GetBGMDevice()->Stop();
	
	CSoundEffect *pSndDecide = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Decide") );
	CSoundEffect *pSndSelect = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Select") );
	
	CSoundEffect *sndTrain	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("STrain") );
	CSoundEffect *sndSetFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Flag") );
	CSoundEffect *sndRecallFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("RecallFlag") );
	
	CSoundEffect *sndMouse = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Mouse") );
	CSoundEffect *sndBird = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Bird") );
	
	sndMouse->GetSEDevice()->Stop( 0 );
	sndBird->GetSEDevice()->Stop( 0 );
	sndTrain->GetSEDevice()->Stop( 0 );
	
	CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ExplainFont") );
	
	CMenu *objMenu = dynamic_cast<CMenu *>( pScene->GetGameObject()->FindObjectFromName("PopMenu") );
	
	objMenu->SetPopUp( false );
	
	vector< string > vecText;
	
	#if defined(NDEBUG)
	
		//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI( 0, 10 ), CColor( 0, 0, 0 ), "Visible:%d", objPopMenu->GetVisibleFlag() );
		
	
	#endif
	
	
	if( !IsSelectedPic )
	{
		/*画面のクリア*/
		pScene->GetAppDevice()->GetRenderer()->Clear();
		
		/*描画開始*/
		pScene->GetAppDevice()->GetRenderer()->Begin();
	
		Math::Point2DF vExpPos[] =
		{
			Math::Point2DF( 550, 0 ),
		};
		
		vecText.push_back( "R2 写真" );
		
		//pExpFont->SetVecTextChat( vecText );
		
		objResult->Rendering();
		
		//pExpFont->Rendering();
		
		objResult->Exec();
		
		const Sint32 PHOTO_SIZE_X = 120;
		const Sint32 PHOTO_SIZE_Y = 90;
		
		Math::Point2DF vPos[] =
		{
			Math::Point2DF( 70, 100 ),
			Math::Point2DF( 70, 200 ),
			Math::Point2DF( 70, 300 ),
			Math::Point2DF( 70, 400 ),
			Math::Point2DF( 70, 500 ),
			Math::Point2DF( 270, 100 ),
			Math::Point2DF( 270, 200 ),
			Math::Point2DF( 270, 300 ),
			Math::Point2DF( 270, 400 ),
			Math::Point2DF( 270, 500 ),
			
		};
		
		pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( toF( vPos[Cursor.y].x - 5  ), toF( vPos[Cursor.y].y - 5  ), PHOTO_SIZE_X + 10, PHOTO_SIZE_Y + 10),
												  CColor(255, 255, 255) );
												  
		pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
		
		
		for( int i = 0;i < pScene->GetFilmCount(); ++i )
		{
			
			char Temp[256] = "";
			
			sprintf( Temp, "Photo%d", i+1 );
			
			string strTemp;
			
			strTemp += Temp;
			
			CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
			
			//pScene->GetAppDevice()->GetRenderer()->( Math::Rect2DF( Cursor.x * ( PHOTO_SIZE_X + 30) + 50, ( Cursor.y + 1 ) * 200, 130, 110 ), CColor(255, 255, 255) );
			pPhoto->Rendering();

			
			pPhoto->GetSprite()->Begin();
			
			
			pPhoto->GetSprite()->DrawSquare( Math::Rect2DF( vPos[i].x, vPos[i].y, toF( PHOTO_SIZE_X ), toF( PHOTO_SIZE_Y ) ),
											 Math::Rect2DF( 0, 0, toF( pPhoto->GetTexture()->GetOriginalSize().x ), toF( pPhoto->GetTexture()->GetOriginalSize().y ) ),
											 CColor(255, 255, 255) );
			
			pPhoto->GetSprite()->End();
			
			
			
			

		}
		
		/*描画終了*/
		pScene->GetAppDevice()->GetRenderer()->End();
	
	
		//pExpFont->DrawMultiLine( vExpPos );
		
		
		
	}
	
	else
	{
		Math::Point2DF vExpPos[] =
		{
			Math::Point2DF( 550, 0 ),
			Math::Point2DF( 550, 20 ),
		};
		
		//vecText.push_back( "△ 写真選択画面に戻る" );
		
		//pExpFont->SetVecTextChat( vecText );
		
		
		/*画面のクリア*/
		pScene->GetAppDevice()->GetRenderer()->Clear( CColor( 255, 255, 255, 128 ) );
		
		/*描画開始*/
		pScene->GetAppDevice()->GetRenderer()->Begin();
		
		
		char Temp[256] = "";
		
		sprintf( Temp, "Photo%d", PhotoIndex+1 );
		
		string strTemp;
		
		strTemp += Temp;
				
		CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
		
		pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
		
		pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, 800, 600 ), CColor( 0, 0, 0, 180 ) );
		
		pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
		
		pPhoto->Rendering();
		
		//pExpFont->Rendering();
		
		//objPopMenu->Rendering();
		//
		//objMenu->Rendering();
		
		//pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 200, 500, 200, 200 ), CColor( 255, 255, 255 ) );
		
		
		#if defined( DEBUG ) || (_DEBUG )
		
			Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
			
//			pRender->DebugPrint( Math::Point2DI( 0, 450 ), CColor( 255, 255, 255 ), "fDistance:%f", pPhoto->GetTargetDistance() );
//			pRender->DebugPrint( Math::Point2DI( 0, 480 ), CColor( 255, 255, 255 ), "Score:%d", Score );
			
		#endif
		
		
		
		//pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_ADD );
		
		//pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, pScene->GetAppDevice()->GetScreenWidth(), pScene->GetAppDevice()->GetScreenHeight() ), CColor(0, 0, 0, 50) );
		
		pPhoto->GetSprite()->Begin();
		
		pPhoto->GetSprite()->DrawSquare( Math::Rect2DF( toF( 200 ), toF( 150 ), 
														toF( pScene->GetAppDevice()->GetScreenWidth()/2 ), toF( pScene->GetAppDevice()->GetScreenHeight()/2 ) ),
										 Math::Rect2DF( 0, 0, toF( pPhoto->GetTexture()->GetOriginalSize().x ), toF( pPhoto->GetTexture()->GetOriginalSize().y ) ),
										 CColor( 255, 255, 255 ) );
		
		pPhoto->GetSprite()->End();
		
		/*描画終了*/
		pScene->GetAppDevice()->GetRenderer()->End();
		
		//pExpFont->DrawMultiLine( vExpPos );
		
		
		
		
	}	
	
				
	static Sint32 Alpha	= 0;
	
	static Sint32 Alphacount = 0;
	
	static bool IsFade = false;
	
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
	{
		pMission->SetPhotoIndex( PhotoIndex + 1 );
		IsFade = true;		
	}
	
	if( IsFade )
	{
		Alphacount++;
		
		Alpha = Interpolation::Flat( 0, 255, toI(60), Alphacount );

		pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
		
		pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ), toF( pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
		
		if( Alpha >= 255 )
		{
			objResult->SetVisibleFlag( false );
			
			IsFade = false;
			Alpha = 0;
			Alphacount = 0;
			
			/*フィルムカウンタのセット*/
			pScene->SetFilmCount( 0 );
	
			Cursor.x = 0;
			Cursor.y = 0;
			
			IsSelectedPic = false;
			
			pScene->SetSceneState( STATE_STANDBY );
			
			pScene->ChangeScene( SCENE_CALCSCORE );
			
			//pScene->Get2DObject()->RemoveObject( pTitle );
		}
		
	}
	
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_TRIANGLE) )
	{
		IsSelectedPic = !IsSelectedPic;
		
		vecText.clear();
		
		//pExpFont->SetVecTextChat( vecText );
		
		CSoundEffect *sndChange	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Change") );
		
		sndChange->GetSEDevice()->Play( 0 );
	
	}
	
	//if( IsSelectedPic )
	//{
	//	static int count = 0;
	//	
	//	if(++count > 60 )
	//	{
	//		count = 0;
	//		objMenu->SetPopUp( true );
	//		
	//	}
	//}
	//
	//if( objMenu->GetPopUpFlag() )
	//{	
	//	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
	//	{
	//		IsFade = true;
	//	}	
	//	
	//}
	
	if( !IsSelectedPic )
	{
		eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor.y, pScene->GetFilmCount() );
		
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, eButtonUpDown ) )
		{
			pSndSelect->GetSEDevice()->Play( 0 );
		}
	}
	
	//objPopMenu->Exec();
	
	//objMenu->Exec();
	
	
		
	//PhotoIndex = Cursor.x + Cursor.y * 2 ;
	PhotoIndex = Cursor.y;
	
}

