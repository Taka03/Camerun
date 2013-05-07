//*============================================================================
//GameSceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "GameSceneManager.h"
#include "SceneGameMain.h"
#include "SceneGameTitle.h"
#include "SceneGameResult.h"
#include "SceneEffect.h"
#include "SceneMissionSelect.h"
#include "ScenePhoto.h"

//=============================================================================
//variable
//=============================================================================


//static void CollisionCallback( Dynamics::ISimulationWorld *pDynamicsWorld, Dynamics::IRigidBody *pIn1, 
//							   Dynamics::IRigidBody *pIn2, Dynamics::IContactPoint *pContact );
//	
//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
CGameSceneManager::CGameSceneManager( CScene *pScene )
{
	m_pScene = pScene;
	
	m_pFiberCtrl = pScene->GetAppDevice()->GetCore()->CreateFiberController(1);

	m_pFiberCtrl->Start();	
	
	CFiber *pFiber = new CFiber( m_pFiberCtrl, pScene );
	
	m_pFiberCtrl->Create( 0, pFiber );
	
	SAFE_DELETE( pFiber );
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGameSceneManager::~CGameSceneManager()
{
	SAFE_DELETE( m_pFiberCtrl );
}

//=============================================================================
//����
//=============================================================================
void CGameSceneManager::Exec()
{
	list<SceneList>::iterator it;
	
	for( it = m_SceneList.begin(); it != m_SceneList.end();it++ )
	{
		if( it->m_eSceneType == m_pScene->GetNowScene() )
		{
			it->m_pScene->Exec( m_pScene );
		}
	}
	
}

//=============================================================================
//�V�[���̒ǉ�
//=============================================================================
//[input]
//	Type:�V�[���^�C�v
//	pScene:�ǉ�����V�[��
//=============================================================================
void CGameSceneManager::AddScene( eSceneType Type, CScene *pScene)
{
	SceneList liScene;
	
	liScene.m_eSceneType = Type;
	liScene.m_pScene = pScene;
	
	m_SceneList.push_back( liScene );
}

//=============================================================================
//�V�[���̍폜
//=============================================================================
//[input]
//	pScene:�폜����V�[��
//=============================================================================
void CGameSceneManager::RemoveScene(CScene *pScene)
{

}

//=============================================================================
//�V�[���̎Q��
//=============================================================================
//[input]
//	Type:�V�[���^�C�v
//=============================================================================
CScene *CGameSceneManager::FindScene( eSceneType Type )
{
	list<SceneList>::iterator it;
	
	for( it = m_SceneList.begin(); it != m_SceneList.end();it++ )
	{
		if( it->m_eSceneType == Type )
		{
			return it->m_pScene;
		}
	}
	
	return NULL;
}


//void CollisionCallback( Dynamics::ISimulationWorld *pDynamicsWorld, Dynamics::IRigidBody *pIn1, Dynamics::IRigidBody *pIn2, Dynamics::IContactPoint *pContact )
//{
//	// �Փ˓X�̐����擾
//	Sint32 Count = pContact->GetCount();
//	
//	// �Փˏ���
//	for ( Sint32 i = 0; i < Count; i++ )
//	{
//		// �ގ��p�����[�^�[�ݒ�
//		Dynamics::SSurfaceParameter Param = { ContactBounce };
//		Param.Friction			= 1.0f;		// ���C��
//		Param.Bounce			= 0.5f;		// ���˗�(0.0�`1.0)
//		Param.BounceVelocity	= 0.0f;		// ���˂���Œᑬ�x(0.0�`)
//		pContact->SetSurfaceParameter( i, Param );
//	}
//}
//
//









