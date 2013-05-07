//*===========================================================================
//C3DObject.cpp
//*===========================================================================

//============================================================================
//include
//============================================================================
#include "C3DObject.h"
#include <string>

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//===========================================================================
CDraw3DObject::CDraw3DObject( string name ) :m_pRigidModel(NULL), m_pShader(NULL)
{
	m_IsVisible = true;
	
	m_DataName = name;
	
	m_vPos.Set( 0, -1, -2 );
	m_vRot.Set( 0, 0, 0 );
	
	m_vScale.Set( 1.0f, 1.0f, 1.0f );
}

//=============================================================================
//デストラクタ
//=============================================================================
CDraw3DObject::~CDraw3DObject(void)
{
//	SAFE_RELEASE( m_pRigidModel );
	
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		SAFE_DELETE( obj );
	}
	
}

//=============================================================================
//初期化
//=============================================================================
void CDraw3DObject::Init()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		i->gameobj->Init();
	}
}


//=============================================================================
//処理
//=============================================================================
void CDraw3DObject::Exec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		i->gameobj->Exec();
	}
	
}

//=============================================================================
//処理
//=============================================================================
void CDraw3DObject::MoveExec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast< CDraw3DObject * >( i->gameobj );
		
		if( !obj->GetStopFlag() )
		{	
			obj->MoveExec();
		}
	}
	
}



//=============================================================================
//レンダリング
//=============================================================================
//[input]
//	index:インデックスに設定する値
//=============================================================================
void CDraw3DObject::Rendering(int index)
{
	list<ListData>::iterator i = m_ObjectList.begin();
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( obj->GetVisibleFlag() )
		{	
			obj->Rendering(index);
		}
		
		#if defined(NDEBUG)
		
			
		
		#endif
	}
	
}

//=============================================================================
//ファイル読み込み
//=============================================================================
//[input]
//	pRender:レンダリング用デバイス
//=============================================================================
void CDraw3DObject::Load( Renderer::IRender *pRender )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->Load( pRender );
			
	}
	
}

//=============================================================================
//シェーダー読み込み
//=============================================================================
//[input]
//	pRender:レンダリング用デバイス
//	name:データ名
//=============================================================================
void CDraw3DObject::LoadShader( Renderer::IRender *pRender, string name )
{
	m_pShader = pRender->CreateShaderFromFile( name.c_str() );
}


//=============================================================================
//アクターの生成
//=============================================================================
//[input]
//	pSceneMgr:シーン管理用デバイス
//=============================================================================
void CDraw3DObject::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateActor( index, pSceneMgr );		
	
	}
	
}

//=============================================================================
//剛体モデルの生成
//=============================================================================
//[input]
//	pWorld:物理シミュレーション用デバイス
//=============================================================================
void CDraw3DObject::CreateRigidModel( Dynamics::ISimulationWorld *pWorld )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateRigidModel( pWorld );
			
	}
	
}

//=============================================================================
//コリジョンデータの作成
//=============================================================================
void CDraw3DObject::CreateCollision()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateCollision();
			
	}
	
}


//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input/output]
//	ppChara:判定するキャラ
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( CDraw3DObject **ppChara )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( obj->GetObjectType() == OBJ_PLAYER && obj->GetObjectType() == OBJ_ENEMY )
		{
			if( this->HitCheck( &obj ) )
			{
				*ppChara = obj;
				return true;
			}
		}
			
	}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay ) )
		{
			return true;
		}
	}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	ppHitObj:当たったオブジェクトの取得
//[output]
//	obj:衝突したオブジェクト	
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay ) )
		{
			*ppHitObj = pChara;
			return true;
		}
	}
	
	return false;
}


//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突判定の結果
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay, Out ) )
		{
			return true;
		}
	}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突判定の結果
//[output]
//	ppHitObj:当たったオブジェクト
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay, Out ) )
		{
			*ppHitObj = pChara;
			
			return true;
		}
	}
	
	return false;
}



//=============================================================================
//フラッシュを浴びた状態の処理
//=============================================================================
void CDraw3DObject::FlashedState(  )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->GetObjectType() == OBJ_ENEMY )
		{
			pChara->FlashedState();
		}	
	}
}

////=============================================================================
////フラグの回収
////=============================================================================
//void CDraw3DObject::RecallFlag( Selene::Peripheral::IInputController *m_pCtrl )
//{
//	list<ListData>::iterator i;
//	
//	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
//	{
//		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
//		
//		if( pChara->GetObjectType() == OBJ_ENEMY )
//		{
//			pChara->RecallFlag( m_pCtrl );
//		}	
//	}
//}





//=============================================================================
//アクターインデックスのセット
//=============================================================================
//[input]
//	index:インデックスに設定する値
//=============================================================================
void CDraw3DObject::SetActorIndex( int index )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( index == S_MAIN || index == S_SUB )
		{
			obj->SetActorIndex( index );
		}
	}
	
}


//=============================================================================
//アクターのセット
//=============================================================================
//[input]
//	style:姿勢データ
//=============================================================================
//void CDraw3DObject::SetActor( Selene::Math::Style *pStyle )
//{
//	list<ListData>::iterator i;
//	
//	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
//	{
//		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
//		
//		obj->SetActor( pStyle );		
//	
//	}
//	
//}





