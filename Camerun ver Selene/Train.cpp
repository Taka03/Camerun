//*=============================================================================
//enemy.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "Train.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�ݒ肷����W
//=============================================================================
CTrain::CTrain( string name, Math::Vector3D vPos ) 
{
	m_DataName = name;
	m_eType = OBJ_OTHER;
	
	m_IsVisible = true;
	m_IsStop	= false;
	m_IsSetFlag = false;	
	
	float Scale = 1.0f;
	
	m_vPos = vPos;
	m_vOldPos = vPos;
	m_vRot.Set( 0, DEG_TO_ANGLE(0), 0 );
	m_vScale.Set( Scale, Scale, Scale );
	
	m_pModel = NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	m_fSpeed = 0.31f;
	
	m_fWeight = 0.0f;
	
}

//=============================================================================
//������
//=============================================================================
void CTrain::Init()
{
	m_vPos = m_vOldPos;
	
	m_ActorIndex = 0;
	
}

//=============================================================================
//����
//=============================================================================
void CTrain::Exec()
{
	/*�^�[�Q�b�g���ʒu�̐ݒ�*/
	m_vArrowPos = m_vPos + Math::Vector3D( 0, 5, 0 );
	
	/*�p���̃��Z�b�g*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.y ) - DEG_TO_ANGLE(90) );
	
	/*�ړ��̐ݒ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );

	// �L�����̕ϊ��X�V
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//�ړ�����
//=============================================================================
void CTrain::MoveExec()
{
	if( m_vPos.z < -540.0f )
	{
		m_vPos.z = m_vOldPos.z;
	}
	
	else
	{
		m_vPos.z -= m_fSpeed;
	}

}

//=============================================================================
//�d�ԉ��̍Đ�
//=============================================================================
//[input]
//	pSound:�T�E���h�f�o�C�X
//	fDistance:����
//=============================================================================
void CTrain::PlaySnd(Selene::Sound::ISound *pSound, float fDistance)
{
	static float Pan = -100.0f;
	
	Pan += 1.0f;
	
	if( Pan >= 100 )
	{
		Pan = 100;
	}
	
	pSound->SetVolume( 0, 100 - (fDistance * 0.5f) );
	
	pSound->Play( 0, true );
	
	
}


