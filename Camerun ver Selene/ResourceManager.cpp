//*============================================================================
//ResourceManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "Sprite.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pCore:コア用デバイス
//	pFileMgr:ファイル管理用デバイス
//	pRender:レンダラー用デバイス
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
//デストラクタ
//=============================================================================
CResourceManager::~CResourceManager()
{
	SAFE_DELETE( m_pGameObj );
	SAFE_DELETE( m_pRender );
	SAFE_DELETE( m_pFileMgr );
	SAFE_DELETE( m_pCore );
}

//=============================================================================
//オブジェクトの追加
//=============================================================================
//[input]
//	type:オブジェクトタイプ
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
//処理
//=============================================================================
void CResourceManager::Run()
{
	/*ファイル読み込み*/
	m_pGameObj->Load( m_pRender, m_pFileMgr );		
}

//=============================================================================
//ファイル読み込みスレッド用
//=============================================================================
//[input]
//	pData:データポインタ
//===========================================================================
void CResourceManager::LoadedProc( void *pData )
{
	/*使用するCPU番号*/
	System::SetThreadCPUNo( 1 );
	
	( (CResourceManager*)pData)->Run();
}




