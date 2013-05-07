//*============================================================================
//MiniMap.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "MiniMap.h"

//�~�j�}�b�v�̈ړ����\��
const float MAP_ZMIN = -528;//�}�b�vZ�ʒu�̍ŏ��ʒu
const float MAP_ZMAX = 0;//�}�b�vZ�ʒu�̍ő�ʒu
const float MAP_XMIN = -359;//�}�b�vX�ʒu�̍ŏ��ʒu
const float MAP_XMAX = 359*2;//�}�b�vX�ʒu�̍ő�ʒu

const float MINI_PLAYER_WIDTH = 16;
const float MINI_PLAYER_HEIGHT = 16;

	


//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
CMiniMap::CMiniMap( string name ) 
{
	m_DataName = name;
	
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
	
	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
	
	m_Scroll.x = 0;
	m_Scroll.y = 0;
	
}

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CMiniMap::CMiniMap( string name, Math::Vector2D vPos ) 
{
	m_DataName = name;
	
	m_IsVisible = true;
	
	m_vPos.Set( vPos.x, vPos.y, 0 );
	m_vRot.Set(0, 0, 0);

	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
	
	m_Scroll.x = 0;
	m_Scroll.y = 0;
	
	m_DrawSize.x = 240;
	m_DrawSize.y = 180;
	
}

//============================================================================
//�f�X�g���N�^
//============================================================================
CMiniMap::~CMiniMap()
{
}


//============================================================================
//����
//============================================================================
void CMiniMap::Exec()
{
	if( m_pSpr != NULL )
	{
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, m_DrawSize.x, m_DrawSize.y );
		
		Math::Rect2DF Src( m_Scroll.x , m_Scroll.y , m_DrawSize.x, m_DrawSize.y  );
		
		//Math::Rect2DF Dst( 0, 0, m_Width, m_Height ); 
		//Math::Rect2DF Src( 0, 0, m_Width, m_Height ); 
		
		
		m_pSpr->Begin();
		
		m_pSpr->DrawSquare( Dst, Src, CColor(255, 255, 255) ); 
		
		m_pSpr->End();
	}
}

//============================================================================
//����
//============================================================================
void CMiniMap::Rendering()
{
	if( m_pRender != NULL )
	{
		/*�g�̕`��*/
		m_pRender->SetDrawType( DRAW_TYPE_ADD );
		
		const int SUB_X = 0;
		const int SUB_Y = 0;
		
		m_pRender->FillRect( Math::Rect2DF( toF( m_vPos.x ), toF( m_vPos.y ), m_DrawSize.x, m_DrawSize.y ), CColor( 189, 140, 191, 128) );
		
		m_pRender->SetDrawType( DRAW_TYPE_BLEND );
		
		m_pSpr->Rendering();
		
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		
	}
	
}



//============================================================================
//�ړ�
//============================================================================
//[input]
//	pChara:�ݒ肷��L�����N�^�[
//============================================================================
void CMiniMap::Move( CCharacter *pChara )
{
	
	m_Scroll.x = ( ( pChara->GetPosition().x - MAP_XMIN) / MAP_XMAX ) * (m_Width) - m_DrawSize.x/2;
	m_Scroll.y = ( (pChara->GetPosition().z /MAP_ZMIN ) )  * (m_Height) - m_DrawSize.y/2;
	
}

//============================================================================
//�X�N���[���␳
//============================================================================
void CMiniMap::ScrollAdjust()
{
	
	if( m_Scroll.x <= 0)
	{
		m_Scroll.x = 0;
	}
	
	if( m_Scroll.x >= m_Width - m_DrawSize.x + MINI_PLAYER_WIDTH )
	{
		m_Scroll.x = m_Width - m_DrawSize.x + MINI_PLAYER_WIDTH;	
	}
	
	if( m_Scroll.y <=  -m_DrawSize.y / 2 )
	{
		m_Scroll.y = -m_DrawSize.y / 2;	
	}
	
	if( m_Scroll.y >= m_Height - m_DrawSize.y / 2 + MINI_PLAYER_HEIGHT)
	{
		m_Scroll.y = m_Height - m_DrawSize.y / 2 + MINI_PLAYER_HEIGHT;
	}
}

