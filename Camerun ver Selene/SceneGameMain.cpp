//*============================================================================
//SceneGameMain.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameMain.h"
#include "MissionTutorial.h"
#include "ScenePhoto.h"
#include "EnemyAmeus.h"
#include "EnemyMouse.h"
#include "EnemyBird.h"
#include "EnemyManta.h"
#include <math.h>
#include <iostream>
#include <fstream>


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneGameMain::CSceneGameMain( )
{
	m_vOldPos.Set( 0, 0, 0 );
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameMain::~CSceneGameMain(void)
{
	//SAFE_DELETE( pScene );
}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneGameMain::Exec( CScene *pScene )
{
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );//CMissionTutorial( dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ) );
	
	CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
	CCamera *objCamSub  = dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamSub") );
	
	CField *objField = dynamic_cast<CField *>( pScene->Get3DObject()->FindObjectFromName("Field") );
	
	CPlayer *objPlayer = dynamic_cast<CPlayer *>( pScene->Get3DObject()->FindObjectFromName("Player") );
	CTrain *objTrain = dynamic_cast<CTrain *>( pScene->Get3DObject()->FindObjectFromName("Train") );
	
	CSoundEffect *sndTrain	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("STrain") );
	CSoundEffect *sndSetFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Flag") );
	CSoundEffect *sndRecallFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("RecallFlag") );

	//CFontSprite *pMissionFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("MissionFont") );
	CFontSprite *pCommonFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("CommonFont") );
	
	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("GameBGM") );
	
	CCharacter *objTarget	= dynamic_cast<CCharacter *>( pMission->GetTarget() );//dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") );
	
	CMenu *objPopMenu = dynamic_cast<CMenu *>( pScene->GetGameObject()->FindObjectFromName("PopMenu") );
	
	CSprite *objMenu = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("PopMenu") );
	
	CCharacter *pObjTargetArrow = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Target") );
	
	//CSprite3D *objBillBoard = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("BillBoard") );
	
	CMiniMap *objMiniMap = dynamic_cast<CMiniMap *>( pScene->Get2DObject()->FindObjectFromName("MiniMap") );
	
	CSprite *objMiniPlayer = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Mini_Player") );
	CSprite *objMiniCamera = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Mini_Camera") );
	CSprite *objMiniTarget = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Mini_Target") );
	
	CSprite3D *objFlagBal = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("FlagBalloon") );
	
	//エモーションバルーン	
	CSprite3D *objEmotion = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("Emotion") );
	
	CCharacter *objArrow = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Arrow") );
	
	CCharacter *objStar = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Star") );
	
	objStar->SetScale( Math::Vector3D( 0.5, 0.5, 0.5 ) );
	
	CParticle *objRunEffect[RUN_EFFECT_NUM];
	
	CFlash *objEmission[FLASH_EFFECT_NUM];
	
	CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ExplainFont") );
	
	CSprite *objNoFilm = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("NoFilm") );
	
	for( int i = 0;i < RUN_EFFECT_NUM;++i )
	{	
		char Temp[12];
		
		sprintf( Temp, "RunEffect%d", i);
		
		objRunEffect[i] = dynamic_cast<CParticle *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	
	for( int i = 0;i < FLASH_EFFECT_NUM;++i )
	{	
		char Temp[10];
		
		sprintf( Temp, "Emission%d", i);
		
		objEmission[i] = dynamic_cast<CFlash *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	
	objPopMenu->SetRenderer( pScene->GetAppDevice()->GetRenderer() );
	
	for	( int i = 0;i < RUN_EFFECT_NUM;++i )
	{
		objRunEffect[i]->SetRenderDevice( pScene->GetAppDevice()->GetRenderer() );
	}
	
	for( int i = 0;i < FLASH_EFFECT_NUM;++i )
	{
		objEmission[i]->SetRenderDevice( pScene->GetAppDevice()->GetRenderer() );
	}
	
	objMiniMap->SetRenderer( pScene->GetAppDevice()->GetRenderer() );
	
	static bool IsNoFlag = false;
	
	
	
	//pMissionFont->SetDrawString( pMission->GetMissionName() );
	
	//Sound::SPlayBlock Tbl[] =
	//{
	//	{
	//		1,
	//		Sound::PLAY_TIME_AUTO,
	//		Sound::PLAY_TIME_AUTO,
	//	},
	//	
	//	{
	//		-1,
	//		4.0f,
	//		Sound::PLAY_TIME_AUTO,
	//	},
	//};
	
	#if defined (DEBUG) | (_DEBUG)	
		CDebugLine *pDebugLine = dynamic_cast<CDebugLine *>( pScene->Get3DObject()->FindObjectFromName("DebugLine") );
	#endif
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{	
		pGameMusic->GetBGMDevice()->Play( );
	}
	
		
	/*プレイヤー用にコントローラーデバイスを取得*/
	objPlayer->SetController( pScene->GetJoyPad()->GetController(), pScene->GetJoyPad()->GetJoyStick() );
	
	CCamObject *objCamObj = dynamic_cast<CCamObject *>( pScene->Get3DObject()->FindObjectFromName("CamObj") );
	CCharacter *objFlag	  = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
	
	/*利便性を考えて、プレイヤーに埋め込む*/
	objPlayer->GetCamObject( objCamObj );
	//objPlayer->GetFlagObject( objFlag );
	
	/*全キャラに対して当たり判定データを作成*/
	pScene->Get3DObject()->CreateCollision();
	
	//-------------------------------------------------------------------------
	//描画開始
	//-------------------------------------------------------------------------
	pScene->GetAppDevice()->GetRenderer()->Begin();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーンマネージャーの内容を実際にレンダリング
	/////////////////////////////////////////////////////////////////////////////////////////////
	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Rendering( false );
	
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->Rendering( false );
	
	int FilmNum = pMission->GetFilmNum() - pScene->GetFilmCount();//現在のフィルム枚数
	
	const int LINENUM = 6;//デバッグ用のライン数
	
	const int RAY_NUM = LINENUM - 1;//評価に使うラインの数
	
	Collision::CLine3D vGradeRay[RAY_NUM];//評価用ライン
	
	//-------------------------------------------------------------------------
	//写真撮影
	//-------------------------------------------------------------------------
							  
	const int CHECK_POINTNUM = 9;
						  
	Math::Vector2D CheckPointTbl[] =
	{
		Math::Vector2D(400, 300),
		Math::Vector2D(350, 300),
		Math::Vector2D(450, 300),
		Math::Vector2D(400, 250),
		Math::Vector2D(400, 350),
		Math::Vector2D(350, 250),
		Math::Vector2D(350, 350),
		Math::Vector2D(450, 250),
		Math::Vector2D(450, 350),
		
	};
	
	
	if( objPlayer->GetSetFlag() )
	{
		Math::Vector3D vFront(0, 0, 0);//カメラの正面
		
		objCamObj->GetModelActor(S_MAIN)->GetFront( vFront );
		
		const int MAX_DISTANCE = 10;//レイの最大距離
		
		Math::Vector3D vRight;
		
		objCamObj->GetModelActor(S_MAIN)->GetRight( vRight );
		
		Math::Vector3D vUp;
		
		objCamObj->GetModelActor(S_MAIN)->GetUp( vUp );
		
		vGradeRay[0].vStart = objCamObj->GetPosition() - vFront;
		vGradeRay[0].vEnd = objCamObj->GetPosition() - vFront * MAX_DISTANCE;

		for( int i = 1;i < RAY_NUM;++i )
		{
			vGradeRay[i].vStart = vGradeRay[0].vStart;
		}				
		
		//vGradeRay[1].vEnd = vGradeRay[0].vEnd + vRight * 5;//Math::Vector3D( (/*vFront.x */+ vRight.x), (vFront.y + vUp.y) / 2, 0 );
		//
		//vGradeRay[2].vEnd = vGradeRay[0].vEnd - vRight * 5;//Math::Vector3D( -(vFront.x + vRight.x), (vFront.y + vUp.y) / 2, 0 );

		//vGradeRay[3].vEnd = vGradeRay[0].vEnd + vUp * 5;//+ Math::Vector3D( (vFront.x + vRight.x), -(vFront.y + vUp.y) / 2, 0 );

		//vGradeRay[4].vEnd = vGradeRay[0].vEnd - vUp * 5;//+ Math::Vector3D( -(vFront.x + vRight.x), -(vFront.y + vUp.y), 0 );
	
		Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
		
		/*カメラ画面枠の描画*/
		pRender->SetDrawType( DRAW_TYPE_ADD );
		
		const float SUB_X = 545;
		const float SUB_Y = 400;
		
		pExpFont->SetPosition( Math::Vector3D( SUB_X, SUB_Y, 0 ) ); 
		
		pRender->FillRect( Math::Rect2DF( toF( SUB_X - 15 ), toF( SUB_Y - 15 ), 270, 210 ), CColor( 189, 140, 191, 128) );
		
		pRender->SetDrawType( DRAW_TYPE_NORMAL );
		
		/*カメラ画面の表示*/	
		if( FilmNum > 0 )
		{
			pRender->DrawTexture( Math::Rect2DF( toF( SUB_X ), toF( SUB_Y ), toF( 240 ), toF( 180 ) ),
								  CColor(255, 255, 255), 
								  Math::Rect2DF(0, 0, 
							 					toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().x ), 
							 					toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().y ) ),
								  pScene->GetSceneMgr(S_SUB)->GetRenderTex() );
								  
			
			objNoFilm->SetPosition( Math::Vector3D( SUB_X, SUB_Y, 0 ) ) ;
			
			objNoFilm->SetVisibleFlag( false );
								  
		}
		
		else
		{
			/*撮れなくなったらグレイスケールにする*/
			pRender->DrawGrayscale( Math::Rect2DF( toF( SUB_X ), toF( SUB_Y ), toF( 240 ), toF( 180 ) ),
								  CColor(255, 255, 255), 
								  Math::Rect2DF(0, 0, 
							 					toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().x ), 
							 					toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().y ) ),
								  pScene->GetSceneMgr(S_SUB)->GetRenderTex() );
								  
			
			objNoFilm->SetVisibleFlag( true );
								  
		}
											
											
		if( FilmNum > 0 && !objPopMenu->GetPopUpFlag() )
		{
			if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2) )
			{
				char Temp[256] = "";
				
				sprintf( Temp, "Photo%d", ( pMission->GetFilmNum() + 1 ) - FilmNum );
				
				string strTemp;
				
				strTemp += Temp;
				
				string name = "file";
				
				char Buff[256] = "";
				sprintf(Buff, "%d", pScene->GetFilmCount() );
				
				name += Buff; 
				name += ".tga";
				
				/*画面をフラッシュさせる*/
				pRender->FillRect( Math::Rect2DF( toF( SUB_X ), toF( SUB_Y ), 
												  toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().x ), 
												  toF( pScene->GetSceneMgr(S_SUB)->GetRenderTex()->GetOriginalSize().y ) ),
												  CColor(255, 255, 255) );
				
				/*写真を一時的に保存して、そのデータを読み込んですぐ破棄*/								
				pScene->GetSceneMgr(S_SUB)->GetRenderTex()->SaveToTGA( name.c_str() );
				
				CPhoto *tempSpr = new CPhoto( name, Math::Vector2D( 0, 0 ) );
				
				pScene->Get2DObject()->AppendObject( tempSpr, strTemp, true );
				
				tempSpr->Load( pRender );
				
				//tempSpr->SetVisibleFlag( true );
				
				#if defined( DEBUG ) | (_DEBUG )
				
				#elif (TEST_RELEASE)
				
				#else 	
					::DeleteFile( name.c_str() ); 
				#endif
				
				CSoundEffect *sndShutter	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Shutter") );
				
				/*シャッター音の再生*/
				sndShutter->GetSEDevice()->Play( 0 );
				
				/*フィルムカウンタの増加*/
				pScene->AddFilmCounter();
				
				//-------------------------------------------------------------------------
				//写真評価
				//-------------------------------------------------------------------------
				Renderer::SCollisionResult Ret;
				
				CDraw3DObject *pObjHit = NULL;//当たったオブジェクトの取得用
				
				pScene->SetPhotoIndex( pScene->GetFilmCount() );
				
				Math::Vector3D vDistance = objTarget->GetPosition() - objCamObj->GetPosition();
				
				
				for( int i = 0;i < CHECK_POINTNUM;++i )
				{
					if( objTarget->GetModelActor(S_MAIN)->Collision_CheckOnScreen( CheckPointTbl[i], pScene->GetSceneMgr(S_SUB)->GetSceneMgr() ) )
					{
						
						if( vDistance.Length() >= pMission->GetMissionData().m_DistanceMin &&
							vDistance.Length() <= pMission->GetMissionData().m_DistanceMax )
						{
							tempSpr->SetExistFlag( true );
							
							#if defined( NDEBUG )
								tempSpr->SetTargetDistance( vDistance.Length() );
								
								tempSpr->SetTargetPos( vDistance );
							#endif
							
							  
						}
							
					}
				}
				
				#if defined( TEST_RELEASE )
				
					tempSpr->SetTargetDistance( vDistance.Length() );
					
					tempSpr->SetTargetPos( vDistance );
				
				
				#endif

				
				pScene->SetSceneState( STATE_STANDBY );
				
				pScene->ChangeScene( SCENE_PHOTOSCREEN );
				
			}
		}
	
		/*既定枚数撮り終わったときの処理*/
		if( pScene->GetFilmCount() >= pMission->GetFilmNum() )
		{	
			
			//objPlayer->SetCameraModeFlag( false );
			
			FilmNum = 0;
		}
		
	
	}
	
	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	pScene->Get2DObject()->Rendering();
	
	objPopMenu->Rendering();
	
	if( IsNoFlag )
	{
		objMenu->Rendering();
		pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( objMenu->GetPosition().x + 10, objMenu->GetPosition().y + 20 ), CColor( 0, 0, 0 ), "カメラを持っていません" );
	}
	
	
	static bool IsModeVisible = false;
	
	if( objPlayer->GetSetFlag() )
	{
		if( !objPlayer->IsCameraMode() )
		{
			pExpFont->SetDrawString("移動モード");
		}
		
		else
		{
			pExpFont->SetDrawString("カメラモード");
			
		}
	}
	
	
	/*モード変更フォントの表示*/
	if( objPlayer->GetSetFlag() )
	{
		if( IsModeVisible )
		{
			pExpFont->SetFontColor( CColor( 255, 0, 0 ) );
			
			//static int count = 0;
			
			pExpFont->Rendering();
			
			if( pScene->GetAppDevice()->GetCore()->GetSyncCount() % 60 == 0 )
			{
				IsModeVisible = false;
			}
		}
	}
	
	
	
	//objMiniMap->Rendering();
	
	
