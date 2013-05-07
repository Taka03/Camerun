//*============================================================================
//SceneMissionSelect.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneChat.h"
#include <fstream>


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneChat::CSceneChat(void)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneChat::~CSceneChat(void)
{

}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneChat::Exec( CScene *pScene )
{
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CSprite *pBG = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Chat") );
	
	#if defined( DEBUG_CHAT )
	
		std::ifstream ifs("missionno.txt");
		
		Sint32 MissionNo = 0;
		
		ifs >> MissionNo;
		
		CMission *pMission = dynamic_cast<CMission *>( pScene->GetMissionMgr()->GetMission( MissionNo ) );
	
	
	#else
		Sint32 MissionNo = pScene->GetMissionMgr()->GetMissionNo();
		
		CMission *pMission = dynamic_cast<CMission *>( pScene->GetMissionMgr()->GetMission( MissionNo ) );
		
	#endif
	
	CFontSprite *pChatFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ChatFont") );
	
	pChatFont->SetVecTextChat( pMission->GetMissionData().m_vecChat );
	
	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("ChatBGM") );
	
	pGameMusic->Exec();
	
	/*画面のクリア*/
	pRender->Clear();
	
	/*描画開始*/
	pRender->Begin();
	
	pBG->Rendering();
	
	pChatFont->Rendering();
	
	//pChatFont->Draw();
	
	pRender->End();
	
	if( pChatFont->DrawNovelStyle( pScene->GetAppDevice()->GetCore(), pScene->GetJoyPad()->GetController() ) )
	{
		
	#if defined (DEBUG_CHAT)
	
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
		{
			pChatFont->SetRefCount( 0 );
		}
	
	
	#else
		
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
		{
			pBG->SetVisibleFlag( false );
			
			pScene->SetFontSize( 15 );
			
			pScene->SetNextScene( SCENE_DRAWMISSION );
			
			pScene->SetSceneState( STATE_FADEOUT );
		
		}
		
	#endif
	
	}
	
	pBG->Exec();
	
	//pChatFont->Exec();
	
	//pChatFont->GetFontSprite()->Begin();
	
	//const int STR_LENGTH = 29;
	
	
	//pChatFont->GetFontSprite()->DrawString( pChatFont->GetFontSprite
	
	//string Str = pChatFont->GetDrawString().substr(0, (STR_LENGTH+1)*2);
	//
	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 ), CColor(100, 100, 100 ), STR_LENGTH );
	//
	//Str = pChatFont->GetDrawString().substr( (STR_LENGTH+1)*2, (STR_LENGTH+1)*3 );
	//
	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 + pChatFont->GetFontSprite()->GetSize() ), CColor(100, 100, 100 ), STR_LENGTH );

	//Str = pChatFont->GetDrawString().substr( (STR_LENGTH+1)*3, (STR_LENGTH+1)*4 );
	//
	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 + pChatFont->GetFontSprite()->GetSize() * 2 ), CColor(100, 100, 100 ), STR_LENGTH );
	//
	//pChatFont->GetFontSprite()->End();
	//
	if( pMission->GetGameClearFlag() )
	{
		/*次のシーンに移動*/
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_START ) )
		{	
			pBG->SetVisibleFlag( false );
			
			pScene->SetFontSize( 40 );
			
			pScene->SetNextScene( SCENE_DRAWMISSION );
			
			pScene->SetSceneState( STATE_FADEOUT );
			
			
		}
	}

	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, MissionClrCount + 1 );
	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, 4 );

}
