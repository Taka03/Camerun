#include "Draw2DObject.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//===========================================================================
Draw2DObject::Draw2DObject( string name ) 
{
	m_DataName = name;
	
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
}

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//	vPos:表示位置
//===========================================================================
Draw2DObject::Draw2DObject( string name, Math::Vector2D vPos )
{
	m_DataName = name;
	
	m_vPos.Set( vPos.x, vPos.y, 0 );
	m_vRot.Set(0, 0, 0);
}

//============================================================================
//デストラクタ
//============================================================================
Draw2DObject::~Draw2DObject( ) 
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		SAFE_DELETE( i->gameobj );
	}
	
}



//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void Draw2DObject::Load( Renderer::IRender *pRender )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		Draw2DObject *obj = dynamic_cast<Draw2DObject *>( i->gameobj );
		
		obj->Load( pRender );
			
	}
}

//============================================================================
//処理
//============================================================================
void Draw2DObject::Exec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		if( !(i->gameobj->GetStopFlag() ) )
		{	
			i->gameobj->Exec();
		}
	}

}

//============================================================================
//アクターの生成
//============================================================================
//[input]
//	pSceneMgr:シーン管理用デバイス
//===========================================================================
//void Draw2DObject::CreateActor( Scene::ISceneManager *pSceneMgr )
//{
//	if( m_pSprite != NULL )
//	{
//		m_pActorSpr = pSceneMgr->CreateActor(
//	}
//}

//============================================================================
//レンダリング
//============================================================================
void Draw2DObject::Rendering( )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		Draw2DObject *obj = dynamic_cast<Draw2DObject *>( i->gameobj );
		
		if( obj->GetVisibleFlag() )
		{	
			obj->Rendering( );
		}
	}
}





