//*============================================================================
//character.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "character.h"


//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//=============================================================================
CCharacter::CCharacter( string name ) :m_pModel(NULL)
{
	m_DataName = name;
	
	m_vPos.Set( 0, 0, 0 );
	m_vRot.Set( 0, 0, 0 );
	m_vScale.Set( 15, 15, 15 );
	
	m_IsVisible = true;
	m_IsStop	= false;	
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�ݒ肷����W
//=============================================================================
CCharacter::CCharacter( string name, Math::Vector3D vPos ) :m_pModel(NULL), m_pRigidBody(NULL)
{
	m_DataName = name;
	
	m_IsVisible = true;
	m_IsStop	= false;
	m_IsSetFlag = false;	
	m_eType = OBJ_OTHER;
	
	
	m_vPos = vPos;
	m_vRot.Set( 0, 0, 0 );
	m_vScale.Set( 1, 1, 1 );
	
	
	
	m_vOldPos = vPos;
	m_vSetFlagPos.Set( 0, 0, 0 );
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	m_fSpeed = 0.0f;
	
	m_fWeight = 0.0f;
	
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		SAFE_RELEASE( m_pActorModel[numActor] ); 
	}
	
	SAFE_RELEASE( m_pModel );
	
}

//=============================================================================
//����
//=============================================================================
void CCharacter::Init()
{
	
}



//=============================================================================
//����
//=============================================================================
void CCharacter::Exec()
{
	m_vArrowPos = m_vPos + Math::Vector3D( 0, 1, 0 );
	
	/*�p���̃��Z�b�g*/
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->RotationX( toI( -m_vRot.y ) );
	
	
	m_pActorModel[m_ActorIndex]->RotationY( toI(m_vRot.x) - DEG_TO_ANGLE(90) );
	
	/*�g��k��*/
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	/*�ړ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	/*�p���̍X�V*/
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
	//m_pRigidBody->SetPosition( m_vPos );
	
//	m_pRigidBody->SetRotation( m_vRot.y );	
	
}

//=============================================================================
//�����_�����O
//=============================================================================
//[input]
//	index:�C���f�b�N�X�ɐݒ肷��l
//=============================================================================
void CCharacter::Rendering( int index )
{
	m_pActorModel[index]->RenderingRequest();
}

//=============================================================================
//�Q�ƃJ�E���^�̑���
//=============================================================================
void CCharacter::AddRef()
{
	m_pModel->AddRef();
	
	for( int actornum = 0;actornum < S_MAX;++actornum )
	{
		m_pActorModel[actornum]->AddRef();
	}	
}



//=============================================================================
//�t�@�C���ǂݍ���
//=============================================================================
//[input]
//	pRender:�����_�����O�p�I�u�W�F�N�g
//=============================================================================
void CCharacter::Load( Renderer::IRender *pRender )
{
	if( !m_DataName.empty() ) 
	{
		m_pModel = pRender->CreateModelFromFile( m_DataName.c_str() );
	}
}

//==============================================================================
//�A�N�^�[�̐���
//==============================================================================
//[input]
//	index:��������A�N�^�[�C���f�b�N�X
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CCharacter::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	if( m_pModel != NULL )
	{
		m_pActorModel[index] = pSceneMgr->CreateActor( m_pModel );
	}
}

//=============================================================================
//�R���W�����f�[�^�̍쐬
//=============================================================================
void CCharacter::CreateCollision()
{
	this->GetModelActor(S_MAIN)->Collision_Create();
}


//==============================================================================
//�����`�F�b�N
//==============================================================================
//[input]
//	pChara:�`�F�b�N����L�����N�^�[
//[return]
//	����
//==============================================================================
float CCharacter::CheckDistance( CCharacter *pChara )
{
	Math::Vector3D vDirection = pChara->GetPosition() - m_vPos;
	
	return vDirection.Length();
	
}


//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N����}�b�v�A�N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck( Scene::IMapActor *pActor )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
		m_fGravity = 1.0f;
	}
	
	if( m_fGravity > 0.0f )
	{
		//m_AnimID[ANIM_NOW] = 2;
		
	}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	#if defined(DEBUG_MAP)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pActor->HitCheckByRay( vRay, Ret ) )
	{
		// �Փˈʒu�Ɉړ�
		m_vPos = Ret.vHitPosition;
		// �d�͉���������
		m_fGravity = 0.0f;
		
		return true;
	}
	
	return false;

}

//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N����}�b�v�A�N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck2( Scene::IMapActor *pActor )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
		m_fGravity = 1.0f;
	}
	
	if( m_fGravity > 0.0f )
	{
		//m_AnimID[ANIM_NOW] = 2;
		
	}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	m_vPos.y -= m_fGravity;
	
	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.1f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pActor->HitCheckByRay( vRay, Ret ) )
	{
		// �Փˈʒu�Ɉړ�
		m_vPos = Ret.vHitPosition;
		// �d�͉���������
		m_fGravity = 0.0f;
		
		
		return true;
	}
	
	
	return false;

}

//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara, int index )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	
	//if ( m_fGravity > 1.0f )
	//{
	//	// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.5f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(index)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// �Փˈʒu�Ɉړ�
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
			
			//m_vDirection += pChara->GetSpeed();
			// �d�͉���������
			m_fGravity = 0.0f;
		}
		
		return true;
	}
	
	return false;

}

//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	//
	//if ( m_fGravity > 1.0f )
	//{
	//	// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,5.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(S_MAIN)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// �Փˈʒu�Ɉړ�
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
		
		
		//m_vDirection += pChara->GetSpeed();
		// �d�͉���������
		
			return true;
		}
	}
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( CCharacter *pChara )
{
	if( this->GetModelActor(S_MAIN)->Collision_Check( pChara->GetModelActor( S_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input/output]
//	ppChara:���肷��L�����N�^�[
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( CDraw3DObject **ppChara )
{
	CCharacter *obj = dynamic_cast<CCharacter *>( *ppChara );
	
	if( this->GetModelActor(S_MAIN)->Collision_Check( obj->GetModelActor( S_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	vRay:����p�̃��C
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay )
{
	if( this->GetModelActor(S_MAIN)->HitCheckByRay( vRay ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փˌ��ʊi�[�p
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	if( this->GetModelActor(S_MAIN)->HitCheckByRay( vRay, Out ) )
	{
		return true;
	}	
	
	return false;
}


//=============================================================================
//���̃��f���̐���
//=============================================================================
//[input]
//	pWorld:�����V�~�����[�V�����p�f�o�C�X
//=============================================================================
void CCharacter::CreateRigidModel( Dynamics::ISimulationWorld *pWorld )
{
	m_pRigidModel = pWorld->CreateModel( m_pModel, true );
	
//	m_pRigidBody = pWorld->( m_pModel, true );
}


//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�C���f�b�N�X�ɐݒ肷��l
//=============================================================================
void CCharacter::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

//=============================================================================
//�t���O�ݒu����t���O�̃Z�b�g
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
//=============================================================================
void CCharacter::SetFlag( bool flag )
{
	m_IsSetFlag = flag;
}

//=============================================================================
//�����W�̐ݒ�
//=============================================================================
//[input]
//	vPos:�ݒ肷����W
//=============================================================================
void CCharacter::SetOldPosition( Selene::Math::Vector3D vPos )
{
	m_vOldPos = vPos;
}


















