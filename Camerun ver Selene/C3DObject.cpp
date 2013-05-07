//*===========================================================================
//C3DObject.cpp
//*===========================================================================

//============================================================================
//include
//============================================================================
#include "C3DObject.h"
#include <string>

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
CDraw3DObject::CDraw3DObject( string name ) :m_pRigidModel(NULL), m_pShader(NULL)
{
	m_IsVisible = true;
	
	m_DataName = name;
	
	m_vPos.Set( 0, -1, -2 );
	m_vRot.Set( 0, 0, 0 );
	
	m_vScale.Set( 1.0f, 1.0f, 1.0f );
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDraw3DObject::~CDraw3DObject(void)
{
//	SAFE_RELEASE( m_pRigidModel );
	
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		SAFE_DELETE( obj );
	}
	
}

//=============================================================================
//������
//=============================================================================
void CDraw3DObject::Init()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		i->gameobj->Init();
	}
}


//=============================================================================
//����
//=============================================================================
void CDraw3DObject::Exec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		i->gameobj->Exec();
	}
	
}

//=============================================================================
//����
//=============================================================================
void CDraw3DObject::MoveExec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast< CDraw3DObject * >( i->gameobj );
		
		if( !obj->GetStopFlag() )
		{	
			obj->MoveExec();
		}
	}
	
}



//=============================================================================
//�����_�����O
//=============================================================================
//[input]
//	index:�C���f�b�N�X�ɐݒ肷��l
//=============================================================================
void CDraw3DObject::Rendering(int index)
{
	list<ListData>::iterator i = m_ObjectList.begin();
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( obj->GetVisibleFlag() )
		{	
			obj->Rendering(index);
		}
		
		#if defined(NDEBUG)
		
			
		
		#endif
	}
	
}

//=============================================================================
//�t�@�C���ǂݍ���
//=============================================================================
//[input]
//	pRender:�����_�����O�p�f�o�C�X
//=============================================================================
void CDraw3DObject::Load( Renderer::IRender *pRender )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->Load( pRender );
			
	}
	
}

//=============================================================================
//�V�F�[�_�[�ǂݍ���
//=============================================================================
//[input]
//	pRender:�����_�����O�p�f�o�C�X
//	name:�f�[�^��
//=============================================================================
void CDraw3DObject::LoadShader( Renderer::IRender *pRender, string name )
{
	m_pShader = pRender->CreateShaderFromFile( name.c_str() );
}


//=============================================================================
//�A�N�^�[�̐���
//=============================================================================
//[input]
//	pSceneMgr:�V�[���Ǘ��p�f�o�C�X
//=============================================================================
void CDraw3DObject::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateActor( index, pSceneMgr );		
	
	}
	
}

//=============================================================================
//���̃��f���̐���
//=============================================================================
//[input]
//	pWorld:�����V�~�����[�V�����p�f�o�C�X
//=============================================================================
void CDraw3DObject::CreateRigidModel( Dynamics::ISimulationWorld *pWorld )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateRigidModel( pWorld );
			
	}
	
}

//=============================================================================
//�R���W�����f�[�^�̍쐬
//=============================================================================
void CDraw3DObject::CreateCollision()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		obj->CreateCollision();
			
	}
	
}


//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input/output]
//	ppChara:���肷��L����
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( CDraw3DObject **ppChara )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( obj->GetObjectType() == OBJ_PLAYER && obj->GetObjectType() == OBJ_ENEMY )
		{
			if( this->HitCheck( &obj ) )
			{
				*ppChara = obj;
				return true;
			}
		}
			
	}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay ) )
		{
			return true;
		}
	}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	ppHitObj:���������I�u�W�F�N�g�̎擾
//[output]
//	obj:�Փ˂����I�u�W�F�N�g	
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay ) )
		{
			*ppHitObj = pChara;
			return true;
		}
	}
	
	return false;
}


//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փ˔���̌���
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay, Out ) )
		{
			return true;
		}
	}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փ˔���̌���
//[output]
//	ppHitObj:���������I�u�W�F�N�g
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->HitCheck( vRay, Out ) )
		{
			*ppHitObj = pChara;
			
			return true;
		}
	}
	
	return false;
}



//=============================================================================
//�t���b�V���𗁂т���Ԃ̏���
//=============================================================================
void CDraw3DObject::FlashedState(  )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( pChara->GetObjectType() == OBJ_ENEMY )
		{
			pChara->FlashedState();
		}	
	}
}

////=============================================================================
////�t���O�̉��
////=============================================================================
//void CDraw3DObject::RecallFlag( Selene::Peripheral::IInputController *m_pCtrl )
//{
//	list<ListData>::iterator i;
//	
//	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
//	{
//		CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
//		
//		if( pChara->GetObjectType() == OBJ_ENEMY )
//		{
//			pChara->RecallFlag( m_pCtrl );
//		}	
//	}
//}





//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�C���f�b�N�X�ɐݒ肷��l
//=============================================================================
void CDraw3DObject::SetActorIndex( int index )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
		
		if( index == S_MAIN || index == S_SUB )
		{
			obj->SetActorIndex( index );
		}
	}
	
}


//=============================================================================
//�A�N�^�[�̃Z�b�g
//=============================================================================
//[input]
//	style:�p���f�[�^
//=============================================================================
//void CDraw3DObject::SetActor( Selene::Math::Style *pStyle )
//{
//	list<ListData>::iterator i;
//	
//	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
//	{
//		CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
//		
//		obj->SetActor( pStyle );		
//	
//	}
//	
//}





