//*============================================================================
//SceneMissionSelect.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneMissionSelect.h"


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneMissionSelect::CSceneMissionSelect(void)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneMissionSelect::~CSceneMissionSelect(void)
{

}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneMissionSelect::Exec( CScene *pScene )
{
	static Sint32 Cursor = 0;
	
	const int MISSION_MAX = 5;
	
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CSprite *pBG = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("MissionSelect") );
	
	CSprite *pPin = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pin") );
	
	CFontSprite *pNumFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("NumFont") );
	
	CFontSprite *pMiContFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ContentFont") );
	
	CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ExplainFont") );
	
	
	pNumFont->SetPosition( Math::Vector3D( 80, 520, 0 ) );
	pMiContFont->SetPosition( Math::Vector3D( 340, 490, 0 ) );
	
	//pExpFont->SetPosition( Math::Vector3D( 600, 10 )
	
	Math::Point2DF vPos[] =
	{
		Math::Point2DF( 600, 10 ),
	};
	
	vector< string > vecText;
	
	vecText.push_back( "R2 ミッション決定" );
	
	pExpFont->SetVecTextChat( vecText );
	
	/*画面のクリア*/
	pRender->Clear();
	
	/*描画開始*/
	pRender->Begin();
	
	pBG->Rendering();
	
	CBGM *pTitleMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("TitleBGM") );
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{
		if( !pTitleMusic->GetBGMDevice()->IsPlay() )
		{	
			pTitleMusic->GetBGMDevice()->Play( );
		}
		
	}
	
	if( pScene->GetSceneState() == STATE_FADEOUT )
	{
		pTitleMusic->GetBGMDevice()->Stop();
	}
	
	
	int MissionClrCount = 0;//ミッションのクリア数カウント
	
	#if defined(DEBUG) | (_DEBUG)  
	
		MissionClrCount = 4;
	
	#else
				
		/*ミッションクリア数のカウントアップ*/
		for( int i = 0; i < pScene->GetMissionMgr()->GetMissionNum(); ++i )
		{
			CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
			
			if( pMission->GetGameClearFlag() )
			{
				MissionClrCount++;
				
			}
		}
		
		//MissionClrCount = 4;
		
		if( MissionClrCount >= 4 )
		{
			MissionClrCount = 4;
		}
				
				
	#endif
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{
		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
		
		pMission->GetMissionData().m_pPhotoSpr->DrawGrayScale( pRender );
		
	}
	
	for( int i = 0;i < MISSION_MAX;++i )
	{
		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			pMission->GetMissionData().m_pPhotoSpr->Rendering();
			
			char Temp[10];
			
			sprintf( Temp, "%d", pMission->GetHiScore() );
			
			/*文字列の設定*/
			pMiContFont->SetVecTextChat( pMission->GetMissionData().m_vecMissionContent );
			
			pNumFont->SetDrawString( Temp ) ;
		}
		
	}
	
	/*ピン表示用ID*/
	Math::Point2DF Anim[] =
	{
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
	};
	
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{	
		Math::Point2DF Pos[] =
		{
			Math::Point2DI( 383, 142 ),
			Math::Point2DI( 228, 232 ),
			Math::Point2DI( 583, 62 ),
			Math::Point2DI( 178, 72 ),
			Math::Point2DI( 543, 252 ),
		};

		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
		
		pPin->Rendering();
		
		pMiContFont->Rendering();
		
		/*ハイスコアの描画*/
		pNumFont->Rendering();
	
		if( pMission->GetGameClearFlag() )	
		{
			Anim[i].x = 1;
			
		}
		
		else
		{
			Anim[i].x = 0;
		}
		
		pPin->DrawMultiGraph( Pos, Anim,  MissionClrCount + 1 );		
		
	}
	
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{	
		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			pMission->GetMissionData().m_pFontSpr->Rendering();
		}
		
	}
	
	//pExpFont->Rendering();
	
	pNumFont->Exec();
	
	pMiContFont->DrawMultiLine();
	
	pExpFont->DrawMultiLine( vPos );
	//pMiContFont->Exec();
	
	/*操作説明の文字描画*/
	//pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 600, 10 ), CColor( 255, 255, 255 ), "R2ボタン　ミッション決定" );
	
	
	/*ミッション概要の描画*/
	
	/*描画終了*/
	pRender->End();
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{
		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
		
		pMission->Exec();
	}
	
	pBG->Exec();
	
	static bool IsFade = false;
	
	/*ミッションの決定*/
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
	{
		pTitleMusic->GetBGMDevice()->Stop();
		
		/*ミッション番号の設定*/
		pScene->GetMissionMgr()->SetMissionNo( Cursor );
		
		CSoundEffect *sndDecide	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Decide") );
			
			
		/*ミニキャラの最大*/
		const int FLASH_CHARA = 9;
		
		/*ミニキャラのオブジェクト名*/
		const char *MiniObjName[] =
		{
			"Mini_Bird1",
			"Mini_Bird2",
			"Mini_Bird3",
			"Mini_Bird4",
			"Mini_Bird5",
			"Mini_Bird6",
			"Mini_Mouse1",
			"Mini_Mouse2",
			"Mini_Mouse3",
		};
			
		/*一旦全ミニキャラを非表示にする*/
		for( int i = 0;i < FLASH_CHARA;++i )
		{	
			CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[i]) ); 
			objMiniSpr->SetVisibleFlag( false );
			objMiniSpr->SetMissionVisible( false );
		}
		
		/*ミッションによって、表示させるミニキャラを変える*/
			
		/*鳥使うミッション*/
		if( Cursor == 2 )
		{
			for( int BirdNum = 0;BirdNum < BIRD_MAX;++BirdNum )
			{
				CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[BirdNum]) ); 
				
				objMiniSpr->SetMissionVisible( true );
			}
		}
		
		/*ねずみつかうミッション*/
		else if( Cursor == 3 )
		{
			for( int MouseNum = BIRD_MAX; MouseNum < FLASH_CHARA;++MouseNum )
			{
				CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[MouseNum]) ); 
				
				objMiniSpr->SetMissionVisible( true );
				
			}
		}
			
		pBG->SetVisibleFlag( false );
		
		for( int i = 0; i < MISSION_MAX; ++i )
		{
			CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
			
			pMission->GetMissionData().m_pFontSpr->SetVisibleFlag( false );
			
			pMission->GetMissionData().m_pPhotoSpr->SetVisibleFlag( false );
			
			pPin->SetVisibleFlag( false );
			
			
		}
		
		pScene->SetNextScene( SCENE_CHAT );
		
		
		//if( pScene->GetSceneState() == STATE_FADEOUT )
		//{
		//	pTitleMusic->FadeOut();
		//}
		//
		//else
		//{
		//	pTitleMusic->GetBGMDevice()->SetVolume( 100 );
		//}
		
		
		vecText.clear();
		
		pExpFont->SetVecTextChat( vecText );
		
		pScene->SetSceneState( STATE_FADEOUT );	
		
		if( pScene->GetSceneState() == STATE_STANDBY )
		{	
			sndDecide->GetSEDevice()->Play( 0 );
		}
		
			
	}
	
	
	eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, MissionClrCount+1 );
	
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, eButtonUpDown ) )
	{
		CSoundEffect *sndSelect	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Select") );
		sndSelect->GetSEDevice()->Play( 0 );
	}
	
	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, 4 );

}
