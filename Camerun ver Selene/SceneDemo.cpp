//*============================================================================
//SceneDemo.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneDemo.h"
#include "EnemyAmeus.h"
#include "EnemyMouse.h"
#include "EnemyBird.h"
#include "EnemyManta.h"
#include <math.h>
#include <iostream>
#include <fstream>


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneDemo::CSceneDemo( )
{
	m_vOldPos.Set( 0, 0, 0 );
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneDemo::~CSceneDemo(void)
{
	//SAFE_DELETE( pScene );
}

//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
void CSceneDemo::Exec( CScene *pScene )
{
	CFontSprite *pChatFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ChatFont") );
	
	pChatFont->SetRefCount( 0 );
	pChatFont->SetStrCount( 1 );
	pChatFont->SetTextEndFlag( false );
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );//CMissionTutorial( dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ) );
	
	CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
	
	CField *objField = dynamic_cast<CField *>( pScene->Get3DObject()->FindObjectFromName("Field") );
	
	CPlayer *objPlayer = dynamic_cast<CPlayer *>( pScene->Get3DObject()->FindObjectFromName("Player") );
	CTrain *objTrain = dynamic_cast<CTrain *>( pScene->Get3DObject()->FindObjectFromName("Train") );
	
	CSoundEffect *sndTrain	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("STrain") );
	CSoundEffect *sndSetFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Flag") );
	CSoundEffect *sndRecallFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("RecallFlag") );
	
	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("GameBGM") );
	CBGM *pChatMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("ChatBGM") );
	
	pChatMusic->GetBGMDevice()->Stop() ;
	
	CCharacter *objTarget	= dynamic_cast<CCharacter *>( pMission->GetTarget() );//dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") );

	CCharacter *objStar = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Star") );
	
	CSprite *objReady = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Ready") );
	CSprite *objGo = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Go") );
	
	CParticle *objRunEffect[RUN_EFFECT_NUM];
	
	for( int i = 0;i < RUN_EFFECT_NUM;++i )
	{	
		char Temp[12];
		
		sprintf( Temp, "RunEffect%d", i);
		
		objRunEffect[i] = dynamic_cast<CParticle *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	
	for	( int i = 0;i < RUN_EFFECT_NUM;++i )
	{
		objRunEffect[i]->SetRenderDevice( pScene->GetAppDevice()->GetRenderer() );
	}
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{	
		pGameMusic->GetBGMDevice()->Play( );
		
	}
	
	if( pScene->GetSceneState() == STATE_FADEOUT )
	{
		objReady->SetVisibleFlag( false );
	}
	
	/*�v���C���[�p�ɃR���g���[���[�f�o�C�X���擾*/
	objPlayer->SetController( pScene->GetJoyPad()->GetController(), pScene->GetJoyPad()->GetJoyStick() );
	
	CCamObject *objCamObj = dynamic_cast<CCamObject *>( pScene->Get3DObject()->FindObjectFromName("CamObj") );
	CCharacter *objFlag	  = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
	
	/*���֐����l���āA�v���C���[�ɖ��ߍ���*/
	objPlayer->GetCamObject( objCamObj );
	//objPlayer->GetFlagObject( objFlag );
	
	/*�S�L�����ɑ΂��ē����蔻��f�[�^���쐬*/
	pScene->Get3DObject()->CreateCollision();
	
	//-------------------------------------------------------------------------
	//�`��J�n
	//-------------------------------------------------------------------------
	pScene->GetAppDevice()->GetRenderer()->Begin();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// �V�[���}�l�[�W���[�̓��e�����ۂɃ����_�����O
	/////////////////////////////////////////////////////////////////////////////////////////////
	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Rendering( false );
	
	if( objReady->GetVisibleFlag() )
	{	
		objReady->Rendering();
	}
	
	else if( objGo->GetVisibleFlag() )
	{
		objGo->Rendering();
	}
	

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
	
	
	/*�H����B��̂Ƃ��̂݃A���E�X��\��������*/
	if( pScene->GetMissionMgr()->GetMissionNo() == 1 )
	{
		objAmeus->SetVisibleFlag( true );
	}
	
	else
	{
		objAmeus->SetVisibleFlag( false );
	}
	
	/*�}���^���B��̂Ƃ��̂݃}���^��\��������*/
	if( pScene->GetMissionMgr()->GetMissionNo() == 4 )
	{
		objManta->SetVisibleFlag( true );
	}
	
	else
	{
		objManta->SetVisibleFlag( false );
	}
	
	/*�C��G�t�F�N�g�̓���*/
	for( int i = 0;i < BIRD_MAX;++i )
	{
		objBird[i]->GetStunEffect( objStar );
	}
	
	for( int i = 0;i < MOUSE_MAX;++i )
	{
		objMouse[i]->GetStunEffect( objStar );
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
	
	/*�`��I��*/
	pScene->GetAppDevice()->GetRenderer()->End();
	
	objPlayer->Move( objCamMain, objRunEffect );
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// �V�[�����\�z
	/////////////////////////////////////////////////////////////////////////////////////////////


	//--------------------------------------------------------------------------
	//���C�����
	//--------------------------------------------------------------------------
	// �V�[����񃊃Z�b�g
	//   Scene::ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ��������������܂��B
		
	/*�`��ʒu�̐ݒ�*/
	pScene->GetSceneMgr(S_MAIN)->SetRenderPos( Math::Vector2D(0, 0) );
	
	/*�p�����[�^�̐ݒ�*/
	pScene->GetSceneMgr(S_MAIN)->SetParameter();

	// ���s����
	//   �V�[���ɑ΂��ĕ��s������ݒ肵�܂��B
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Directional(
		Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ���C�g�̕���
		Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ���C�g�̐F

	// �A���r�G���g
	// �������C�e�B���O���s���Ă���̂ŁA�V���ƒn�\�̏Ƃ�Ԃ��̐F��ݒ肵�܂��B
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Ambient(
		Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// �V���̐F
		Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// �n�\�̐F

	// �J�����̒����ڕW
	objCamMain->SetTargetPos( objPlayer->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f) );

	/*�g�����X�t�H�[���̐ݒ�*/
	objCamMain->SetTransformDemo();
	
	const int MAX_KEY = 4;
	
	//Math::Animation AnimX(MAX_KEY);
	//Math::Animation AnimY(MAX_KEY);
	//Math::Animation AnimZ(MAX_KEY);
	//
	//for( int i = 0;i < MAX_KEY;++i )
	//{	
	//	AnimX.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	AnimY.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	AnimZ.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	
	//}
	
	static float fAnimTime = 0.0f;
	
	fAnimTime += 1.0f / 60.0f;
	
	// �_�̈ړ�
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );
	
	//objCamMain->SetPosition( Math::Vector3D( AnimX.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ),
											 //AnimY.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ),
											 //AnimZ.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ) ) );											 
											 
	if( fAnimTime >= 40.0f )
	{
		fAnimTime = 0.0f;
	}											 
											 

	objCamMain->SetRotate( Math::Vector3D( objPlayer->GetRotate().y,  DEG_TO_ANGLE( 90 ) -objPlayer->GetRotate().x , objCamMain->GetRotate().z ) );
	
	
	//------------------------------------------------
	//�n�ʃ`�F�b�N
	//------------------------------------------------
	
	/*�}�b�v�Ƃ̔���*/
	if( objPlayer->GroundCheck( objField ) )
	{
		
	}

	pScene->Get3DObject()->SetActorIndex(S_MAIN);

	pScene->Get3DObject()->MoveExec();
	
	/*����*/
	pScene->Get3DObject()->Exec();
	
	objReady->Exec();
	objGo->Exec();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// �V�[���ւ̃����_�����O���N�G�X�g
	/////////////////////////////////////////////////////////////////////////////////////////////

	// �V�[���Ǘ�
	//   Scene::ISceneManager�C���^�[�t�F�C�X���g�����V�[���Ǘ����J�n���܂��B
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Begin( false );
	
	// �X�J�C�h�[���̃����_�����O
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_Rendering();

	objField->Rendering(S_MAIN);
	
	//�����_�����O
	pScene->Get3DObject()->Rendering(S_MAIN);
	
	// �V�[���Ǘ����I��
	//   �����܂łō\�z���ꂽ�V�[���������Ɏ��ۂɕ`��p�f�[�^�̍\�z���s���܂��B
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->End();
	
	static int count = 0;
	
	count ++;
	
	if( count > 0 && count <= 60 )
	{
		//objReady->SetVisibleFlag( true );
	}
	
	if( count > 60 )
	{
		objReady->SetVisibleFlag( false );
		objGo->SetVisibleFlag( true );
	}
	
	pScene->SetNextScene( SCENE_GAMEMAIN );
	
	if( count >= 120 )
	{	
		objReady->SetVisibleFlag( false );
		objGo->SetVisibleFlag( false );
		
		pScene->SetFadeTime( 10.0f );
		
		pScene->SetSceneState( STATE_FADEOUT );
		
		count = 0;
		
		
	}
		

}

