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
//コンストラクタ
//=============================================================================
//[input]
//	pScene:設定するシーン
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
//デストラクタ
//=============================================================================
CGameSceneManager::~CGameSceneManager()
{
	SAFE_DELETE( m_pFiberCtrl );
}

//=============================================================================
//処理
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
//シーンの追加
//=============================================================================
//[input]
//	Type:シーンタイプ
//	pScene:追加するシーン
//=============================================================================
void CGameSceneManager::AddScene( eSceneType Type, CScene *pScene)
{
	SceneList liScene;
	
	liScene.m_eSceneType = Type;
	liScene.m_pScene = pScene;
	
	m_SceneList.push_back( liScene );
}

//=============================================================================
//シーンの削除
//=============================================================================
//[input]
//	pScene:削除するシーン
//=============================================================================
void CGameSceneManager::RemoveScene(CScene *pScene)
{

}

//=============================================================================
//シーンの参照
//=============================================================================
//[input]
//	Type:シーンタイプ
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
//	// 衝突店の数を取得
//	Sint32 Count = pContact->GetCount();
//	
//	// 衝突処理
//	for ( Sint32 i = 0; i < Count; i++ )
//	{
//		// 材質パラメーター設定
//		Dynamics::SSurfaceParameter Param = { ContactBounce };
//		Param.Friction			= 1.0f;		// 摩擦率
//		Param.Bounce			= 0.5f;		// 反射率(0.0～1.0)
//		Param.BounceVelocity	= 0.0f;		// 反射する最低速度(0.0～)
//		pContact->SetSurfaceParameter( i, Param );
//	}
//}
//
//









