//*============================================================================
//Scene.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Scene.h"
#include "player.h"
#include "EnemyAmeus.h"
#include "EnemyBird.h"
#include "EnemyMouse.h"
#include "EnemyManta.h"
#include "EnemyRabbit.h"
#include "Mission.h"

#include <fstream>


//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pGame:ゲーム用デバイス
//	pJoy:ジョイパッド用デバイス
//=============================================================================
CScene::CScene( CApplication *pAppli, CJoyPad *pJoy ) :m_pMouse(NULL)
{
	m_pApp = pAppli;
	
	pAppli->AddRef();

	m_pJoyPad = pJoy;
	
	pJoy->AddRef();
	
	m_pGameObj = new CGameObject();
	m_p3DObj = new CDraw3DObject();
	m_p2DObj = new Draw2DObject();
	m_pSoundObj = new CSound();
	//m_pDebugLine = new CDebugLine();
	
	m_pMissionMgr = new MissionManager();
	
	for( int i = 0;i < S_MAX;++i )
	{
		m_pSceneMgr[i] = new CSceneManager();
	}
	
	m_eNowScene = SCENE_INIT;
	m_eNextScene = SCENE_TITLE;
	
	m_eSceneState = STATE_STANDBY;
	
	m_fFadeTime = 60.0f;
	
	m_IsFirstBoot = true;
	m_IsLoadEnd = false;
	
	m_FilmCount = 0;
	
	m_FontSize = 15;
	
//	CThread.Create( StThread, this );
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene::~CScene()
{
	SAFE_DELETE( m_pMouse );
	
	SAFE_DELETE( m_pSoundObj );
	SAFE_DELETE( m_p2DObj );
	SAFE_DELETE( m_p3DObj );
	
	SAFE_DELETE( m_pGameObj );
	
	SAFE_DELETE( m_pMissionMgr );
	
	for( int i = 0;i < S_MAX;++i )
	{	
		SAFE_DELETE( m_pSceneMgr[i] );
	}
	
	SAFE_DELETE( m_pJoyPad );
	
	SAFE_DELETE( m_pApp );
	
	
}

//=============================================================================
//初期化
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
bool CScene::Init( CScene *pScene )
{
	if( m_IsFirstBoot )
	{
		/*マウスの取得*/
		pScene->m_pMouse = m_pApp->GetCore()->GetMouse();
		
		//-----------------------------------------------------------------
		// シーン
		//-----------------------------------------------------------------
		m_pSceneMgr[S_MAIN]->SetRenderSize( m_pApp->GetScreenWidth(), m_pApp->GetScreenHeight() );
		m_pSceneMgr[S_SUB]->SetRenderSize( m_pApp->GetScreenWidth(), m_pApp->GetScreenHeight() );
		
		for( int i = 0;i < S_MAX;++i )
		{
			m_pSceneMgr[i]->CreateDevice( m_pApp->GetRenderer() );
		}
		
		m_pSceneMgr[S_MAIN]->SetInitParameter( false );
		m_pSceneMgr[S_SUB]->SetInitParameter( true );
		
		//-----------------------------------------------------------------
		//オブジェクトの追加
		//-----------------------------------------------------------------
		//std::ifstream ifs("aa.csv");
		
		//char Temp[256];
		//char Temp2[256];
		//
		//string strDataName;
		//string strObjectName;
		

		//ifs >> Temp >> Temp2;
		//
		//strDataName = Temp;
		//strObjectName = Temp2;
		
		//m_pGameObj->AppendObject( new CField(strDataName), strObjectName, true );
		
		Selene::File::IResourceFile *pResFile = NULL;
		
		
		#if defined(DEBUG_CHAT)
		
		#else
		
		m_p3DObj->AppendObject( new CField("map.stm"), "Field", true );
		//m_pGameObj->AppendObject( new CField("Kaidan.stm"), "Field", true );
		//ifs >> Temp >> Temp2 ;
		//
		//strDataName = Temp;
		//strObjectName = Temp2;
		
		m_pApp->GetFileMgr()->SetCurrentPath( "CSV" );
		
		
		pResFile = m_pApp->GetFileMgr()->FileOpen("Ameus.csv");
		
		m_p3DObj->AppendObject( new CPlayer("Camerun.smf" , Math::Vector3D( 0, 7, -73) ) , "Player", true ); 
		m_p3DObj->AppendObject( new CTrain("train1.smf", Math::Vector3D(0.0f, 0.0f, -73.0f) ), "Train", true );
		m_p3DObj->AppendObject( new CEnemyAmeus("ameus.smf", Math::Vector3D(-141.0f , 1.0f, -238.0f), pResFile->GetNamePointer() ), "Ameus", true );
		
		SAFE_RELEASE( pResFile );
		
		for( int i = 0;i < BIRD_MAX;++i )
		{
			char Temp[20] = "";
			
			sprintf( Temp, "bird%d.csv", i+1 );
			
			pResFile = m_pApp->GetFileMgr()->FileOpen(Temp);
			
			sprintf(Temp, "Bird%d", i+1 );
			
			m_p3DObj->AppendObject( new CEnemyBird("bird.smf", Math::Vector3D(0.0f, 120.0, -45.0f), pResFile->GetNamePointer() ), Temp, true );
			
			SAFE_RELEASE( pResFile );
		}
		
		for( int i = 0;i < MOUSE_MAX;++i )
		{
			char Temp[20] = "";
			
			sprintf( Temp, "mouse%d.csv", i+1 );
			
			pResFile = m_pApp->GetFileMgr()->FileOpen(Temp);
			
			sprintf(Temp, "Mouse%d", i+1 );
			
			m_p3DObj->AppendObject( new CEnemyMouse("mouse.smf", Math::Vector3D(0.0f, 0.0f, -40.0f), pResFile->GetNamePointer() ), Temp, true );
			
			SAFE_RELEASE( pResFile );
		}
		
		pResFile = m_pApp->GetFileMgr()->FileOpen("manta.csv");
		
		#if defined( TEST_RELEASE )	
			m_p3DObj->AppendObject( new CEnemyManta("manta.smf", Math::Vector3D(0.0f, 0.0f, -40.0f), pResFile->GetNamePointer() ), "Manta", true );
		#else
			m_p3DObj->AppendObject( new CEnemyManta("manta.smf", Math::Vector3D(0.0f, 80.0f, -40.0f), pResFile->GetNamePointer() ), "Manta", true );
		#endif
		
		SAFE_RELEASE( pResFile );
		
		pResFile = m_pApp->GetFileMgr()->FileOpen("rabbit.csv");
		
		m_p3DObj->AppendObject( new CEnemyRabbit("rabbit.smf", Math::Vector3D(0.0f, 0.0f, -40.0f), pResFile->GetNamePointer() ), "Rabbit", true );
		
		SAFE_RELEASE( pResFile );
		
		m_p3DObj->AppendObject( new CCamObject("camera.smf"), "CamObj", false );
		
		m_p3DObj->AppendObject( new CCharacter("statue_dove.smf", Math::Vector3D( -188, 3.6f, -361) ), "FountObj", true );
		m_p3DObj->AppendObject( new CCharacter("flag.smf", Math::Vector3D( -188, 3.6f, -361) ), "Flag", true );
		
		//m_p3DObj->AppendObject( new CFlagObject("flag.smf"), "Flag", false );
		
		//m_p3DObj->AppendObject( new CCharacter("statue_dove.smf", Math::Vector3D( -188, 4.4f, -361) ), "FountObj2", true );
		//m_p3DObj->AppendObject( new CCharacter("statue_dove.smf", Math::Vector3D( -188, 4.4f, -361) ), "FountObj3", true );
		
		
		m_p3DObj->AppendObject( new CCharacter("arrow.smf", Math::Vector3D( 0, 0, 0 ) ), "Arrow", true );
		//m_p3DObj->AppendObject( new CSprite3D("title.png", Math::Vector3D( 0, 0, -100 ) ), "BillBoard", true );
		m_p3DObj->AppendObject( new CCharacter("target.smf", Math::Vector3D( 0, 0, -100 ) ), "Target", true );
		m_p3DObj->AppendObject( new CCharacter("star.smf", Math::Vector3D( 0, 0, -100 ) ), "Star", false ) ;
		m_p3DObj->AppendObject( new CCharacter("flying_island.smf", Math::Vector3D( 162, 180, -212 ) ), "IsLand", true ) ;
		
		
		m_p3DObj->AppendObject( new CSprite3D("flgemo.dds", Math::Vector3D( 0, 0, -10 ) ), "FlagBalloon", true );
		m_p3DObj->AppendObject( new CParticle("smoke.dds", Math::Vector3D(0, 0, 10) ), "RunEffect0", false );
		m_p3DObj->AppendObject( new CParticle("smoke.dds", Math::Vector3D(0, 0, 10) ), "RunEffect1", false );
		m_p3DObj->AppendObject( new CParticle("smoke.dds", Math::Vector3D(0, 0, 10) ), "RunEffect2", false );
		m_p3DObj->AppendObject( new CParticle("smoke.dds", Math::Vector3D(0, 0, 10) ), "RunEffect3", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission0", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission1", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission2", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission3", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission4", false );
		m_p3DObj->AppendObject( new CFlash("flash2.png", Math::Vector3D( 0, 0, 0 ) ), "Emission5", false );
		
		
		m_p3DObj->AppendObject( new CSprite3D("emo.dds", Math::Vector3D( 0, 0, 0 ) ), "Emotion", false );
	
		
		m_pSoundObj->AppendObject( new CSoundEffect("shutter.WAV"), "Shutter", true );
		m_pSoundObj->AppendObject( new CSoundEffect("flag.WAV"), "Flag", true );
		m_pSoundObj->AppendObject( new CSoundEffect("run.WAV"), "Run", true );
		m_pSoundObj->AppendObject( new CSoundEffect("train.WAV"), "STrain", true );
		m_pSoundObj->AppendObject( new CSoundEffect("change.WAV"), "Change", true );
		m_pSoundObj->AppendObject( new CSoundEffect("enter.WAV"), "Enter", true );
		m_pSoundObj->AppendObject( new CSoundEffect("collision.WAV"), "Collision", true );
		m_pSoundObj->AppendObject( new CSoundEffect("mouse.WAV"), "Mouse", true );
		m_pSoundObj->AppendObject( new CSoundEffect("flagrecall.WAV"), "RecallFlag", true );
		m_pSoundObj->AppendObject( new CSoundEffect("flagsetfail.WAV"), "SetFlagFail", true );
		m_pSoundObj->AppendObject( new CSoundEffect("missionclear.WAV"), "MissionClear", true );
		m_pSoundObj->AppendObject( new CSoundEffect("missionfail.WAV"), "MissionFail", true );
		m_pSoundObj->AppendObject( new CSoundEffect("bird.WAV"), "Bird", true );
		m_pSoundObj->AppendObject( new CSoundEffect("select.WAV"), "Select", true );
		m_pSoundObj->AppendObject( new CSoundEffect("DrumRoll.WAV"), "DrumRoll", true );
		m_pSoundObj->AppendObject( new CSoundEffect("decide.WAV"), "Decide", true );
		
		
		
		
		//while( !ifs.eof() )
		//{	
		//	ifs >> Temp >> Temp2;
		//	
		//	strDataName = Temp;
		//	strObjectName = Temp2;
		//	
		//	m_pSoundObj->AppendObject( new CSoundEffect(strDataName), strObjectName, true );
		//	
		//}
		
		#endif
		
		m_pSoundObj->AppendObject( new CBGM("BGM.ogg"), "TitleBGM", true );
		m_pSoundObj->AppendObject( new CBGM("Rolling Railing Hiking!.ogg"), "GameBGM", true );
		m_pSoundObj->AppendObject( new CBGM("TitleBGM.ogg"), "ChatBGM", true );
		
		m_pSoundObj->AppendObject( new CBGM("BGM.ogg"), "ResultBGM", true );
		
		
		m_pGameObj->AppendObject( new CCamera(), "CamMain", true );
		m_pGameObj->AppendObject( new CCamera(), "CamSub", true );
		
		m_pGameObj->AppendObject( new CFontSprite("font.sff", Math::Vector2D( 200, 400 ) ), "TitleFont", true );
		m_pGameObj->AppendObject( new CFontSprite("font2.sff", Math::Vector2D( 200, 400 ) ), "CommonFont", true );
		m_pGameObj->AppendObject( new CFontSprite("MissionFont.sff", Math::Vector2D( 430, 13) ), "MissionFont", true );
		m_pGameObj->AppendObject( new CFontSprite("MenuFont.sff", Math::Vector2D( 220, 100 ) ), "MenuFont", true );
		m_pGameObj->AppendObject( new CFontSprite("ChatFont.sff", Math::Vector2D( 110, 465 ) ), "ChatFont", true );
		m_pGameObj->AppendObject( new CFontSprite("NumFont.sff", Math::Vector2D( 110, 465 ) ), "NumFont", true );
		m_pGameObj->AppendObject( new CFontSprite("MiContFont.sff", Math::Vector2D( 110, 465 ) ), "ContentFont", true );
		m_pGameObj->AppendObject( new CFontSprite("MiContFont2.sff", Math::Vector2D( 110, 465 ) ), "ContentFont2", true );
		m_pGameObj->AppendObject( new CFontSprite("ExplainFont.sff", Math::Vector2D( 110, 465 ) ), "ExplainFont", true );
		
		
		
		
		//m_pGameObj->AppendObject( new Draw2DObject("Build_1.bmp", Math::Vector2D(100, 200) ), "Film", true );
		#if defined( DEBUG_MAP_EDIT ) 
		
		#elif defined( DEBUG_MAP_SEE )
		
		#else
			m_p2DObj->AppendObject( new CSprite("title.png", Math::Vector2D( 0, 0 ) ), "Title", false );
			m_p2DObj->AppendObject( new CSprite("background.png", Math::Vector2D( 0, 0 ) ), "MissionSelect", false );
			m_p2DObj->AppendObject( new CSprite("chat.png", Math::Vector2D( 0, 0 ) ), "Chat", false );
			m_p2DObj->AppendObject( new CSprite("Result.png", Math::Vector2D( 0, 0 ) ), "Result", false );
			m_p2DObj->AppendObject( new CSprite("back.png", Math::Vector2D( 0, 0 ) ), "CalcScore", false );
			m_p2DObj->AppendObject( new CSprite("clear.dds", Math::Vector2D( 0, 0 ) ), "GameClear", false );
			m_p2DObj->AppendObject( new CSprite("failure.dds", Math::Vector2D( 0, 0 ) ), "GameFailure", false );
			
		#endif
		
		const char *pMiniCharaName[] =
		{
			"Mini_Mouse1",	
			"Mini_Mouse2",
			"Mini_Mouse3",
			"Mini_Bird1",
			"Mini_Bird2",
			"Mini_Bird3",
			"Mini_Bird4",
			"Mini_Bird5",
			"Mini_Bird6",
			
		};
		
		m_p2DObj->AppendObject( new CMiniMap("minimap3.png", Math::Vector2D( 0, 0) ), "MiniMap", true );
		m_p2DObj->AppendObject( new CSprite("came.dds", Math::Vector2D( 200, 200) ), "Mini_Player", true );
		m_p2DObj->AppendObject( new CSprite("mini_flag.dds", Math::Vector2D( 0, 0 ) ), "Mini_Camera", false );
		
		for( int i = 0;i < MINI_CHARA_MAX;++i )
		{
			m_p2DObj->AppendObject( new CSprite("mini_camera.png", Math::Vector2D( 0, 0 ) ), pMiniCharaName[i], false );
		}
			
		m_p2DObj->AppendObject( new CSprite("mini_target.dds", Math::Vector2D( 0, 0 ) ), "Mini_Target", false );
		
		
		m_p2DObj->AppendObject( new CSprite("pauseback.png", Math::Vector2D( 0, 0 ) ), "Pause", false );
		m_p2DObj->AppendObject( new CSprite("menu.dds", Math::Vector2D( 0, 0 ) ), "Menu", true );
		m_p2DObj->AppendObject( new CSprite("char.dds", Math::Vector2D( 170, 7 ) ), "CharaIcon", true );
		m_p2DObj->AppendObject( new CSprite("flag.dds", Math::Vector2D( 170, 7 ) ), "FlagIcon", true );
		m_p2DObj->AppendObject( new CSprite("film.dds", Math::Vector2D( 220, 7 ) ), "Film", true );
		m_p2DObj->AppendObject( new CSprite("bar.dds", Math::Vector2D( 310, 5 ) ), "Bar", true );
		m_p2DObj->AppendObject( new CSprite("systemmenu.dds", Math::Vector2D( 100, 200 ) ), "PopMenu", true );
		m_p2DObj->AppendObject( new CSprite("high.dds", Math::Vector2D( 590, 90 ) ), "HighScore", false );
		m_p2DObj->AppendObject( new CSprite("pointa.dds", Math::Vector2D( 645, 470 ) ), "Pointa", true );
		m_p2DObj->AppendObject( new CSprite("Cloud.tga", Math::Vector2D( 0, 0 ) ), "Cloud", true );
		
		#if defined( DEBUG_MAP_EDIT )
		
		#elif defined( DEBUG_MAP_SEE )
		
		#else
		
  			m_p2DObj->AppendObject( new CSprite("mission1.dds", Math::Vector2D( 270, 208 ) ), "MissionFont1", true );
			m_p2DObj->AppendObject( new CSprite("mission2.dds", Math::Vector2D( 115, 298 ) ), "MissionFont2", true );
			m_p2DObj->AppendObject( new CSprite("mission3.dds", Math::Vector2D( 452, 128 ) ), "MissionFont3", true );
			m_p2DObj->AppendObject( new CSprite("mission4.dds", Math::Vector2D( 65, 138 ) ), "MissionFont4", true );
			m_p2DObj->AppendObject( new CSprite("mission5.dds", Math::Vector2D( 426, 318 ) ), "MissionFont5", true );
			m_p2DObj->AppendObject( new CSprite("pin.dds", Math::Vector2D( 383, 142 ) ), "Pin", true );
			
			//m_p2DObj->AppendObject( new CSprite("pin2.dds", Math::Vector2D( 665, 490 ) ), "Pin2", true );
			m_p2DObj->AppendObject( new CSprite("train.png", Math::Vector2D( 280, 150) ), "Picture1", true );
			m_p2DObj->AppendObject( new CSprite("ameus.png", Math::Vector2D( 125, 240) ), "Picture2", true );
			m_p2DObj->AppendObject( new CSprite("oashisu.png", Math::Vector2D( 480, 70) ), "Picture3", true );
			m_p2DObj->AppendObject( new CSprite("funsui.png", Math::Vector2D( 75, 80 ) ), "Picture4", true );
			m_p2DObj->AppendObject( new CSprite("manta.png", Math::Vector2D( 440, 260 ) ), "Picture5", true );
			m_p2DObj->AppendObject( new CSprite("note.dds", Math::Vector2D( 322, 200 ) ), "Note", false );
			
			
		#endif
		
			m_p2DObj->AppendObject( new CSprite("ready.dds", Math::Vector2D( 159, 245 ) ), "Ready", true );
			m_p2DObj->AppendObject( new CSprite("go.dds", Math::Vector2D( 300, 238 ) ), "Go", true );
			m_p2DObj->AppendObject( new CSprite("nofilm.dds", Math::Vector2D( 300, 238 ) ), "NoFilm", false );
		
		
		m_p3DObj->AppendObject( new CDebugLine(), "DebugLine", true );
		
		//ifs.close();
		
		#if defined( DEBUG_MAP_EDIT ) 
		
		#elif defined( DEBUG_MAP_SEE )
		
		
		#elif defined( DEBUG_CHAT )
		
		#else
			CSprite *pPin = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pin") );
			
			pPin->SetDivnum( Math::Point2DI(2, 1) );
			
			CSprite3D *pEmotion = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("Emotion") );
			
			pEmotion->SetDivnum( Math::Point2DI( 4, 1 ) );
			
			CSprite3D *pFlagBal = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("FlagBalloon") );
			
			pFlagBal->SetDivnum( Math::Point2DI( 2, 1 ) );
			
		#endif
		
		
		
			//CSprite *pPin = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pin") );
			//
			//pPin->SetDivnum( Math::Point2DI(2, 1) );
			//
			//CSprite3D *pEmotion = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("Emotion") );
			//
			//pEmotion->SetDivnum( Math::Point2DI( 4, 1 ) );
			//
			//CSprite3D *pFlagBal = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("FlagBalloon") );
			//
			//pFlagBal->SetDivnum( Math::Point2DI( 2, 1 ) );
		
		
		
		//---------------------------------------------------------------------------
		//カメラ
		//---------------------------------------------------------------------------
		CCamera *objCamMain	= dynamic_cast<CCamera *>( m_pGameObj->FindObjectFromName("CamMain") );
		CCamera *objCamSub  = dynamic_cast<CCamera *>( m_pGameObj->FindObjectFromName("CamSub") );
		
		/*カメラデバイスのセット*/
		objCamMain->SetCamera( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
		objCamSub->SetCamera( m_pSceneMgr[S_SUB]->GetSceneMgr() );
		
		/*プロジェクションのセット*/
		objCamMain->SetProjection( 1.0f, 1000.0f, 45, m_pSceneMgr[S_MAIN]->GetRenderWidth(), m_pSceneMgr[S_MAIN]->GetRenderHeight() );
		
		objCamSub->SetProjection( 1.0f, 1000.0f, 45, m_pSceneMgr[S_SUB]->GetRenderWidth(), m_pSceneMgr[S_SUB]->GetRenderHeight() );
		
		
		//---------------------------------------------------------------------------
		//物理エンジン初期化
		//---------------------------------------------------------------------------
		//pDynamicsWorld = Dynamics::CreateWorld( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
		//
		///*ワールドにおける重力を設定*/
		//pDynamicsWorld->SetGravity( Math::Vector3D( 0, -GRAVITY, 0 ) );
		//
		///*剛体モデルの生成*/
		//m_p3DObj->CreateRigidModel( pDynamicsWorld );
		
		
		//---------------------------------------------------------------------------
		//モデル
		//---------------------------------------------------------------------------
		
		#if defined( DEBUG_CHAT )
		
		#else
			// ルートディレクトリに対して読み込むカレントディレクトリ設定
			m_pApp->GetFileMgr()->SetCurrentPath( "Model" );
			
			CField *objField = dynamic_cast<CField *>( m_p3DObj->FindObjectFromName("Field") );
			
			CDebugLine *pDebugLine = dynamic_cast<CDebugLine *>( m_p3DObj->FindObjectFromName("DebugLine") );

			/*読み込み*/
			m_p3DObj->Load( m_pApp->GetRenderer() );
			
			
			m_pApp->GetFileMgr()->SetCurrentPath("Shader");
			
			CPlayer *objPlayer = dynamic_cast<CPlayer *>( pScene->Get3DObject()->FindObjectFromName("Player") );
			
			pDebugLine->CreateLine( m_pApp->GetRenderer() );
			
			
			
			//objPlayer->LoadShader( m_pGame->GetRenderer(), "UserShader.fx" );
			pDebugLine->CreateActor( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
					
		#endif
	
		#if defined( DEBUG ) | (_DEBUG )
		
			objField->SetCollisionLine( pDebugLine->GetLine() );
		
		
		#elif defined( DEBUG_CHAT )
		
		
		#endif
		
		//pDebugLine->CreateActor( m_pSceneMgr[S_SUB]->GetSceneMgr() );

		#if defined( DEBUG_CHAT )
		
		#else
			/*アクターの生成*/
			for( int numScreen = 0;numScreen < S_MAX;++numScreen )
			{	
				m_p3DObj->CreateActor( numScreen, m_pSceneMgr[numScreen]->GetSceneMgr() );
				
				objField->CreateActor( numScreen, m_pSceneMgr[numScreen]->GetSceneMgr() );
			}
			
		#endif
		
		//---------------------------------------------------------------------------
		//サウンド
		//---------------------------------------------------------------------------
		m_pApp->GetFileMgr()->SetCurrentPath("Sound");
		
		/*サウンドの読み込み*/
		m_pSoundObj->LoadSound( m_pApp->GetCore() );
		
		//---------------------------------------------------------------------------
		//テクスチャ
		//---------------------------------------------------------------------------
		m_pApp->GetFileMgr()->SetCurrentPath("Texture");
		
		/*テクスチャの読み込み*/
		m_p2DObj->Load( m_pApp->GetRenderer() );
		
		CSprite *SkySpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Cloud") );
		
		for( int scenenum = 0;scenenum < S_MAX;++scenenum )
		{
			m_pSceneMgr[scenenum]->CreateSkyDoom( SkySpr->GetTexture(), m_pApp->GetRenderer() );
		}
		
		pScene->Get2DObject()->RemoveObject( SkySpr );
			
		//---------------------------------------------------------------------------
		//フォント
		//---------------------------------------------------------------------------
		m_pApp->GetFileMgr()->SetCurrentPath("Font");
		
		CFontSprite *pFontSpr = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("TitleFont") );
		CFontSprite *pCommonFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("CommonFont") );
		CFontSprite *pMissionFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("MissionFont") );
		CFontSprite *pMenuFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("MenuFont") );
		CFontSprite *pChatFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("ChatFont") );
		CFontSprite *pNumFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("NumFont") );
		CFontSprite *pMiContFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("ContentFont") );
		CFontSprite *pMiContFont2 = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("ContentFont2") );
		CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( m_pGameObj->FindObjectFromName("ExplainFont") );
		
		pFontSpr->Load( m_pApp->GetRenderer() );
		pCommonFont->Load( m_pApp->GetRenderer() );
		pMissionFont->Load( m_pApp->GetRenderer() );
		pMenuFont->Load( m_pApp->GetRenderer() );
		pChatFont->Load( m_pApp->GetRenderer() );
		pNumFont->Load( m_pApp->GetRenderer() );
		pMiContFont->Load( m_pApp->GetRenderer() );
		pMiContFont2->Load( m_pApp->GetRenderer() );
		pExpFont->Load( m_pApp->GetRenderer() );
		
		//---------------------------------------------------------------------------
		//テキスト読み込み
		//---------------------------------------------------------------------------
		pResFile = 	m_pApp->GetFileMgr()->FileOpen("Text.txt");
		
		Sint32 FileSize = pResFile->GetFileSize();
		
		char *pTextBuff = new char[FileSize + 1];
		
		pResFile->Read( pTextBuff, FileSize );
		
		pTextBuff[FileSize] = '\0';
		
		pResFile->Release();
		
		pFontSpr->SetDrawString("PUSH START");
		
		CSprite *objPopMenu	= dynamic_cast<CSprite *>( m_p2DObj->FindObjectFromName("PopMenu") );
		
		m_pGameObj->AppendObject( new CMenu( pMenuFont, objPopMenu ), "PopMenu", true );
		
		//---------------------------------------------------------------------------
		//ミッションの追加
		//---------------------------------------------------------------------------
		m_pApp->GetFileMgr()->SetCurrentPath("CSV");
		
		pResFile = m_pApp->GetFileMgr()->FileOpen("mission.csv");
		
		std::ifstream ifsMission( pResFile->GetNamePointer() );
		
		SAFE_RELEASE( pResFile );
		
		char MissionTemp[256];
		
		ifsMission.getline( MissionTemp, 256 );
		
		m_pApp->GetFileMgr()->SetCurrentPath("Font");
		
		
		//ifs.open("mission.csv");
		
		while( !ifsMission.eof() )
		{
			char Temp[20];
			
			static int count = 0;
			
			MissionData datMission;
			char TempMissionName[256];
			char TempTargetName[256];
			char TempChat[1024];
			
			
			sprintf( Temp, "Mission%d.txt", count+1);
			
			pResFile = 	m_pApp->GetFileMgr()->FileOpen(Temp);
			
			ifstream ifs( pResFile->GetNamePointer() );
			
			SAFE_RELEASE(pResFile);
			
			#if defined (DEBUG) | (_DEBUG)
				//ofstream out( Temp, ios::out );
				//
				////while( *pTextBuff != '\0')
				////{
				////	if( *pTextBuff != '\n' )
				////	{
				////		out << pTextBuff;
				////	}
				////	
				////	pTextBuff += 1;
				////	
				////	
				////}
				//
				//
				//out.close();
			
			#endif
			
			while( !ifs.eof() )
			{	
				ifs >> TempChat;
				datMission.m_vecChat.push_back( TempChat );
			}
			
			ifs.close();
			
			
			sprintf( Temp, "MissionContent%d.txt", count+1 );
			
			pResFile = 	m_pApp->GetFileMgr()->FileOpen(Temp);
			
			ifstream ifsContent( pResFile->GetNamePointer() );
			
			char TempMiCont[256] = "";
			
			//ifsContent.read( TempMiCont, pResFile->GetFileSize() );
			
			SAFE_RELEASE( pResFile );
			
			while( !ifsContent.eof() )
			{
				ifsContent >> TempMiCont;
				datMission.m_vecMissionContent.push_back( TempMiCont );
			}
			
			ifsContent.close();
			
			ifsMission >> TempMissionName >> TempTargetName >> datMission.m_ClearPoint >> datMission.m_FilmNum 
			>> datMission.m_LimitTime.Min >> datMission.m_LimitTime.Sec >> datMission.m_TimeBorder.Min >> datMission.m_TimeBorder.Sec
			>> datMission.m_TargetPosMin >> datMission.m_TargetPosMax >> datMission.m_DistanceMin >> datMission.m_DistanceMax ;
			
			datMission.m_MissionName = TempMissionName;
			datMission.m_TargetName = TempTargetName;
			
			CCharacter *objFlag	  = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
			
			float Scale = 4.0f;
			objFlag->SetScale( Math::Vector3D( Scale, Scale, Scale ) );
			
			sprintf( Temp, "MissionFont%d", count+1 );
			
			datMission.m_pFontSpr = dynamic_cast<CSprite *>( m_p2DObj->FindObjectFromName(Temp) );		
			
			sprintf( Temp, "Picture%d", count+1 );
			
			datMission.m_pPhotoSpr = dynamic_cast<CSprite *>( m_p2DObj->FindObjectFromName(Temp) );	
			
			m_pMissionMgr->AppendMission( count, new CMission( dynamic_cast<CDraw3DObject *>( m_p3DObj->FindObjectFromName( datMission.m_TargetName ) ), datMission ) );
			
			count++;
		}
			
		ifsMission.close();
			
		#if defined( DEBUG_MAP_EDIT )
		
		#elif defined( DEBUG_MAP_SEE)
		
		#else
			
		#endif
		
		//-----------------------------------------------------------------
		// 変更しないステート
		//-----------------------------------------------------------------
		m_pApp->SetTextureFilter();
		
		m_IsFirstBoot = false;
	}
	
	
	return true;
	
}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CScene::Exec(CScene *pScene)
{
	Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CSprite *pSpr = dynamic_cast<CSprite *>( m_p2DObj->FindObjectFromName("Loading") );
	
	pSpr->SetDivnum( Math::Point2DI(6, 1) );
	
	pScene->GetAppDevice()->GetRenderer()->Clear();
	
	pScene->GetAppDevice()->GetRenderer()->Begin();
	
	pSpr->Rendering();
	
	//pScene->GetAppDevice()->GetRenderer()->DebugPrint( Math::Point2DI( 400, 300 ), CColor(255, 255, 255 ), "Npw Loading" );
	
	pScene->GetAppDevice()->GetRenderer()->End();

	pSpr->DrawAnimation( 6, 0 );
	
	/*ロード終わってない*/
	if( !pScene->GetLoadEndFlag() )
	{	
		static string Str = "Now Loading";
		
		static int count = 0;
		
		count ++;
		
		if( count % 10 == 0 )
		{
			Str += ".";
		}
		
		if( count >= 40 )
		{
			count = 0;
			Str = "Now Loading";
		}
		
		pRender->DrawText( Math::Point2DI( 590, 520 ), CColor(255, 255, 255 ), Str.c_str() );
		
		
	}
	
	/*ロード終了*/
	if( pScene->GetLoadEndFlag() )
	{
		pSpr->SetVisibleFlag( false );
		
		m_p3DObj->Init();
		
		CCamera *objCamMain	= dynamic_cast<CCamera *>( m_pGameObj->FindObjectFromName("CamMain") );
		
		objCamMain->Init();
		
		pSpr->Move();
		
		/*キャラが画面外にいったら、次のシーンに*/
		if( pSpr->GetPosition().x <= -100 )
		{
			#if defined( DEBUG_MAP_EDIT ) 
			
				m_eNextScene = SCENE_GAMEMAIN;
			
			
			#elif defined( DEBUG_MAP_SEE )
			
				m_eNextScene = SCENE_DEMO;
				
			#elif defined( DEBUG_CHAT )
			
				m_eNextScene = SCENE_CHAT;
				
			#endif
			
			pScene->SetSceneState( STATE_STANDBY );
			
			pScene->ChangeScene( m_eNextScene );
		}
		
	}
	
}

