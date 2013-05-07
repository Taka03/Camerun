//*=============================================================================
//enemy.cpp
//*=============================================================================


//==============================================================================
//include
//==============================================================================
#include "enemy.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�ݒ肷����W
//=============================================================================
CEnemy::CEnemy( string name, Math::Vector3D vPos )  
{
	m_DataName = name;
	m_eType = OBJ_ENEMY;
	
	m_IsVisible = true;
	m_IsStop	= false;	
	m_IsSetFlag = false;
	
	float Scale = 1.0f;
	
	m_vPos = vPos;
	m_vOldPos = vPos;
	m_vRot.Set( 0, -DEG_TO_ANGLE(60), 0 );
	m_vScale.Set( Scale, Scale, Scale );
	
	m_pModel = NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 0.0f;
		m_AnimID[Anim] = 0;
	} 
	
	m_fKeyTime = 0.0f;
	
	m_fSpeed = 1.0f;
	
	//m_pAnim = new Math::Animation(4);
	//
	//m_pAnim->SetKey( 0, 0.0f, vPos.z );
	//m_pAnim->SetKey( 1, 5.0f, vPos.z - 3.0f );
	//m_pAnim->SetKey( 2, 10.0f, vPos.z - 100.0f );
	//m_pAnim->SetKey( 3, 15.0f, vPos.z - 200.0f );
	//
	m_fWeight = 0.0f;
	
	//m_pAnim->SetKey
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
//	SAFE_DELETE( m_pStunEffect );
	SAFE_DELETE( m_pAnimZ );
	SAFE_DELETE( m_pAnimX );
}



//=============================================================================
//������
//=============================================================================
void CEnemy::Init()
{
}

//=============================================================================
//����
//=============================================================================
void CEnemy::Exec()
{
	
	//Update( m_Anim*m_AnimSpeed );
	
	static Sint32 counter = 0;
	
	counter++;
	
	
	//if( m_vPos.z < -540.0f )
	//{
	//	m_vPos.z = -40.0f;
	//	counter = 0;
	//}
	m_fKeyTime += 1.0f/60.0f;
		
	//m_vPos.z -= m_pAnim->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	
	if( m_fKeyTime >= 15.0f )
	{
		m_fKeyTime = 0.0f;
	}
	
	m_vPos.z = Selene::Interpolation::Add4( -40.0f, -80.0f, 15.0f, m_fKeyTime );//m_pAnim->GetParameter( m_fKeyTime, ::ANIMATION_TYPE_TCB, 0.0f );//Interpolation::Neville( m_pAnim->GetParameter( 0, ANIMATION_TYPE_TCB, 0.0f ), m_pAnim->GetParameter( 1, ANIMATION_TYPE_TCB, 1.0f ), m_pAnim->GetParameter( 2, ANIMATION_TYPE_TCB, 7.0f ), m_fKeyTime/60.0f );
	
	
	/*�p���̃��Z�b�g*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI(-m_vRot.y) - DEG_TO_ANGLE(90) );
	
	/*�ړ��̐ݒ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] ++;
		
		/*���Ԃ��Ō�܂œ��B*/
		if ( m_fAnimTime[Anim] > m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] ) )
		{
			/*�ŏ��ɖ߂�*/
			m_fAnimTime[Anim] = 1.0f;
		}
	}

	// �L�����ɑ΂��ăA�j���[�V�������X�V
	m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW] );
	
	// �L�����̕ϊ��X�V
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//�t���b�V���𗁂т���Ԃ̏���
//=============================================================================
void CEnemy::FlashedState( )
{
	if( m_IsStop )
	{
		static int count = 0;
		
		int Time = Interpolation::Flat( 0, 30, 180, count ); 
		
		count++;
		
		//if( Time % 2 == 0 )
		//{
		//	m_IsVisible = !m_IsVisible;
		//}
		
		/*3�b�������瓮���n�߂�*/
		if( Time >= 30 )
		{
			count = 0;
			m_IsVisible = true;
			m_IsStop = false;
		}
	}
}

//=============================================================================
//�A�j���[�V�����̐؂�ւ�
//=============================================================================
void CEnemy::ChangeAnimation()
{
	if( m_AnimID[ANIM_NOW] != m_AnimID[ANIM_NEXT] )
	{
		/*��b�Ő؂�ւ���*/
		m_fWeight += 1.0f / 120.0f;
		
		if( m_fWeight >= 1.0f )
		{
			m_fWeight = 0.0f;
			m_fAnimTime[ANIM_NOW] = m_fAnimTime[ANIM_NEXT];
			m_AnimID[ANIM_NOW] = m_AnimID[ANIM_NEXT];
		}
	}
}

//=============================================================================
//�L�[�^�C���̐؂�ւ�
//=============================================================================
//[input]
//	pMouse:�}�E�X�f�o�C�X
//=============================================================================
void CEnemy::ChangeKeyTime( Selene::Peripheral::IMouse *pMouse )
{
	/*�t���[�����~������*/
	if( pMouse->GetStateW() == MOUSE_PUSH )
	{
		m_IsStop = !m_IsStop;
	}
	
	if( pMouse->GetStateL() == MOUSE_PUSH )
	{
		m_IsChangeKeyTime = true;
		m_KeyIndex --;	
	}
	
	if( pMouse->GetStateR() == MOUSE_PUSH )
	{
		m_IsChangeKeyTime = true;
		m_KeyIndex ++;
	}
	
	if( m_IsChangeKeyTime )
	{	
		m_fKeyTime = m_vKeyTime.at(m_KeyIndex);	
		m_IsChangeKeyTime = false;
	}
	
	if( m_KeyIndex <= 1 )
	{
		m_KeyIndex = 1;
	}
	
	if( m_KeyIndex >= m_vKeyTime.size() - 1 )
	{
		m_KeyIndex = 0;
	}
}

//==============================================================================
//�L�[�X�s�[�h�̕ύX
//==============================================================================
//[input]
//	pCtrl:�R���g���[���[�p�f�o�C�X
//==============================================================================
void CEnemy::ChangeKeySpeed( ::Peripheral::IInputController *pCtrl )
{
	if( pCtrl->GetState( BUTTON_STATE_HOLD,  BUTTON_AXIS1_LEFT ) )
	{
		m_fKeySpeed -= 0.01f;
	}
	
	else if( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
	{
		m_fKeySpeed += 0.01f;
	}
}





//==============================================================================
//�A�j��ID�̐ݒ�
//==============================================================================
//[input]
//	index:�C���f�b�N�X
//	animID:�ݒ肷��A�j��ID
//==============================================================================
void CEnemy::SetAnimationID(eAnimType index, int animID)
{
	m_AnimID[index] = animID;
}





