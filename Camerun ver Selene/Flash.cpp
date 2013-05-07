//*============================================================================
//Particle.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Flash.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
CFlash::CFlash( string name ) 
{
	m_DataName = name;
	
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
	
}

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CFlash::CFlash( string name, Math::Vector3D vPos ) 
{
	m_DataName = name;
	
	m_IsVisible = true;
	
	m_vPos = vPos;
	m_vRot.Set(DEG_TO_ANGLE(90), 0, 0);
	m_vScale.Set( 1, 1, 1 );
	
	m_vRot.y = DEG_TO_ANGLE( 120 );
	m_vRot.z = DEG_TO_ANGLE( 0 );
	
	m_Alpha.x = 255;
	m_Alpha.y = 255;
	m_Alpha.z = 0;
	
}

////============================================================================
////����
////============================================================================
//void CFlash::Exec()
//{
//	static int count = 0;
//	
//	if( m_pSpr != NULL )
//	{
//		if( m_IsVisible )
//		{
//			if( ++count == 60 )
//			{
//				count = 0;
//				m_IsVisible = false;
//			}
//			
//			m_pSpr->Begin();
//			
//			m_Alpha.x = 255;//Interpolation::Flat( m_Alpha.y, m_Alpha.z, BOMB_ALIVE_TIME, count );
//			m_vScale.x = Interpolation::Flat( m_vScale.y, m_vScale.z, 60, count );
//			
//			//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vPos.z + 1, BOMB_ALIVE_TIME, count );
//		
//			Math::Rect2DI SrcRect( 0, 0, m_Width, m_Height );
//			
//			m_matWorld.w = m_vPos;
//			
//			m_pSpr->Draw( m_matWorld, Math::Point2DF(m_Width, m_Height ), SrcRect, CColor( 255, 255, 255, m_Alpha.x ) );
//			
//			//m_pSpr->DrawPolyLine( m_matWorld., Math::Point2DF( m_vScale.x, m_vScale.y ), SrcRect, CColor( 255, 255, 255, m_Alpha.x ) );
//			
//			m_pSpr->End();
//		}
//	}
//}

//============================================================================
//�����_�����O
//============================================================================
void CFlash::Rendering( int index )
{
	m_pRender->SetDrawType( DRAW_TYPE_ADD );	// �`�惂�[�h�i������
	m_pRender->SetAlphaTestEnable( true );		// �A���t�@�e�X�gON
	m_pRender->SetDepthTestEnable( true );		// �[�x�e�X�gON
	m_pRender->SetDepthWriteEnable( false );		// �[�x��������OFF
	
	m_pActorParticle[index]->RenderingRequest();
	
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );	
	
}
