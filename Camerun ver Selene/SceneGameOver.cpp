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
//�R���X�g���N�^
//=============================================================================
CSceneGameOver::CSceneGameOver(void)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneGameOver::~CSceneGameOver(void)
{

}

//=============================================================================
//����
//=============================================================================
void CSceneGameOver::Exec()
{
	///*�W���C�p�b�h�̐���*/
	//m_pJoyPad->CreateDevice( m_pGame->GetCore() );
	//
	//m_pKeyboard = m_pGame->GetCore()->GetKeyboard();
	//
	////-----------------------------------------------------------------
	//// �V�[��
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
	////�I�u�W�F�N�g�̒ǉ�
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
	////�J����
	////---------------------------------------------------------------------------
	//CCamera *objCamMain	= dynamic_cast<CCamera *>( m_pObj->FindObjectFromName("CamMain") );
	//CCamera *objCamSub  = dynamic_cast<CCamera *>( m_pObj->FindObjectFromName("CamSub") );
	//
	///*�J�����f�o�C�X�̃Z�b�g*/
	//objCamMain->SetCamera( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
	//objCamSub->SetCamera( m_pSceneMgr[S_SUB]->GetSceneMgr() );
	//
	///*�v���W�F�N�V�����̃Z�b�g*/
	//objCamMain->SetProjection( 1.0f, 4096.0f, 45, m_pSceneMgr[S_MAIN]->GetRenderWidth(), m_pSceneMgr[S_MAIN]->GetRenderHeight() );
	//
	//objCamSub->SetProjection( 1.0f, 4096.0f, 45, m_pSceneMgr[S_SUB]->GetRenderWidth(), m_pSceneMgr[S_SUB]->GetRenderHeight() );
	//
	////---------------------------------------------------------------------------
	////�����G���W��������
	////---------------------------------------------------------------------------
	//pDynamicsWorld = Dynamics::CreateWorld( m_pSceneMgr[S_MAIN]->GetSceneMgr() );
	//
	///*���[���h�ɂ�����d�͂�ݒ�*/
	//pDynamicsWorld->SetGravity( Math::Vector3D( 0, -GRAVITY, 0 ) );
	//
	///*���̃��f���̐���*/
	//p3DObj->CreateRigidModel( pDynamicsWorld );
	//
	//
	////---------------------------------------------------------------------------
	////���f��
	////---------------------------------------------------------------------------
	//
	//// ���[�g�f�B���N�g���ɑ΂��ēǂݍ��ރJ�����g�f�B���N�g���ݒ�
	//m_pGame->GetFileMgr()->SetCurrentPath( "Model" );

	///*�ǂݍ���*/
	//p3DObj->Load( m_pGame->GetRenderer() );

	///*�A�N�^�[�̐���*/
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
	////�T�E���h
	////---------------------------------------------------------------------------
	//m_pGame->GetFileMgr()->SetCurrentPath("Sound");
	//
	///*�T�E���h�̓ǂݍ���*/
	//m_pSoundObj->LoadSound( m_pGame->GetCore() );
	//
	////---------------------------------------------------------------------------
	////�e�N�X�`��
	////---------------------------------------------------------------------------
	//m_pGame->GetFileMgr()->SetCurrentPath("Texture");
	//
	///*�e�N�X�`���̓ǂݍ���*/
	//m_p2DObj->Load( m_pGame->GetRenderer() );
	//
	////---------------------------------------------------------------------------
	////�t�H���g
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
	//pMissionFont->SetDrawString("�ʐ^���B��܂���!!");
	//
	////-----------------------------------------------------------------
	//// �ύX���Ȃ��X�e�[�g
	////-----------------------------------------------------------------
	//m_pGame->SetTextureFilter();

	////pLine = m_pGame->GetRenderer()->CreateLine3D( 1000, true );
	////
	////pActorLine = m_pSceneMgr[S_MAIN]->GetSceneMgr()->CreateActor( pLine );

}
