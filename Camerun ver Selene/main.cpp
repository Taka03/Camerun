//*============================================================================
//main.cpp
//*============================================================================


//=============================================================================
//include
//=============================================================================
#include "field.h"
#include "player.h"
#include "joypad.h"
#include "camera.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameSceneManager.h"
#include "CamObject.h"
#include "enemy.h"
#include "Photo.h"
#include "SoundEffect.h"
#include "BGM.h"
#include "Draw2DObject.h"
#include <math.h>
#include "SceneGameMain.h"
#include "SceneGameTitle.h"
#include "SceneGameResult.h"
#include "SceneMissionSelect.h"
#include "SceneChat.h"
#include "SceneCalcScore.h"
#include "SceneStartMenu.h"
#include "SceneDrawMission.h"
#include "ScenePhoto.h"
#include "SceneDemo.h"
#include "SceneEnding.h"
#include "Application.h"

//=============================================================================
//variable
//=============================================================================

//=============================================================================
//マルチスレッド用の処理
//=============================================================================
void StThread( LPVOID lpParam )
{
	CScene *pScene = (CScene *)lpParam;
	
	if( pScene->Init( pScene ) )
	{
		pScene->SetLoadEndFlag( true );
		
		::ExitThread(0);
	}
	
}

//キャスト用クラス
//template<typename T>
//void DynamicCast( T *DstObj, CGameObject *SrcObj, string name )
//{
//	DstObj = dynamic_cast<T *>( SrcObj->FindObjectFromName(name) );
//	
//}


//----------------------------------------------------------------------------------
/**
	@brief メイン関数

	コンソールアプリケーションでいう所の main() 関数です。
	ウィンドウズアプリケーションでは以下の関数が main() になります。
*/
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{

	CApplication *pAppli = new CApplication();
	
	//CGame *pGame = new CGame();
	CJoyPad *pJoyPad = new CJoyPad();
	Selene::Peripheral::IKeyboard *pKeyboard = NULL;

	/*コアの生成N*/
	pAppli->CreateCore();
	
	//----------------------------------------------------------------------------
	// 初期化
	//----------------------------------------------------------------------------
	if ( pAppli->Initialize() )
	{
		pJoyPad->CreateDevice( pAppli->GetCore() );
		
		pKeyboard = pAppli->GetCore()->GetKeyboard();
		
		CScene *pScene = new CScene( pAppli, pJoyPad );		
		
		CGameSceneManager *pGameSceneMgr = new CGameSceneManager( pScene );
		
		const int FADE_COUNT = 1;
		
		/*シーンの追加*/
		pGameSceneMgr->AddScene( SCENE_INIT, pScene );
		pGameSceneMgr->AddScene( SCENE_TITLE, new CSceneGameTitle() );
		pGameSceneMgr->AddScene( SCENE_MISSIONSELECT, new CSceneMissionSelect() );
		pGameSceneMgr->AddScene( SCENE_CHAT, new CSceneChat() );
		pGameSceneMgr->AddScene( SCENE_DRAWMISSION, new CSceneDrawMission() );
		pGameSceneMgr->AddScene( SCENE_DEMO, new CSceneDemo() );
		pGameSceneMgr->AddScene( SCENE_GAMEMAIN, new CSceneGameMain() );
		pGameSceneMgr->AddScene( SCENE_PHOTOSCREEN, new CScenePhoto() );
		pGameSceneMgr->AddScene( SCENE_RESULT, new CSceneGameResult() );
		pGameSceneMgr->AddScene( SCENE_CALCSCORE, new CSceneCalcScore() );
		pGameSceneMgr->AddScene( SCENE_STARTMENU, new CSceneStartMenu() );
		//pGameSceneMgr->AddScene( SCENE_ENDING, new CSceneEnding() );
		
		pScene->Get2DObject()->AppendObject( new CSprite("char.png", Math::Vector2D( 520, 500 ) ), "Loading", true );
		
		pScene->GetAppDevice()->GetFileMgr()->SetCurrentPath( "Texture" );
		
		pScene->Get2DObject()->Load( pScene->GetAppDevice()->GetRenderer() );
		
		pScene->GetAppDevice()->GetRenderer()->SetDrawTextFont("MS ゴシック", 25 );
		
		::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)(StThread), pScene, NULL, 0 );
		
		//-----------------------------------------------------------------
		// メインループ
		//-----------------------------------------------------------------
		while ( pAppli->GetCore()->Run() )
		{
			pGameSceneMgr->Exec();
				
			if( pKeyboard->GetKeyData( SELENE_VK_F2 ) )
			{
				pAppli->GetCore()->ChangeScreenMode();
			}
			
			pJoyPad->Update();
			
			pScene->SceneStateExec();
			
		}
		
		SAFE_DELETE( pGameSceneMgr );
		SAFE_DELETE( pScene );
		
		SAFE_RELEASE( pKeyboard );
		//SAFE_DELETE( pJoyPad );
			
	}
		
	
//	SAFE_DELETE( pGame );

	//--------------------------------------------------------
	// システムの解放
	//--------------------------------------------------------
	// アプリケーションの終了時に必ず呼び出して下さい。
	// またこの関数を呼び出す前に取得した全ての
	// インターフェイスを解放してください。
	System::Finalize();

	return 0;
}

