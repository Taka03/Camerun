//*============================================================================
//Sprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
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
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�\���ʒu
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
//�f�X�g���N�^
//============================================================================
CSprite::~CSprite(void)
{
	SAFE_RELEASE( m_pTex );
	SAFE_RELEASE( m_pSpr );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
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
//����
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
//�����_�����O
//============================================================================
void CSprite::Rendering( )
{
	m_pSpr->Rendering();
}

//============================================================================
//�摜�̕����`��
//============================================================================
//[input]
//	pos:�`��ʒu
//	AnimID:�A�j��ID
//	DrawNum:�`�搔
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
//�O���[�X�P�[���`��
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
void CSprite::DrawGrayScale( Renderer::IRender *pRender )
{
	pRender->DrawGrayscale( Math::Rect2DF( m_vPos.x, m_vPos.y, toF( m_pTex->GetOriginalSize().x ), toF( m_pTex->GetOriginalSize().y ) ), 
							CColor( 255, 255, 255 ),
							Math::Rect2DF( 0, 0, toF( m_pTex->GetOriginalSize().x ), toF( m_pTex->GetOriginalSize().y ) ),
							m_pTex );
}

//============================================================================
//�A�j���[�V�����̕`��
//============================================================================
//[input]
//	animtime:�A�j���[�V��������
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
//�ړ�
//============================================================================
void CSprite::Move()
{
	m_vPos.x -= 4.0f;
}