//	pMissionFont->Rendering();
	
	CSprite *objPointa = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pointa") );
	
	objPointa->SetDivnum( Math::Point2DI( 2, 1 ) );
	
	for( int i = 0;i < CHECK_POINTNUM;++i )
	{
		if( objTarget->GetModelActor(S_MAIN)->Collision_CheckOnScreen( CheckPointTbl[i], pScene->GetSceneMgr(S_SUB)->GetSceneMgr() ) )
		{
			Math::Vector3D vDistance = objTarget->GetPosition() - objCamObj->GetPosition();
			
			
			//if( objField->GetMapActor(S_MAIN)->HitCheckByRay( vGradeRay[0] ) )
			//{
			//	objPointa->SetAnimID( Math::Point2DI( 0, 0 ));
			//}
			//
			//else
			//{
			if( vDistance.Length() >= pMission->GetMissionData().m_DistanceMin &&
				vDistance.Length() <= pMission->GetMissionData().m_DistanceMax )
			{
				objPointa->SetAnimID( Math::Point2DI( 1, 0 ));
			}
			//}
		}
		
		else
		{
			objPointa->SetAnimID( Math::Point2DI( 0, 0 ));
		}
	}
	
	objPointa->SetVisibleFlag( objPlayer->GetSetFlag() );
		
	CSprite *pCharaIcon = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("CharaIcon") );
	CSprite *pFlagIcon = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("FlagIcon") );
	
	//---------------------------------------------------------------------------
	//モード表示
	//---------------------------------------------------------------------------
	if( !objPlayer->IsCameraMode() )
	{
		pCharaIcon->SetVisibleFlag( true );
		pFlagIcon->SetVisibleFlag( false );
	}
	
	else
	{
		pCharaIcon->SetVisibleFlag( false );
		pFlagIcon->SetVisibleFlag( true );
	}
	
	//---------------------------------------------------------------------------
	//フィルムがなくなったときの処理
	//---------------------------------------------------------------------------
	if( FilmNum <= 0 )
	{
		if( objPlayer->IsCameraMode( ) )
		{
			objNoFilm->SetVisibleFlag( true );
		}
		
		else
		{
			objNoFilm->SetVisibleFlag( false );
		}
	
	}
	
	else
	{
		objNoFilm->SetVisibleFlag( false );
	}
			
	
	/*描画終了*/
	pScene->GetAppDevice()->GetRenderer()->End();
	
	Math::Vector3D vPlayerRight;
	
	objPlayer->GetModelActor(S_MAIN)->GetRight( vPlayerRight );
	
	objEmotion->SetPosition( objPlayer->GetPosition() - vPlayerRight + Math::Vector3D(0, 1.2f, 0 ) );
	
	if( objEmotion->GetVisibleFlag() )
	{
		pScene->AddVisibleCounter();
		
		if( pScene->GetVisibleCount() > 60 )
		{
			pScene->SetVisibleCount( 0 );
			objEmotion->SetVisibleFlag( false );
		}
	}
	
	
	char Temp[256] = "";
	
	sprintf( Temp, "×%d", FilmNum );
	
	char TempTime[20] = "";
	
	//pMissionFont->GetFontSprite()->Begin();
	//
	//pMissionFont->GetFontSprite()->DrawString( Temp, Math::Point2DI(260, 13), CColor(180, 180, 180) );
	//pMissionFont->GetFontSprite()->DrawString( "TIME", Math::Point2DI(710, 13), CColor(180, 180, 180) );
	//
	pScene->GetAppDevice()->GetRenderer()->DrawText( Math::Point2DI(260, 13), CColor(180, 180, 180), Temp );
	pScene->GetAppDevice()->GetRenderer()->DrawText( Math::Point2DI(720, 13), CColor(180, 180, 180), "TIME" );

	/*タイムカウンタの増加*/
	if( !objPopMenu->GetPopUpFlag() )
	{
		if( pScene->GetSceneState() == STATE_STANDBY )	
		{
			pScene->TimeCount();
		}
	}
	//
	sprintf( TempTime, "%2d:%2d:%2d", pScene->GetCountTime().Hour, pScene->GetCountTime().Min, pScene->GetCountTime().Sec );
	
	//pMissionFont->GetFontSprite()->DrawString( TempTime , Math::Point2DI(730, 30), CColor(180, 180, 180) );
	//pMissionFont->GetFontSprite()->DrawString( pMission->GetMissionName().c_str(), Math::Point2DI( 430, 13 ), CColor(180, 180, 180) );
	//
	pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI(730, 30), CColor(180, 180, 180), TempTime );
	
	/*ミッション名の描画*/
	pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 430, 13 ), CColor( 180, 180, 180 ), pMission->GetMissionName().c_str() );
	
	objMiniMap->SetMiniCharaPos( objPlayer, objMiniPlayer, true );
	objMiniMap->Move( objPlayer );
	
