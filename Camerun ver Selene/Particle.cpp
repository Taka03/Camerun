//*============================================================================
//Particle.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Particle.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
CParticle::CParticle( string name ) :m_pTex(NULL), m_pParticle(NULL)
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
CParticle::CParticle( string name, Math::Vector3D vPos ) :m_pTex(NULL), m_pParticle(NULL)
{
	m_DataName = name;
	
	for( int i = 0;i < S_MAX;++i )
	{
		m_pActorParticle[i] = NULL;
	}
	
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

//============================================================================
//�f�X�g���N�^
//============================================================================
CParticle::~CParticle(void)
{
	for( int i = 0;i < S_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorParticle[i] );
	}
	
	SAFE_RELEASE( m_pTex );
	SAFE_RELEASE( m_pParticle );
	
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
void CParticle::Load( Renderer::IRender *pRender )
{
	m_pTex = pRender->CreateTextureFromFile( m_DataName.c_str() );
	
	m_Width = m_pTex->GetOriginalSize().x;
	m_Height = m_pTex->GetOriginalSize().y;
	
	/*�p�[�e�B�N���̐���*/
	m_pParticle = pRender->CreateParticle( 128, m_pTex, PARTICLE_TYPE_VOLUME, true ); 
	
}

//============================================================================
//�A�N�^�[����
//============================================================================
//[input]
//	index:�C���f�b�N�X
//	pSceneMgr:�V�[���}�l�[�W��
//===========================================================================
void CParticle::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorParticle[index] = pSceneMgr->CreateActor( m_pParticle );
}

//============================================================================
//����
//============================================================================
void CParticle::Exec()
{
	static int count = 0;
	
	if( m_pParticle != NULL )
	{
		if( m_IsVisible )
		{
			
			m_pParticle->Begin();
			
			//m_Alpha.x = Interpolation::Flat( m_Alpha.y, m_Alpha.z, BOMB_ALIVE_TIME, count );
			//m_vRot.x = DEG_TO_ANGLE(0);
			//m_Alpha.x = 255;
			//m_vScale.x = Interpolation::Flat( m_vScale.y, m_vScale.z, BOMB_ALIVE_TIME, count );
			
			//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vPos.z + 1, BOMB_ALIVE_TIME, count );
		
			Math::Rect2DI SrcRect( 0, 0, m_Width, m_Height );
			
			m_pParticle->DrawRotate( m_vPos, Math::Point2DF( m_vScale.x, m_vScale.y ), SrcRect, CColor( 255, 255, 255, m_Alpha.x ), toI( m_vRot.x ) );
			
			m_pParticle->End();
		}
	}
}

//============================================================================
//�����_�����O
//============================================================================
void CParticle::Rendering( int index )
{
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );	// �`�惂�[�h�i���Z
	m_pRender->SetAlphaTestEnable( true );		// �A���t�@�e�X�gON
	m_pRender->SetDepthTestEnable( true );		// �[�x�e�X�gON
	m_pRender->SetDepthWriteEnable( false );		// �[�x��������OFF
	
	m_pActorParticle[index]->RenderingRequest();
	
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );	
	
}