//=============================================================================
//シーン状態による処理
//=============================================================================
void CScene::SceneStateExec()
{
	if( m_eSceneState == STATE_FADEIN )
	{
		FadeIn();
	}
	
	if( m_eSceneState == STATE_FADEOUT )
	{
		FadeOut();
	}
	
}

//=============================================================================
//時間計測
//=============================================================================
void CScene::TimeCount()
{
	if( ++m_CurrentTime.MinSec == 60 )
	{
		m_CurrentTime.MinSec = 0;
		m_CurrentTime.Sec++;
	}
	
	if( m_CurrentTime.Sec == 60 )
	{
		m_CurrentTime.Sec = 0;
		m_CurrentTime.Min++;
	}
	
	if( m_CurrentTime.Min == 60 )
	{	
		m_CurrentTime.Min = 0;
		m_CurrentTime.Hour++;
	}

}

//=============================================================================
//フェードイン
//=============================================================================
void CScene::FadeIn( )
{
	static Sint32 Alphacount = 0;
	
	static Sint32 Alpha	= 255;
	
	Alphacount++;
	
	Alpha = Interpolation::Flat(255, 0, toI(m_fFadeTime), Alphacount);

	m_pApp->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	m_pApp->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( m_pApp->GetScreenWidth() ),toF(  m_pApp->GetScreenHeight() ) ), CColor( 255, 255, 255, Alpha ) );
	
	if( Alpha <= 0 )
	{
		Alpha = 255;
		Alphacount = 0;
		
		ChangeScene( m_eNextScene );
		
		m_eSceneState = STATE_STANDBY;
		
		//pScene->Get2DObject()->RemoveObject( pTitle );
	}
	
}

//=============================================================================
//フェードアウト
//=============================================================================
void CScene::FadeOut( )
{
	static Sint32 Alphacount = 0;
	
	static Sint32 Alpha	= 0;
	
	Alphacount++;
	
	Alpha = Interpolation::Flat(0, 255, toI(m_fFadeTime), Alphacount);

	m_pApp->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	m_pApp->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( m_pApp->GetScreenWidth() ),toF(  m_pApp->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
	
	if( Alpha >= 255 )
	{
		Alpha = 0;
		Alphacount = 0;

		ChangeScene( m_eNextScene );
		
		m_pApp->GetRenderer()->SetDrawTextFont("MS ゴシック", m_FontSize );		
		
		m_eSceneState = STATE_STANDBY;
	}
	
	
	
}



//=============================================================================
//シーンの移行
//=============================================================================
//[input]
//	scene:設定するシーン
//=============================================================================
void CScene::ChangeScene( eSceneType scene )
{
	m_eNowScene = scene;
}

//=============================================================================
//次のシーンの設定
//=============================================================================
//[input]
//	scene:設定するシーン
//=============================================================================
void CScene::SetNextScene( eSceneType scene )
{
	m_eNextScene = scene;
}


