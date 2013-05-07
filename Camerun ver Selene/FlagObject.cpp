//*============================================================================
//FlagObject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FlagObject.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//=============================================================================
CFlagObject::CFlagObject( string name )
{
	m_IsVisible = true;
	
	m_pModel	= NULL;
	m_eType		= OBJ_OTHER;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_vPos.Set(0, 10, 0);
	m_vRot.Set(0, 0, 0);
	
	m_vScale.Set(4.0f, 4.0f, 4.0f);
	
	m_fGravity = 0.0f;
	
	m_ActorIndex = 0;
	
	m_DataName = name;
	
	m_matBone.Identity();
	
}

//=============================================================================
//������
//=============================================================================
void CFlagObject::Init()
{
	m_vPos.Set(0, 10, 0);
	m_vRot.Set(0, 0, 0);
}


//=============================================================================
//����
//=============================================================================
void CFlagObject::Exec()
{
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	if( !m_IsSetFlag )
	{	
		//m_pActorModel[m_ActorIndex]->LocalTranslation( m_vOldPos + Math::Vector3D( 1.0, 1.0, 0 ) );
		
		//m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.x - DEG_TO_ANGLE(90) ) );
		
		
		//m_pActorModel[m_ActorIndex]->LocalRotationX( DEG_TO_ANGLE( 90 ) );
		
		//
		//m_pActorModel[m_ActorIndex]->RotationY( toI( m_vRot.x - DEG_TO_ANGLE(90) ) );
		
	}
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	

	/*�ړ��̐ݒ�*/
	if( m_IsSetFlag )
	{	
		m_pActorModel[m_ActorIndex]->RotationX( toI( m_vRot.y ) );
		
		m_pActorModel[m_ActorIndex]->RotationY( toI( m_vRot.x - DEG_TO_ANGLE(90) ) );
		
		m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	}
	
	// �L�����̕ϊ��X�V
	m_pActorModel[m_ActorIndex]->TransformUpdate();
}

