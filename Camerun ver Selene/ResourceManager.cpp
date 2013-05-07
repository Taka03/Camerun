//*============================================================================
//ResourceManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "Sprite.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pCore:�R�A�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
CResourceManager::CResourceManager( ICore *pCore,
									File::IFileManager *pFileMgr, 
									Renderer::IRender *pRender )
:m_pCore(pCore), m_pFileMgr(pFileMgr), m_pRender( pRender )
 
 

{
	pCore->AddRef();
	pFileMgr->AddRef();
	pRender->AddRef();
	
	m_pGameObj = new CGameObject();
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CResourceManager::~CResourceManager()
{
	SAFE_DELETE( m_pGameObj );
	SAFE_DELETE( m_pRender );
	SAFE_DELETE( m_pFileMgr );
	SAFE_DELETE( m_pCore );
}

//=============================================================================
//�I�u�W�F�N�g�̒ǉ�
//=============================================================================
//[input]
//	type:�I�u�W�F�N�g�^�C�v
//===========================================================================
void CResourceManager::AppendObject( eResourceType type )
{
	//switch( type )
	//{
	//	case TEXTURE:
	//	{
	//		m_pGameObj->AppendObject( new CSprite(
	//		break;
	//	}
	//	
	//	case MODEL:
	//	{
	//		m_pGameObj->AppendObject( new 
	//		break;
	//	}
	//	
	//	case MAP:
	//	{
	//		m_pGameObj->AppendObject( 
	//		break;
	//	}

	//	case SOUND:
	//	{
	//		m_pGameObj->AppendObject( 
	//		break;
	//	}

	//	case BGM:
	//	{
	//		m_pGameObj->AppendObject( 
	//		break;
	//	}
	//	
	//}
}

//=============================================================================
//����
//=============================================================================
void CResourceManager::Run()
{
	/*�t�@�C���ǂݍ���*/
	m_pGameObj->Load( m_pRender, m_pFileMgr );		
}

//=============================================================================
//�t�@�C���ǂݍ��݃X���b�h�p
//=============================================================================
//[input]
//	pData:�f�[�^�|�C���^
//===========================================================================
void CResourceManager::LoadedProc( void *pData )
{
	/*�g�p����CPU�ԍ�*/
	System::SetThreadCPUNo( 1 );
	
	( (CResourceManager*)pData)->Run();
}