//	pMissionFont->Exec();
	
	objPopMenu->Exec();
	
	#if defined (DEBUG) | (_DEBUG)	
		
		pDebugLine->Exec();
	#endif
	
	Collision::CBox Box;
	
	Math::Matrix matWorld;
	
	Math::Matrix matTemp;
	
	matTemp.Identity();
	
	matWorld.Identity();
	
	matTemp.RotationY( toI(-objPlayer->GetRotate().x ) - DEG_TO_ANGLE( 90 ));
	//matTemp.RotationY( objFlag->GetRotate().x - DEG_TO_ANGLE( 90 ) ) ;
	
	matWorld *= matTemp;
	
	matTemp.Translation( objPlayer->GetPosition().x, objPlayer->GetPosition().y, objPlayer->GetPosition().z );
	//matTemp.Translation( objFlag->GetPosition().x, objFlag->GetPosition().y, objFlag->GetPosition().z );
	
	matWorld *= matTemp;
	
	Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
	
	CEnemyAmeus *objAmeus = dynamic_cast<CEnemyAmeus *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ); 
	
	CEnemyBird *objBird[BIRD_MAX];
	
	for( int i = 0;i < BIRD_MAX;++i )
	{	
		char Temp[20];
		
		sprintf( Temp, "Bird%d", i+1 );
		objBird[i]  = dynamic_cast<CEnemyBird *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	CEnemyMouse *objMouse[MOUSE_MAX];
	
	for( int i = 0;i < MOUSE_MAX;++i )
	{	
		char Temp[20];
		
		sprintf( Temp, "Mouse%d", i+1 );
		
		objMouse[i] = dynamic_cast<CEnemyMouse *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	
	CEnemyManta *objManta = dynamic_cast<CEnemyManta *>( pScene->Get3DObject()->FindObjectFromName("Manta") );
	
	CSoundEffect *sndMouse = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Mouse") );
	CSoundEffect *sndBird = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Bird") );
	
	objAmeus->GetCore( pScene->GetAppDevice()->GetCore() );
	
	//objAmeus->GetStunEffect( objStar );
	//objBird->GetStunEffect( objStar );
	//objBird2->GetStunEffect( objStar );
	//objBird3->GetStunEffect( objStar );
	//
	//
	///*幽霊を撮れのときのみアメウスを表示させる*/
	//if( pScene->GetMissionMgr()->GetMissionNo() == 1 )
	//{
	//	objAmeus->SetVisibleFlag( true );
	//}
	//
	//else
	//{
	//	objAmeus->SetVisibleFlag( false );
	//}
	//
	///*マンタを撮れのときのみマンタを表示させる*/
	//if( pScene->GetMissionMgr()->GetMissionNo() == 4 )
	//{
	//	objManta->SetVisibleFlag( true );
	//}
	//
	//else
	//{
	//	objManta->SetVisibleFlag( false );
	//}
	
	
	
	/*ミニキャラの最大*/
	const int CHARA_MAX = 11;
	
	/*ミニキャラの位置*/
	CCharacter *pMiniChara[] =
	{
		objFlag,
		objBird[0],
		objBird[1],
		objBird[2],
		objBird[3],
		objBird[4],
		objBird[5],
		objMouse[0],
		objMouse[1],
		objMouse[2],
		objTarget,
		
	};	
	
	/*ミニキャラのオブジェクト名*/
	const char *pMiniObjName[] =
	{
		"Mini_Camera",
		"Mini_Bird1",
		"Mini_Bird2",
		"Mini_Bird3",
		"Mini_Bird4",
		"Mini_Bird5",
		"Mini_Bird6",
		"Mini_Mouse1",
		"Mini_Mouse2",
		"Mini_Mouse3",
		"Mini_Target",
	};
		
	for( int i = 0;i < CHARA_MAX;++i )
	{	
		CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(pMiniObjName[i]) ); 
		
		objMiniMap->SetMiniCharaPos( pMiniChara[i], objMiniSpr, false );
		
	}
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{
		float fDistance = objPlayer->CheckDistance( objTrain );
		
		objTrain->PlaySnd( sndTrain->GetSEDevice(), fDistance );
		
		for( int i = 0;i < BIRD_MAX;++i )
		{
			fDistance = objPlayer->CheckDistance( objBird[i] );
			
			objBird[i]->PlaySnd( sndBird->GetSEDevice(), fDistance );
		}
		
		for( int i = 0;i < MOUSE_MAX;++i )
		{
			fDistance = objPlayer->CheckDistance( objMouse[i] );
				
			objMouse[i]->PlaySnd( sndMouse->GetSEDevice(), fDistance );
		
		}
		
	}
		
	Collision::CBox BoxAmeus;//アメウスの可視判定用
	
	Math::Matrix matAmeWorld;
	
	matAmeWorld.Identity();
	
	//matTemp.Perspective( DEG_TO_ANGLE(45), 0.01f, 50.0f, toF( 800 / 600 ) );
	//
	//matAmeWorld *= matTemp;
	
	matTemp.RotationY( toI( -objAmeus->GetRotate().x ) + DEG_TO_ANGLE(90) );
	
	matAmeWorld *= matTemp;
	
	matTemp.Translation( objAmeus->GetPosition().x, objAmeus->GetPosition().y, objAmeus->GetPosition().z );
	
	matAmeWorld *= matTemp;
	
	BoxAmeus.CreateBoxProjection( Math::Vector3D( -1, 0, -10 ), Math::Vector3D( 1, 2, 0 ), matAmeWorld );
	
	#if defined(DEBUG) | (_DEBUG)
				
				Math::Vector3D vFront(0, 0, 0);
				
				objCamObj->GetModelActor(S_MAIN)->GetFront( vFront );

				Math::Vector3D vRight;
				
				objCamObj->GetModelActor(S_MAIN)->GetRight( vRight );
				
				Math::Vector3D vUp;
				
				objCamObj->GetModelActor(S_MAIN)->GetUp( vUp );
				
				Selene::Renderer::SLineVertex3D Line[LINENUM + 3];
				
				Line[0].v1.Pos = objPlayer->GetRay().vStart;
				Line[0].v2.Pos = objPlayer->GetRay().vEnd;					
				Line[0].v1.Col = CColor(255, 255, 255 );
				Line[0].v2.Col = CColor(255, 255, 0 );
				
				for( int i = 0;i < RAY_NUM;++i )
				{
					Line[i+1].v1.Pos = vGradeRay[i].vStart;
					Line[i+1].v2.Pos = vGradeRay[i].vEnd;					
					Line[i+1].v1.Col = CColor(255, 128, 255 );
					Line[i+1].v2.Col = CColor(255, 0, 0 );
				}
				
				for( int i = 0;i < RAY_NUM;++i )
				{
					Renderer::SCollisionResult Ret;
					
					if( pScene->Get3DObject()->HitCheck( vGradeRay[i], Ret ) )
					{
							Line[5].v1.Pos = Ret.vTriangle[0];
							Line[5].v1.Col = CColor( 255, 255, 0 );
							Line[5].v2.Pos = Ret.vTriangle[1];
							Line[5].v2.Col = CColor( 255, 255, 0 );
							
							Line[6].v1.Pos = Ret.vTriangle[1];
							Line[6].v1.Col = CColor( 255, 255, 0 );
							Line[6].v2.Pos = Ret.vTriangle[2];
							Line[6].v2.Col = CColor( 255, 255, 0 );

							Line[7].v1.Pos = Ret.vTriangle[2];
							Line[7].v1.Col = CColor( 255, 255, 0 );
							Line[7].v2.Pos = Ret.vTriangle[0];
							Line[7].v2.Col = CColor( 255, 255, 0 );
					}
					
				}
				
				#if defined( DEBUG_MAP_EDIT )	
					Math::Vector3D vCharaFront;
					
					objPlayer->GetModelActor(S_MAIN)->GetFront( vCharaFront );			
					
					vCharaFront.Normalize();		
					
					Line[8].v1.Pos = objPlayer->GetPosition();
					Line[8].v2.Pos = objPlayer->GetPosition() + vCharaFront * 10;
					Line[8].v1.Col = CColor( 255, 0, 0 );
					Line[8].v2.Col = CColor( 255, 0, 0 );
					
				#endif
				
				pDebugLine->GetLine()->Begin();
												  
				pDebugLine->AddLine( Line, LINENUM+3 );
				
				pDebugLine->GetLine()->PushBox( Box, CColor( 255, 255, 255 ) );
				//
				pDebugLine->GetLine()->PushBox( BoxAmeus, CColor( 255, 255, 255 ) );
				
				//objField->GetMapActor(S_MAIN)->RenderingBounding( pDebugLine->GetLine() );
				//
				pDebugLine->GetLine()->End();

	#endif
	
	#if defined(NDEBUG) 
	
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 105), CColor(128,128,192), "Cam:x:%f y:%f z:%f", objCamObj->GetPosition().x, objCamObj->GetPosition().y, objCamObj->GetPosition().z );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 120), CColor(128,128,192), "Flag:x:%f y:%f z:%f", objFlag->GetPosition().x, objFlag->GetPosition().y, objFlag->GetPosition().z );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 150), CColor(128,128,192), "Flag:Visible:%d", objFlag->GetVisibleFlag() );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 180), CColor(128,128,192), "Flag:Visible2:%d", objPlayer->GetSetFlag() );
			
			
			
	#endif
		
	// 情報
