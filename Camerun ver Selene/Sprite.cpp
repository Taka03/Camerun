//*============================================================================
//Sprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//===========================================================================
CSprite::CSprite( string name ) :m_pTex(NULL), m_pSpr(NULL)
{
	m_DataName = name;
	
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
	
	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
	
}

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	name:データ名
//	vPos:表示位置
//===========================================================================
CSprite::CSprite( string name, Math::Vector2D vPos ) :m_pTex(NULL), m_pSpr(NULL)
{
	m_DataName = name;
	
	m_IsVisible = true;
	m_IsMissionVisible = true;
	
	m_vPos.Set( vPos.x, vPos.y, 0 );
	m_vRot.Set(0, 0, 0);

	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;

}

//============================================================================
//デストラクタ
//============================================================================
CSprite::~CSprite(void)
{
	SAFE_RELEASE( m_pTex );
	SAFE_RELEASE( m_pSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void CSprite::Load( Renderer::IRender *pRender )
{
	m_pTex = pRender->CreateTextureFromFile( m_DataName.c_str() );
	
	m_Width = m_pTex->GetOriginalSize().x / m_Divnum.x;
	m_Height = m_pTex->GetOriginalSize().y / m_Divnum.y;
	
	if( m_pTex != NULL )
	{	
		m_pSpr = pRender->CreateSprite2D( 1000, m_pTex ); 
	}
}

//============================================================================
//処理
//============================================================================
void CSprite::Exec()
{
	if( m_pSpr != NULL )
	{
		float fWidth = toF(m_pTex->GetOriginalSize().x) / toF( m_Divnum.x );
		float fHeight = toF( m_pTex->GetOriginalSize().y ) / toF( m_Divnum.y );
		
		m_pSpr->Begin();
		
		m_pSpr->DrawSquareRotate( Math::Rect2DF( m_vPos.x, m_vPos.y, toF( fWidth ), toF( fHeight ) ),
								  Math::Rect2DF( m_Anim.x * fWidth, m_Anim.y * fHeight, toF( fWidth ), toF( fHeight ) ), 
								  CColor(255, 255, 255),
								  toI( m_vRot.x ) ); 
		
		m_pSpr->End();
	}
}

//============================================================================
//レンダリング
//============================================================================
void CSprite::Rendering( )
{
	m_pSpr->Rendering();
}

//============================================================================
//画像の複数描画
//============================================================================
//[input]
//	pos:描画位置
//	AnimID:アニメID
//	DrawNum:描画数
//===========================================================================
void CSprite::DrawMultiGraph( Selene::Math::Point2DF pos[], Math::Point2DF AnimID[], int DrawNum )
{
	if( m_pSpr != NULL )
	{
		float fWidth = toF( m_pTex->GetOriginalSize().x ) / toF( m_Divnum.x );
		float fHeight = toF( m_pTex->GetOriginalSize().y ) / toF( m_Divnum.y );
		
		m_pSpr->Begin();
		
		for( int i = 0;i < DrawNum;++i )
		{	
			m_pSpr->DrawSquare( Math::Rect2DF( pos[i].x, pos[i].y, toF( fWidth ), toF( fHeight ) ), Math::Rect2DF( AnimID[i].x * fWidth, AnimID[i].y * fHeight, toF( fWidth ), toF( fHeight ) ), CColor(255, 255, 255) ); 
		}
		
		m_pSpr->End();
	}
}

//============================================================================
//グレースケール描画
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void CSprite::DrawGrayScale( Renderer::IRender *pRender )
{
	pRender->DrawGrayscale( Math::Rect2DF( m_vPos.x, m_vPos.y, toF( m_pTex->GetOriginalSize().x ), toF( m_pTex->GetOriginalSize().y ) ), 
							CColor( 255, 255, 255 ),
							Math::Rect2DF( 0, 0, toF( m_pTex->GetOriginalSize().x ), toF( m_pTex->GetOriginalSize().y ) ),
							m_pTex );
}

//============================================================================
//アニメーションの描画
//============================================================================
//[input]
//	animtime:アニメーション時間
//===========================================================================
void CSprite::DrawAnimation( int animNum, int animTime )
{
	if( m_pSpr != NULL )
	{
		float fWidth = toF( m_pTex->GetOriginalSize().x ) / toF( m_Divnum.x );
		float fHeight = toF( m_pTex->GetOriginalSize().y ) / toF( m_Divnum.y );
		
		static int Time = 0;
		
		static int AnimCount = 0;
		
		Time ++;
		
		if( Time % 2 == 0 )
		{
			AnimCount++;
		}
		
		m_Anim.x = AnimCount % animNum;
		
		m_pSpr->Begin();
		
		m_pSpr->DrawSquare( Math::Rect2DF( m_vPos.x, m_vPos.y, toF( fWidth ), toF( fHeight ) ), Math::Rect2DF( m_Anim.x * fWidth, m_Anim.y * fHeight, toF( fWidth ), toF( fHeight ) ), CColor(255, 255, 255) ); 
		
		m_pSpr->End();
	}
	
}

//============================================================================
//移動
//============================================================================
void CSprite::Move()
{
	m_vPos.x -= 4.0f;
}


