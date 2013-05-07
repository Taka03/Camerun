//*============================================================================
//SceneGameOver.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameOver.h"
#include "player.h"
#include "FontSprite.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneGameOver::CSceneGameOver(void)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameOver::~CSceneGameOver(void)
{

}

//=============================================================================
//処理
//=============================================================================
void CSceneGameOver::Exec()
{
	///*ジョイパッドの生成*/
	//m_pJoyPad->CreateDevice( m_pGame->GetCore() );
	//
	//m_pKeyboard = m_pGame->GetCore()->GetKeyboard();
	//
	////-----------------------------------------------------------------
	//// シーン
	////-----------------------------------------------------------------
	//m_pSceneMgr[S_MAIN]->SetRenderSize( m_pGame->GetScreenWidth(), m_pGame->GetScreenHeight() );
	//m_pSceneMgr[S_SUB]->SetRenderSize( 240, 180 );
	//
	//for( int i = 0;i < S_MAX;++i )
	//{
	//	m_pSceneMgr[i]->CreateDevice( m_pGame->GetRenderer() );
	//}
	//
	//m_pSceneMgr[S_MAIN]->SetInitParameter( false );
	//m_pSceneMgr[S_SUB]->SetInitParameter( true );
	//
	//for( int photonum = 0;photonum < PHOTONUM;++photonum )
	//{
	//	pPhoto[photonum]->CreateTexture( m_pGame->GetRenderer(), m_pSceneMgr[S_SUB]->GetRenderWidth(), m_pSceneMgr[S_SUB]->GetRenderHeight() );
	//}
	//
	////-----------------------------------------------------------------
	////オブジェクトの追加
	////-----------------------------------------------------------------
	//
	//m_p3DObj->AppendObject( new CField("Map.stm"), "Building", true );
	//
	////p3DObj->AppendObject( new CField("ground.stm"), "Ground", true );
	//
	//m_p3DObj->AppendObject( new CPlayer("Camerun.smf"), "Player", true ); 
	//m_p3DObj->AppendObject( new CEnemy("train1.smf", Math::Vector3D(0.0f, 0.0f, -40.0f) ), "Train", true );
	////p3DObj->AppendObject( new CCharacter("soldier.smf", Math::Vector3D(1.0f, 1.0f, 0.0f) ), "Soldier", true );
	//m_p3DObj->AppendObject( new CCamObject("camera.smf"), "CamObj", true );
	//m_p3DObj->AppendObject( new CCharacter("flag.smf", Math::Vector3D(0.0f, 4.0f, 0.0f) ), "Flag", true );
	//
	//m_pSoundObj->AppendObject( new CSoundEffect("shutter.WAV"), "Shutter", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("flag.WAV"), "Flag", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("run.WAV"), "Run", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("train.WAV"), "STrain", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("change.WAV"), "Change", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("enter.WAV"), "Enter", true );
	//m_pSoundObj->AppendObject( new CSoundEffect("collision.WAV"), "Collision", true );
	//
	//
	//m_pSoundObj->AppendObject( new CBGM("bgm.ogg"), "BGM", true );
	//
	//
	//m_pObj->AppendObject( new CCamera(), "CamMain", true );
	//m_pObj->AppendObject( new CCamera(), "CamSub", true );
	//
	////m_pObj->AppendObject( new Draw2DObject("Build_1.bmp", Math::Vector2D(100, 200) ), "Film", true );
	//m_p2DObj->AppendObject( new CSprite("title.png", Math::Vector2D( 0, 0 ) ), "Title", true );
	//m_p2DObj->AppendObject( new CSprite("menu.dds", Math::Vector2D( 0, 0 ) ), "Menu", true );
	//m_p2DObj->AppendObject( new CSprite("char.dds", Math::Vector2D( 170, 7 ) ), "CharaIcon", true );
	//m_p2DObj->AppendObject( new CSprite("flag.dds", Math::Vector2D( 170, 7 ) ), "FlagIcon", true );
	//m_p2DObj->AppendObject( new CSprite("film.dds", Math::Vector2D( 220, 7 ) ), "Film", true );
	//m_p2DObj->AppendObject( new CSprite("bar.dds", Math::Vector2D( 310, 5 ) ), "Bar", true );
	//m_pObj->AppendObject( new CFontSprite("font.sff", Math::Vector2D( 200, 400 ) ), "TitleFont", true );
	//m_pObj->AppendObject( new CFontSprite("font2.sff", Math::Vector2D( 200, 400 ) ), "CommonFont", true );
	//m_pObj->AppendObject( new CFontSprite("font2.sff", Math::Vector2D( 430, 13) ), "MissionFont", true );
	//
	////---------------------------------------------------------------------------
	////カメラ
	////---------------------------------------------------------------------------
	//CCamera *objCamMain	= dynamic_cast<CCamera *>( m_pObj->FindObjectFromName("CamMain") );
	//CCamera *objCamSub  = dynamic_cast<CCamera *>( m_pObj->FindObjectFromName("CamSub") );
	//
	///*カメラデバイスのセット*/
	//objCamMain->SetCamera( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
	//objCamSub->SetCamera( m_pSceneMgr[S_SUB]->GetSceneMgr() );
	//
	///*プロジェクションのセット*/
	//objCamMain->SetProjection( 1.0f, 4096.0f, 45, m_pSceneMgr[S_MAIN]->GetRenderWidth(), m_pSceneMgr[S_MAIN]->GetRenderHeight() );
	//
	//objCamSub->SetProjection( 1.0f, 4096.0f, 45, m_pSceneMgr[S_SUB]->GetRenderWidth(), m_pSceneMgr[S_SUB]->GetRenderHeight() );
	//
	////---------------------------------------------------------------------------
	////物理エンジン初期化
	////---------------------------------------------------------------------------
	//pDynamicsWorld = Dynamics::CreateWorld( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
	//
	///*ワールドにおける重力を設定*/
	//pDynamicsWorld->SetGravity( Math::Vector3D( 0, -GRAVITY, 0 ) );
	//
	///*剛体モデルの生成*/
	//p3DObj->CreateRigidModel( pDynamicsWorld );
	//
	//
	////---------------------------------------------------------------------------
	////モデル
	////---------------------------------------------------------------------------
	//
	//// ルートディレクトリに対して読み込むカレントディレクトリ設定
	//m_pGame->GetFileMgr()->SetCurrentPath( "Model" );

	///*読み込み*/
	//p3DObj->Load( m_pGame->GetRenderer() );

	///*アクターの生成*/
	//for( int numScreen = 0;numScreen < S_MAX;++numScreen )
	//{	
	//	p3DObj->CreateActor( numScreen, m_pSceneMgr[numScreen]->GetSceneMgr() );
	//}
	//
	//for( int scenenum = 0;scenenum < S_MAX;++scenenum )
	//{
	//	m_pSceneMgr[scenenum]->CreateSkyDoom( m_pGame->GetRenderer() );
	//}
	//
	////---------------------------------------------------------------------------
	////サウンド
	////---------------------------------------------------------------------------
	//m_pGame->GetFileMgr()->SetCurrentPath("Sound");
	//
	///*サウンドの読み込み*/
	//m_pSoundObj->LoadSound( m_pGame->GetCore() );
	//
	////---------------------------------------------------------------------------
	////テクスチャ
	////---------------------------------------------------------------------------
	//m_pGame->GetFileMgr()->SetCurrentPath("Texture");
	//
	///*テクスチャの読み込み*/
	//m_p2DObj->Load( m_pGame->GetRenderer() );
	//
	////---------------------------------------------------------------------------
	////フォント
	////---------------------------------------------------------------------------
	//m_pGame->GetFileMgr()->SetCurrentPath("Font");
	//
	//CFontSprite *pFontSpr = dynamic_cast<CFontSprite *>( m_pObj->FindObjectFromName("TitleFont") );
	//CFontSprite *pCommonFont = dynamic_cast<CFontSprite *>( m_pObj->FindObjectFromName("CommonFont") );
	//CFontSprite *pMissionFont = dynamic_cast<CFontSprite *>( m_pObj->FindObjectFromName("MissionFont") );
	//
	//pFontSpr->Load( m_pGame->GetRenderer() );
	//pCommonFont->Load( m_pGame->GetRenderer() );
	//pMissionFont->Load( m_pGame->GetRenderer() );
	//
	//pFontSpr->SetDrawString("PUSH START");
	//pMissionFont->SetDrawString("写真を撮りまくれ!!");
	//
	////-----------------------------------------------------------------
	//// 変更しないステート
	////-----------------------------------------------------------------
	//m_pGame->SetTextureFilter();

	////pLine = m_pGame->GetRenderer()->CreateLine3D( 1000, true );
	////
	////pActorLine = m_pSceneMgr[S_MAIN]->GetSceneMgr()->CreateActor( pLine );

}