//			pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5,20), CColor(128,128,192), "↑：前進" );
	#if defined(DEBUG) | (_DEBUG )
	
			//remove("debug.txt");
			
	
//			// レンダリングオブジェクト数
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5,5), CColor(128,128,192), "Render Count %3d/%3d", pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->GetResult_RenderingActorCount(), pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->GetResult_RenderingRequestActorCount() );
//			pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5,15), CColor(128,128,192), "Render Count %3d/%3d", pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->GetResult_RenderingActorCount(), pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->GetResult_RenderingRequestActorCount() );
//			
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(170,5), CColor(128,128,192), "QuadTree %3d/%3d", objBuilding->GetMapActor()->GetRenderingCellCount(), objBuilding->GetMapActor()->GetCellCount() );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 105), CColor(128,128,192), "Cam:x:%f y:%f z:%f", objCamObj->GetPosition().x, objCamObj->GetPosition().y, objCamObj->GetPosition().z );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 120), CColor(128,128,192), "Flag:x:%f y:%f z:%f", objFlag->GetPosition().x, objFlag->GetPosition().y, objFlag->GetPosition().z );
			pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 50), CColor( 255, 255, 255 ), "Player:x:%f y:%f z:%f Rot:%f", objPlayer->GetPosition().x, objPlayer->GetPosition().y, objPlayer->GetPosition().z, objPlayer->GetRotate().x );
			
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 90), CColor( 255, 255, 255 ), "Bird:x:%f y:%f z:%f", objBird->GetPosition().x, objBird->GetPosition().y, objBird->GetPosition().z );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 110), CColor( 255, 255, 255 ), "Mouse:x:%f y:%f z:%f", objMouse->GetPosition().x, objMouse->GetPosition().y, objMouse->GetPosition().z );
			//
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 70), CColor( 255, 255, 255 ), "Camera:x:%f y:%f z:%f", objCamMain->GetPosition().x, objCamMain->GetPosition().y, objCamMain->GetPosition().z);
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 130), CColor( 150, 255, 255 ), "Scroll:x:%f:y:%f", objMiniMap->GetScroll().x, objMiniMap->GetScroll().y );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 150), CColor( 150, 255, 255 ), "miniCamera:x:%f:y:%f", objMiniCamera->GetPosition().x, objMiniCamera->GetPosition().y );
			
			
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 25), CColor( 255, 255, 255 ), "Train:x:%f y:%f z:%f", objTrain->GetPosition().x, objTrain->GetPosition().y, objTrain->GetPosition().z );
			//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 75), CColor( 255, 255, 255 ), "Joy:%d", p );
			
			#if defined( DEBUG_MAP_EDIT )
			
				std::ofstream ofs( "debug.csv", std::ios::out | std::ios::app );
				
				if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R1 ) )
				{	
					static int count = 0;
					
					ofs << objPlayer->GetPosition().x << " " << objPlayer->GetPosition().y << " " << objPlayer->GetPosition().z << " " << objPlayer->GetRotate().x << std::endl;
					
					count ++;
					
					if( count < 60 )
					{
						pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI( 400, 300 ), CColor( 255, 0, 0 ), "座標を保存しました。" );
						
					}
					
					if( count > 60 )
					{
						count = 0;
					}
				}
			#endif
			
			//int MeshIndex = objTarget->GetModelActor(S_MAIN)->GetMeshCount();
			