//============================================================================
//�~�j�}�b�v�p�L�����ʒu�̐ݒ�
//============================================================================
//[input]
//	pChara:�ݒ肷��L�����N�^�[
//	pSpr:�ݒ肷��~�j�L�����X�v���C�g
//	IsPlayer:�v���C���[�L�������ǂ���
//============================================================================
void CMiniMap::SetMiniCharaPos( CCharacter *pChara, CSprite *pSpr, bool IsPlayer )
{
	if( IsPlayer )
	{
		if( pChara->GetPosition().x < 0 )
		{	
			//float XAxis = ( pChara->GetPosition().x + MAP_XMAX/2  ) / MAP_XMAX ;
			//float ZAxis =( pChara->GetPosition().z ) / MAP_ZMIN;
			//float AdjustHeight = m_DrawSize.y - pSpr->GetHeight();
			
			//pSpr->SetPosition( Math::Vector3D( XAxis * m_DrawSize.x + m_vPos.x, 
			//								   ZAxis * AdjustHeight + m_vPos.y,
			//									0 )  );
			
			pSpr->SetPosition( Math::Vector3D( m_DrawSize.x / 2 - pSpr->GetWidth() / 2, m_DrawSize.y / 2 - pSpr->GetHeight() / 2, 0 ) );
			
		}
		
		else
		{
			float XAxis = ( pChara->GetPosition().x ) / MAP_XMAX;
			float ZAxis = ( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustWidth = m_DrawSize.x - pSpr->GetWidth() / 2;
			float AdjustHeight = m_DrawSize.y - pSpr->GetHeight();
		
			//pSpr->SetPosition( Math::Vector3D(	XAxis  * AdjustWidth + m_DrawSize.x / 2 + m_vPos.x,
			//											ZAxis  * AdjustHeight + m_vPos.y ,
			//											 0 ) );
			//
			pSpr->SetPosition( Math::Vector3D( m_DrawSize.x / 2 - pSpr->GetWidth() / 2 , m_DrawSize.y / 2 - pSpr->GetHeight() / 2, 0 ) );
														 
		}	
		
		pSpr->SetRotate( Math::Vector3D( -pChara->GetRotate().x + DEG_TO_ANGLE( 90 ) , pChara->GetRotate().y, pChara->GetRotate().z  ) );
		
		
		//if( pSpr->GetPosition().y <= m_DrawSize.y / 2)
		//{
		//	pSpr->SetPosition( Math::Vector3D( pSpr->GetPosition().x, m_DrawSize.y / 2, pSpr->GetPosition().z ) );
		//}
		//
		//if( pSpr->GetPosition().y >= m_DrawSize.y / 2 + pSpr->GetHeight() )
		//{
		//	pSpr->SetPosition( Math::Vector3D( pSpr->GetPosition().x, m_DrawSize.y / 2 + pSpr->GetHeight(), pSpr->GetPosition().z ) );
		//}
		//
		//
		//if( pSpr->GetPosition().x <= m_DrawSize.x / 2 )
		//{
		//	pSpr->SetPosition( Math::Vector3D( m_DrawSize.x / 2, pSpr->GetPosition().y, pSpr->GetPosition().z ) );
		//}
		//
		//if( pSpr->GetPosition().x >= m_DrawSize.x / 2 + pSpr->GetWidth() )
		//{
		//	pSpr->SetPosition( Math::Vector3D( m_DrawSize.x / 2 + pSpr->GetWidth(), pSpr->GetPosition().y, pSpr->GetPosition().z ) );
		//}
		
	}
	
	else
	{
		if( pSpr->GetPosition().x < 0 )
		{	
			float XAxis = ( pChara->GetPosition().x + MAP_XMAX/2  ) / MAP_XMAX ;
			float ZAxis =( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustHeight = toF( m_Width ) - toF( pSpr->GetHeight() );
			
			pSpr->SetPosition( Math::Vector3D( (XAxis * m_Width + m_vPos.x) -  m_Scroll.x  /*+ m_DrawSize.x / 2*/, 
											   (ZAxis * AdjustHeight + m_vPos.y) - m_Scroll.y  /*+ m_DrawSize.y / 2*/,
												0 )  );
		}
		
		else
		{
			float XAxis = ( pChara->GetPosition().x ) / MAP_XMAX;
			float ZAxis = ( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustWidth = toF( m_Width ) - toF( pSpr->GetWidth() / 2 ) ;
			float AdjustHeight = toF( m_Height ) - toF( pSpr->GetHeight() ) ;
		
			pSpr->SetPosition( Math::Vector3D( (XAxis  * AdjustWidth + m_Width / 2 + m_vPos.x ) - m_Scroll.x - pSpr->GetWidth()/2/* + m_DrawSize.x / 2*/,
												(ZAxis  * AdjustHeight + m_vPos.y) - m_Scroll.y  /*+ m_DrawSize.y / 2*/,
														 0 ) );
		}	
		
		/*�~�j�}�b�v�O�ɂ���Ƃ��́A�\�������Ȃ��悤�ɂ���*/
		if( pSpr->GetPosition().x >= m_vPos.x && pSpr->GetPosition().x <= m_vPos.x + m_DrawSize.x
			&& pSpr->GetPosition().y >= m_vPos.y && pSpr->GetPosition().y <= m_vPos.y + m_DrawSize.y )
		{
			if( pSpr->GetMissionVisible() )
			{	
				pSpr->SetVisibleFlag( pChara->GetVisibleFlag() );
			}
		}
		
		else
		{
			pSpr->SetVisibleFlag( false );
		}
	
	}
	
	
}




