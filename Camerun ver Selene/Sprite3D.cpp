//*============================================================================
//Sprite3D.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite3D.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//===========================================================================
CSprite3D::CSprite3D( string name ) :m_pTex(NULL), m_pSpr(NULL)
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
CSprite3D::CSprite3D( string name, Math::Vector3D vPos ) :m_pTex(NULL), m_pSpr(NULL)
{
	m_DataName = name;
	
	for( int i = 0;i < S_MAX;++i )
	{
		m_pActorSprite[i] = NULL;
	}
	
	m_IsVisible = true;
	
	m_vPos = vPos;
	m_vRot.Set(0, 0, 0);
	m_vScale.Set( 1, 1, 1 );
	
	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
	
	m_matWorld.Identity();
}

//============================================================================
//デストラクタ
//============================================================================
CSprite3D::~CSprite3D(void)
{
	for( int i = 0;i < S_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorSprite[i] );
	}
	
	SAFE_RELEASE( m_pTex );
	SAFE_RELEASE( m_pSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void CSprite3D::Load( Renderer::IRender *pRender )
{
	m_pTex = pRender->CreateTextureFromFile( m_DataName.c_str() );
	
	m_Width = m_pTex->GetOriginalSize().x / m_Divnum.x;
	m_Height = m_pTex->GetOriginalSize().y / m_Divnum.y;
	
	if( m_pTex != NULL )
	{	
		m_pSpr = pRender->CreateSprite3D( 1000, m_pTex ); 
	}
}

//============================================================================
//アクター生成
//============================================================================
//[input]
//	index:インデックス
//	pSceneMgr:シーンマネージャ
//===========================================================================
void CSprite3D::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorSprite[index] = pSceneMgr->CreateActor( m_pSpr );
}

//============================================================================
//処理
//============================================================================
void CSprite3D::Exec()
{
	if( m_pSpr != NULL )
	{
		m_pSpr->Begin();
		
		Math::Rect2DI SrcRect( m_Anim.x*m_Width, m_Anim.y*m_Height, m_Width, m_Height );
		
		m_matWorld.w = m_vPos;
		
		/*描画*/
		m_pSpr->Draw( m_matWorld, Math::Point2DF( m_vScale.x, m_vScale.x ), SrcRect, CColor( 255, 255, 255 ) );
		
		m_pSpr->End();
	}
}

//============================================================================
//参照カウンタの増加
//============================================================================
void CSprite3D::AddRef()
{
	m_pTex->AddRef();
	m_pSpr->AddRef();
	
	for( int actornum = 0;actornum < S_MAX;++actornum )
	{
		m_pActorSprite[actornum]->AddRef();
	}
}


//============================================================================
//レンダリング
//============================================================================
void CSprite3D::Rendering( int index )
{
	m_pActorSprite[index]->RenderingRequest();
}