//			for( int i = 0;i < MeshIndex; ++i )
//			{	
//				int MateIndex = objTarget->GetModelActor(S_MAIN)->GetMeshMaterialCount( i );
//				
//				for( int j = 0;j < MateIndex; ++j )
//				{			
//					objTarget->GetModelActor(S_MAIN)->MeshMaterial_SetSpecularColor( i, j, Math::Vector4D(0, 0, 0, 255 ) );
//				}
//			}
////			
//			pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 150), CColor(128, 128, 192), "AppTime:x:%d", pScene->GetAppDevice()->GetCore()->GetSyncCount() );
//			
//			pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 175), CColor(128, 128, 192), "FlashMode:x:%d", objPlayer->IsFlashMode() );
//	
		
		//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 15), CColor(255, 255, 255), "Player-Train:Distance:%f", fDistance );
		
		
	#endif
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーン情報構築
	/////////////////////////////////////////////////////////////////////////////////////////////


	//--------------------------------------------------------------------------
	//メイン画面
	//--------------------------------------------------------------------------
	// シーン情報リセット
	//   Scene::ISceneManagerインターフェイスを使ったシーン管理情報を初期化します。
		
	/*描画位置の設定*/
	pScene->GetSceneMgr(S_MAIN)->SetRenderPos( Math::Vector2D(0, 0) );
	
	/*パラメータの設定*/
	pScene->GetSceneMgr(S_MAIN)->SetParameter();
	
	//pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetParameter_HighDynamicRange( 0.5f, 0.5f );
	
	
	// 平行光源
	//   シーンに対して平行光源を設定します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Directional(
		Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ライトの方向
		Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ライトの色

	// アンビエント
	// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Ambient(
		Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// 天球の色
		Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// 地表の色
		
	//ソフトパーティクルのアルファ値のスケールを設定
	//pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetParameter_SoftParticleScale( 300 );
		
		
	//pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->		
	//pDynamicsWorld->Update( 1.0f / 60.0f, CollisionCallback );	
	
	// カメラの注視目標
	#if defined( DEBUG_MAP_SEE )
	
		ifstream ifs("target.txt");
		
		char TargetStr[20] = "";
		
		ifs >> TargetStr;
		
		CCharacter *CamTarget = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName(TargetStr) );
		
		
		objCamMain->SetTargetPos( CamTarget->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f ) );
		
		ifs.close();
	
	#else
	
		objCamMain->SetTargetPos( objPlayer->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f) );
	
	
	#endif

	/*トランスフォームの設定*/
	
	#if defined( DEBUG_MAP_SEE )
	
		if( objCamMain->GetTopViewFlag() )
		{	
			objCamMain->SetTransform3();
		}
		
		else
		{
			objCamMain->SetTransform();
		}
		
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_L1 ) )
		{
			objCamMain->SetTopViewFlag( !objCamMain->GetTopViewFlag() );
		}
		
	#elif defined( DEBUG_MAP_EDIT )
	
		objCamMain->SetTopViewFlag( true );
		
		if( objCamMain->GetTopViewFlag() )
		{	
			objCamMain->SetTransform3();
		}
		
		//else
		//{
		//	objCamMain->SetTransform();
		//}
		//
		//if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_L1 ) )
		//{
		//	objCamMain->SetTopViewFlag( !objCamMain->GetTopViewFlag() );
		//}
	
	
	
	#else
		
		objCamMain->SetTransform();
	#endif
	
	
	
	// シーンにシャドウマップ用カメラ設定t
	//   シャドウマップのレンダリングに使うカメラを設定
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetParameter_Shadow(
		Math::Vector3D( -3.0f, 20.0f, -30.0f ),	// カメラ位置
		Math::Vector3D( 0, 10.0, 0 ),
		//objPlayer->GetPosition(),									// カメラ注視点
		100.0f,								// レンダリングサイズ
		10.0f,								// 近クリップ面
		30.0f,								// 遠クリップ面
		0.0f,								// Z値バイアス（実際に見ていい感じに調整
		0.7f );								// 影の強さ（SHADING_NORMALの時のみ有効）
		
	// ハッチング用のパラメーター
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetParameter_Toon( Math::Vector3D(0.5, 0.5, 0.5 ), 0.1f );
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetParameter_ToonEdge( 3.0f, 10.0f, false );
		
	// 雲の移動
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );

	/////////////////////////////////////////////////////////////////////////////////////////////
	// キャラの移動処理
	/////////////////////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------
	// カメラ基準の方向を取得
	//------------------------------------------------
	Math::Vector3D vCameraFront, vCameraRight;
	// 前
	objCamMain->GetStyle().GetFront( vCameraFront );
	// 高さは考慮しない
	vCameraFront.y = 0.0f;
	vCameraFront.Normalize();
	// 右
	objCamMain->GetStyle().GetRight( vCameraRight );
	// 高さは考慮しない
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();
	
	//if( objCamMain->GetRotate().x > DEG_TO_ANGLE( 180 ) && objCamMain->GetRotate().x < DEG_TO_ANGLE( 270 ) )
	//{	
		objCamMain->SetRotate( Math::Vector3D( objPlayer->GetRotate().y,  DEG_TO_ANGLE( 90 ) -objPlayer->GetRotate().x , objCamMain->GetRotate().z ) );
	//}
	
	//objCamMain->SetRotate( Math::Vector3D( objPlayer->GetRotate().y,  0 , objCamMain->GetRotate().z ) );
	
	
	//------------------------------------------------
	// キャラの移動
	//------------------------------------------------
	
	/*通常状態*/
	if( !objPopMenu->GetPopUpFlag() && 
		!objPlayer->GetSettingFlag() )

	{	
		objPlayer->Move( objCamMain, objRunEffect );
		
	}
	
	//------------------------------------------------
	// 移動チェック
	//------------------------------------------------
	/*マップとの判定*/
	if( objPlayer->MoveCheck( objField->GetMapActor(S_MAIN) ) )
	{
		CSoundEffect *sndCollision	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Collision") );
		
		sndCollision->GetSEDevice()->Play(0);
		
	}
	
	//else if( objPlayer->MoveCheck( objFlag ) ) 
	//{
	//	
	//}
	//
	//else if( objPlayer->MoveCheck( objBird ) )
	//{
	//
	//}
	
	//else if( objPlayer->MoveCheck( objMouse ) )
	//{
	//
	//}
	//
	//else if( objPlayer->MoveCheck( objMouseDummy ) )
	//{
	//	
	//}
	
	/*電車との判定*/
	else if( objPlayer->MoveCheck( objTrain ) )
	{
	
	}
	
	//---------------------------------------------------------------------------
	//電車にぶつかる処理
	//---------------------------------------------------------------------------
	//if( objPlayer->GetModelActor(S_MAIN)->Collision_Check( objTrain->GetModelActor(S_MAIN) ) )
	//{
	//	//objPlayer->SetPosition( Math::Vector3D(0, 0, 0) );
	//}
	
	//---------------------------------------------------------------------------
	//アメウスとのボックスに当たったとき
	//---------------------------------------------------------------------------
	if( objPlayer->GetModelActor(S_MAIN)->Collision_Check( BoxAmeus ) )
	{
		objAmeus->SetHitFlag( true );
		
	}
	
	
	//------------------------------------------------
	//地面チェック
	//------------------------------------------------
	
	/*マップとの判定*/
	if( objPlayer->GroundCheck( objField ) )
	{
		
	}
	
	/*画面外に出たとき元に戻してやる*/
	objPlayer->GroundAdjust();
	
	//------------------------------------------------
	//地面チェック(電車)
	//------------------------------------------------
	if( objPlayer->GroundCheck( objTrain, S_MAIN ) )
	{

	}
	
	
	
	//---------------------------------------------------------------------------
	//駅の入り口との当たり判定
	//---------------------------------------------------------------------------
	if( pScene->GetFilmCount() > 0)
	{
		/*フラグが回収されていることを確認*/
		if( !objPlayer->GetSetFlag() )
		{
			
			const float STATION_MIN_X = -2.8f;
			const float STATION_MAX_X = 2.8f;
			const float STATION_MIN_Y = -68.0f;
			const float STATION_MAX_Y = -64.0f;
			
			if( ( objPlayer->GetPosition().x > STATION_MIN_X && objPlayer->GetPosition().x < STATION_MAX_X ) && 
				( objPlayer->GetPosition().z > STATION_MIN_Y && objPlayer->GetPosition().z < STATION_MAX_Y ) )
			{
				objPopMenu->SetPopUp( true );
			}

			if( objPopMenu->GetPopUpFlag() )
			{
				
				objPopMenu->SetCaptionName("ミッションを終了しますか?");
				
				eSelectType Select = objPopMenu->SelectYesNo( pScene->GetJoyPad()->GetController() );
				
				if( Select == SELECT_YES )
				{ 
					/*結果画面に移行*/
					pScene->SetNextScene( SCENE_RESULT );
					
					pGameMusic->GetBGMDevice()->Stop();
					
					/*クリア時間の設定*/
					pScene->SetClearTime( pScene->GetCountTime() );			
					
					/*経過時間の初期化*/
					tagTime Time;
					
					pScene->SetCurrentTime( Time );
					
					pScene->SetSceneState( STATE_FADEOUT );
					
					
				}

				else if( Select == SELECT_NO )
				{
					objPlayer->SetPosition( objPlayer->GetOldPosition() );
					
				}
				
			}
		}
		
		else
		{
			const float STATION_MIN_X = -2.8f;
			const float STATION_MAX_X = 2.8f;
			const float STATION_MIN_Y = -68.0f;
			const float STATION_MAX_Y = -64.0f;
			
			if( ( objPlayer->GetPosition().x > STATION_MIN_X && objPlayer->GetPosition().x < STATION_MAX_X ) && 
				( objPlayer->GetPosition().z > STATION_MIN_Y && objPlayer->GetPosition().z < STATION_MAX_Y ) )
			{
				IsNoFlag = true;
				
			}
			
			else
			{
				IsNoFlag = false;
			}
		
		}
		
	}
	
	else
	{
		//const float STATION_MIN_X = -2.0f;
		//const float STATION_MAX_X = 2.0f;
		//const float STATION_MIN_Y = -35.0f;
		//const float STATION_MAX_Y = -32.0f;
		//
		//if( ( objPlayer->GetPosition().x > STATION_MIN_X && objPlayer->GetPosition().x < STATION_MAX_X ) && 
		//	( objPlayer->GetPosition().z > STATION_MIN_Y && objPlayer->GetPosition().z < STATION_MAX_Y ) )
		//{
		//	
		//		//pScene->ChangeScene( SCENE_RESULT );
		//	
		//}
	}
	
	
	//------------------------------------------------
	// カメラモード切替
	//------------------------------------------------
	if ( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_TRIANGLE ) )
	{
		CSoundEffect *snd	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Change") );
		
		objPlayer->ChangeCameraMode( snd->GetSEDevice() );
		
		IsModeVisible = true;
		
	}
	
	static CCharacter *objFlashedObj = NULL;
	
	//----------------------------------------------------------------------------
	// フラグ設置
	//----------------------------------------------------------------------------
	
	const int FLASH_CHARA = 9;
	
	/*フラッシュ対象オブジェクト*/
	CCharacter *pFlashObj[] =
	{
		objMouse[0],
		objMouse[1],
		objMouse[2],
		objBird[0],
		objBird[1],
		objBird[2],
		objBird[3],
		objBird[4],
		objBird[5],
		
	};
	
	
	
	if( !objPlayer->GetSetFlag() )
	{
		Collision::CLine3D vFlagRay;//
		
		Math::Vector3D vPlayerFront;
		
		objPlayer->GetModelActor(S_MAIN)->GetFront( vPlayerFront );
		
		vFlagRay.vStart = objPlayer->GetPosition();
		vFlagRay.vEnd = objPlayer->GetPosition() - vPlayerFront * 10;
		
		//if( objField->GetMapActor(S_MAIN)->HitCheckByRay( vFlagRay ) )
		//{
		//
		//}
		//
		//else
		//{
		#if defined(DEBUG_MAP_EDIT)
			if( objPlayer->GetGravity() >= 0.0f )	
		#else
			if( objPlayer->GetGravity() == 0.0f )	
		#endif
			{
				/*フラグ設置*/
				objPlayer->SettingFlag();
				
				//if( objPlayer->FlagObjectCheck( pFlashObj, FLASH_CHARA, sndSetFlag->GetSEDevice(), &objFlashedObj ) )
				//{
				//	objPlayer->SetFlagToObject( objFlashedObj, sndSetFlag->GetSEDevice() );
				//}
				//
				//else
				//{
				//	objPlayer->SetFlagToGround( sndSetFlag->GetSEDevice(), objFlag  );	
				//}
				
				Collision::CBox FlagRangeBox;
				
				matTemp.Identity();
				
				matWorld.Identity();
				
				matTemp.RotationY( toI( -objPlayer->GetRotate().x ) - DEG_TO_ANGLE( 90 ));
				
				matWorld *= matTemp;
				
				matTemp.Translation( objPlayer->GetPosition().x,
									 objPlayer->GetPosition().y, 
									 objPlayer->GetPosition().z );
				
				matWorld *= matTemp;
				
				/*判定用ボックスの作成*/
				FlagRangeBox.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
				
				if( objPlayer->GetSettingFlag() )
				{
					if( objBird[0]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[0], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[0];
					}
					
					else if( objBird[1]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[1], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[1];
					}
					
					else if( objBird[2]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[2], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[2];
					}
					
					else if( objBird[3]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[3], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[3];
					}
					
					else if( objBird[4]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[4], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[4];
					}
					
					else if( objBird[5]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox )  )
					{
						objPlayer->SetFlagToObject( objBird[5], sndSetFlag->GetSEDevice() );
						objFlashedObj = objBird[5];
					}

					else if( objMouse[0]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox ) )
					{
						objPlayer->SetFlagToObject( objMouse[0], sndSetFlag->GetSEDevice() );
						objFlashedObj = objMouse[0];
						
					}
					
					else if( objMouse[1]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox ) )
					{
						objPlayer->SetFlagToObject( objMouse[1], sndSetFlag->GetSEDevice() );
						objFlashedObj = objMouse[1];
						
					}
					
					else if( objMouse[2]->GetModelActor(S_MAIN)->Collision_Check( FlagRangeBox ) )
					{
						objPlayer->SetFlagToObject( objMouse[2], sndSetFlag->GetSEDevice() );
						objFlashedObj = objMouse[2];
						
					}
					
					else
					{
						objPlayer->SetFlagToGround( sndSetFlag->GetSEDevice(), objFlag  );	
						objFlashedObj = NULL;
						
					}
				}
				
				
		}
			
			
		//}
				
	}
	
	//----------------------------------------------------------------------------
	// フラグ設置ウィンドウの表示
	//----------------------------------------------------------------------------
	if( !objPlayer->GetSetFlag() )
	{
		//if( objFlashedObj != NULL )
		//{
		if( objBird[0]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			//if( pScene->GetMissionMgr()->GetMissionNo == 2 )
			//{
			//	if( pMission->GetFirstPlayFlag() )
			//	{
			//		
			//		
			//	}
			//}
			
			if( objBird[0]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[0]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objBird[1]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objBird[1]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[1]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objBird[2]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objBird[2]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[2]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objBird[3]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objBird[3]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[3]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objBird[4]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objBird[4]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[4]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}

		else if( objBird[5]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objBird[5]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objBird[5]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objMouse[0]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objMouse[0]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objMouse[0]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else if( objMouse[1]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objMouse[1]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objMouse[1]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}

		else if( objMouse[2]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
		{
			if( objMouse[2]->GetStopFlag() )
			{	
				objFlagBal->SetVisibleFlag( true );
			}
			
			objFlagBal->SetAnimID( Math::Point2DI( 0, 0 ) );
			
			objFlagBal->SetPosition( objMouse[2]->GetPosition() + Math::Vector3D(0, 1.5, 0) );
		}
		
		else
		{
			objFlagBal->SetVisibleFlag( false );
		}
		
	}
	
	else
	{
		objFlagBal->SetVisibleFlag( false );
	}
	
	//------------------------------------------------
	// フラッシュ処理
	//------------------------------------------------
	//objPlayer->SetFlash( objAmeus, pScene->GetAppDevice()->GetRenderer() ); 
	objPlayer->SetFlash( pFlashObj, FLASH_CHARA, pScene->GetAppDevice()->GetRenderer(), objEmission );
	
	//for( int i = 0;i < FLASH_CHARA;++i )
	//{
		//objPlayer->SetFlash( pFlashObj[0], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[1], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[2], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[3], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[4], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[5], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[6], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[7], pScene->GetAppDevice()->GetRenderer(), objEmission );
		//objPlayer->SetFlash( pFlashObj[8], pScene->GetAppDevice()->GetRenderer(), objEmission );
		
		
	//}
	//objPlayer->SetFlash( objBird2, pScene->GetAppDevice()->GetRenderer(), objEmission );
	//objPlayer->SetFlash( objBird3, pScene->GetAppDevice()->GetRenderer(), objEmission );
	//
	//
	//objPlayer->SetFlash( objMouse, pScene->GetAppDevice()->GetRenderer(), objEmission );
	//objPlayer->SetFlash( objMouseDummy, pScene->GetAppDevice()->GetRenderer(), objEmission );
	//objPlayer->SetFlash( objMouseDummy2, pScene->GetAppDevice()->GetRenderer(), objEmission );
	
	
	/*当たっていたらフラッシュを浴びた状態にする*/
	pScene->Get3DObject()->FlashedState( );	
	
	/*フラグの回収*/
	#if defined(POP_UP)
		
		objPlayer->RecallFlag( objFlashedObj, sndRecallFlag->GetSEDevice(), objPopMenu );
		
	#else
	
		objPlayer->RecallFlag( objFlashedObj, sndRecallFlag->GetSEDevice(), objFlagBal, objFlag );
		
	#endif
	
	//---------------------------------------------------------------------------
	//フラグの表示判定
	//---------------------------------------------------------------------------
	objFlag->SetVisibleFlag( objPlayer->GetSetFlag() );
	objCamObj->SetVisibleFlag( objPlayer->GetSetFlag() );
	
	pScene->Get3DObject()->SetActorIndex(S_MAIN);
	
	objCamObj->SetPosition( objFlag->GetPosition() + Math::Vector3D( 0, 1.2f, 0 ) );
	
	Math::Matrix matViewToWorld = objCamMain->GetCamera()->ViewToWorld();
	
	/*ワールド行列の設定*/
	objFlagBal->SetMatWorld( matViewToWorld );
	
	objEmotion->SetMatWorld( matViewToWorld );
	
	//---------------------------------------------------------------------------
	//ターゲットへの矢印
	//---------------------------------------------------------------------------
	Math::Vector3D vDirection = objTarget->GetPosition() - objPlayer->GetPosition();
	
	objArrow->SetPosition( objPlayer->GetPosition() + Math::Vector3D( 0, 5, 0 ) );
	
	/*ターゲットとの距離によって色を変更*/
	if( vDirection.Length() >= 0.0 && vDirection.Length() < 10.0 )
	{
		Sint32 MeshCount = objArrow->GetModelActor(S_MAIN)->GetMeshCount();
		
		for( int MeshIndex = 0; MeshIndex < MeshCount;++MeshIndex )
		{
			Sint32 MateCount = objArrow->GetModelActor(S_MAIN)->GetMeshMaterialCount( MeshIndex );
			
			for( int MateIndex = 0; MateIndex < MateCount;++MateIndex )
			{
				objArrow->GetModelActor(S_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 0, 0, 255 ) );
			}
		}
	}
	
	else if( vDirection.Length() >= 10.0 && vDirection.Length() < 30.0 )
	{
		Sint32 MeshCount = objArrow->GetModelActor(S_MAIN)->GetMeshCount();
		
		for( int MeshIndex = 0; MeshIndex < MeshCount;++MeshIndex )
		{
			Sint32 MateCount = objArrow->GetModelActor(S_MAIN)->GetMeshMaterialCount( MeshIndex );
			
			for( int MateIndex = 0; MateIndex < MateCount;++MateIndex )
			{
				objArrow->GetModelActor(S_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 255, 0, 255 ) );
			}
		}
	}
	
	else
	{
		Sint32 MeshCount = objArrow->GetModelActor(S_MAIN)->GetMeshCount();
		
		for( int MeshIndex = 0; MeshIndex < MeshCount;++MeshIndex )
		{
			Sint32 MateCount = objArrow->GetModelActor(S_MAIN)->GetMeshMaterialCount( MeshIndex );
			
			for( int MateIndex = 0; MateIndex < MateCount;++MateIndex )
			{
				objArrow->GetModelActor(S_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 0, 0, 255, 255 ) );
			}
		}
	}
	
	/*ターゲットの位置によって、方向を変える*/
	Sint32 RotX = Math::ATan2( vDirection.x, vDirection.z );
	//Sint32 RotY = Math::ATan2( vDirection.z, vDirection.y );
	
	objArrow->SetRotate( Math::Vector3D( toF(-RotX), 0, 0 ) );
	
	pObjTargetArrow->SetVisibleFlag( true );
	
	pObjTargetArrow->SetPosition( objTarget->GetArrowPosition() );
	
	static Math::Vector3D vRot;
	
	vRot.x += DEG_TO_ANGLE( 1 );
	vRot.y = 0;
	vRot.z = 0;
	
	pObjTargetArrow->SetRotate( vRot );
	
	#if defined( DEBUG_MAP_SEE )
	
		CEnemy *pTarget = dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName(TargetStr) );
		
		pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 80), CColor( 128, 128, 255 ), "KeyTime:%f", pTarget->GetKeyTime() );
		pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 100), CColor( 128, 128, 255 ), "pTarget:x%f:y:%f:z:%f", pTarget->GetPosition().x, pTarget->GetPosition().y, pTarget->GetPosition().z );
		
		
		
		pTarget->ChangeKeyTime( pScene->GetMouse() );
		
		pTarget->ChangeKeySpeed( pScene->GetJoyPad()->GetController() );
		
	#elif defined(DEBUG) | (_DEBUG)
	
		//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 80), CColor( 128, 128, 255 ), "KeyTime:%f", objMouseDummy->GetKeyTime() );
		//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI(5, 100), CColor( 128, 128, 255 ), "pTarget:x%f:y:%f:z:%f", pTarget->GetPosition().x, pTarget->GetPosition().y, pTarget->GetPosition().z );
	
		
	
	#endif
	
	objArrow->SetVisibleFlag( true );
	
	pObjTargetArrow->SetVisibleFlag( true );

	if( !objPopMenu->GetPopUpFlag() )
	{	
		pScene->Get3DObject()->MoveExec();
	}
	
	/*処理*/
	pScene->Get3DObject()->Exec();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーンへのレンダリングリクエスト
	/////////////////////////////////////////////////////////////////////////////////////////////

	// シーン管理
	//   Scene::ISceneManagerインターフェイスを使ったシーン管理を開始します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Begin( false );
	
	// スカイドームのレンダリング
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_Rendering();

	// 影の影響を受けるように設定
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_0 );

	objField->Rendering(S_MAIN);
	
	// 影を落とすように設定
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_1 );

	//objField->GetMapActor(S_MAIN)->RenderingBounding(
	
	//レンダリング
	pScene->Get3DObject()->Rendering(S_MAIN);
	
	#if defined( DEBUG ) | (_DEBUG )	
		pDebugLine->Rendering();
	#endif
	
	// シーン管理を終了
	//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->End();
	
	pExpFont->Exec();

	//--------------------------------------------------------------------------
	//サブ画面
	//--------------------------------------------------------------------------
	/*描画位置の設定*/
	pScene->GetSceneMgr(S_SUB)->SetRenderPos( Math::Vector2D( 0, 0 ) );
	
	/*描画パラメータの設定*/
	pScene->GetSceneMgr(S_SUB)->SetParameter();
	
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetLightParameter_Directional(
		Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ライトの方向
		Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ライトの色

		
	//pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetLightParameter_AddPoint
	

	// アンビエント
	// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetLightParameter_Ambient(
		Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// 天球の色
		Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// 地表の色
		
	//ソフトパーティクルのアルファ値のスケールを設定
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetParameter_SoftParticleScale( 300 );
	
	
	//objCamSub->SetPosition( objCamObj->GetPosition() );
	
	// カメラの注視目標の設定
	objCamSub->SetTargetPos( objCamObj->GetPosition() /* + Math::Vector3D(0.0f, 2.0f, -7.0f)*/);
	
	/*トランスフォームの設定*/
	objCamSub->SetTransform2( );

	// シーンにシャドウマップ用カメラ設定
	//   シャドウマップのレンダリングに使うカメラを設定
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetParameter_Shadow(
		objCamObj->GetPosition() + Math::Vector3D( -3.0f, 20.0f, -5.0f ),	// カメラ位置
		objCamObj->GetPosition(),									// カメラ注視点
		100.0f,								// レンダリングサイズ
		10.0f,								// 近クリップ面
		30.0f,								// 遠クリップ面
		0.0f,								// Z値バイアス（実際に見ていい感じに調整
		0.7f );								// 影の強さ（SHADING_NORMALの時のみ有効）
		
	// ハッチング用のパラメーター
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetParameter_Toon( Math::Vector3D(0.5, 0.5, 0.5 ), 0.1f );
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetParameter_ToonEdge( 0.3f, 30.0f, false );
		
		
	// 雲の移動
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );
	
	objCamSub->SetRotate( Math::Vector3D( objCamObj->GetRotate().y ,  
						  objCamObj->GetRotate().x - DEG_TO_ANGLE(90) ,
						  objCamSub->GetRotate().z ) );
						  
	#if defined(DEBUG) | (_DEBUG)	
		pDebugLine->Exec();
	#endif
						  
	//------------------------------------------------
	// カメラの移動処理
	//------------------------------------------------
	if( objPlayer->IsCameraMode() )
	{
		
		if( !objPopMenu->GetPopUpFlag() )
		{	
			objCamObj->Move( pScene->GetJoyPad()->GetController() );
			//objCamObj->Move( pScene->GetJoyPad()->GetJoyStick() );
		}
	}
	
	
	
	
	//----------------------------------------------------------------------------
	//メニューの表示
	//----------------------------------------------------------------------------
	if( !objPopMenu->GetPopUpFlag() )
	{
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_START ) )
		{
			pScene->SetNextScene( SCENE_STARTMENU );
			
			pScene->SetFontSize( 30 );
			
			pScene->SetSceneState( STATE_FADEOUT );
			
			//pScene->GetAppDevice()->GetRenderer()->ChangeDebugPrintFont( "TT-JTCウインZ10", 30 );
			
		}
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーンへのレンダリングリクエスト
	/////////////////////////////////////////////////////////////////////////////////////////////

	// シーン管理
	//   Scene::ISceneManagerインターフェイスを使ったシーン管理を開始します。
	
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->Begin( false );
	
	// スカイドームのレンダリング
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SceneSkydoom_Rendering();
	
	// 影の影響を受けるように設定
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_0 );

	/*フィールドのレンダリング*/
	objField->Rendering(S_SUB);

	// 影を落とすように設定
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_1 );

	/*アクターのインデックスを切り替える*/
	pScene->Get3DObject()->SetActorIndex(S_SUB);
	
	objFlag->SetPosition( objFlag->GetPosition() );//Math::Vector3D( objPlayer->GetPosition().x, objPlayer->GetPosition().y, objPlayer->GetPosition().z ) );

	objCamObj->SetPosition( objCamObj->GetPosition() );
	
	objArrow->SetVisibleFlag( false );
	
	objFlagBal->SetVisibleFlag( false );
	
	pObjTargetArrow->SetVisibleFlag( false );
	//objFlash->SetVisibleFlag( true );
	
	if( !objPopMenu->GetPopUpFlag() )
	{	
		pScene->Get3DObject()->MoveExec();
	}
	
	/*処理*/
	pScene->Get3DObject()->Exec();
	
	objField->Exec();
	
	pScene->Get2DObject()->Exec();
	
	//objPointa->GetSprite()->Begin();
	//
	//objPointa->GetSprite()->DrawSquare( 
	//
	//objPointa->GetSprite()->End();
	
	
	// キャラのレンダリング
	pScene->Get3DObject()->Rendering(S_SUB);
	
	//pDebugLine->Rendering();
	
	
	// シーン管理を終了
	//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
	pScene->GetSceneMgr(S_SUB)->GetSceneMgr()->End();
		

}

