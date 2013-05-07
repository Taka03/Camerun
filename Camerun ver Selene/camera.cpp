//*============================================================================
//camera.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "camera.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCamera::CCamera() :m_pCamera(NULL)
{
	m_IsVisible = true;
	m_IsStop	= false;
	
	m_vPos.Set( 0, 50.0f, 50.0f );
	m_vRot.Set( -15, 0, 0 );
	
	m_IsChangeTopView = false;
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
	SAFE_RELEASE( m_pCamera ); 
}

//=============================================================================
//������
//=============================================================================
void CCamera::Init()
{
	m_vPos.Set( 0, 50.0f, 50.0f );
	m_vRot.Set( -15, 0, 0 );
	
}

//=============================================================================
//����
//=============================================================================
void CCamera::Exec()
{

}


//=============================================================================
//�J�����̃Z�b�g
//=============================================================================
//[input]
//	pScene:�V�[���Ǘ��f�o�C�X
//=============================================================================
void CCamera::SetCamera( Scene::ISceneManager *pScene )
{
	/*�V�[������J�������擾*/
	m_pCamera = pScene->GetCamera();
	
}

//=============================================================================
//�J�����̃Z�b�g
//=============================================================================
//[input]
//	pScene:�V�[���Ǘ��f�o�C�X
//=============================================================================
//void CCamera::SetCamera( Scene::ICustomizedSceneManager *pScene )
//{
//	/*�V�[������J�������擾*/
//	m_pCamera = pScene->GetCamera();
//	
//}




//=============================================================================
//�v���W�F�N�V�����̐ݒ�
//=============================================================================
//[input]
//	fNear:��Z���ʃN���b�v
//	fFar:��Z�ʃN���b�v
//	fov:����p
//	Width:��ʕ�
//	Height:��ʍ���
//=============================================================================
void CCamera::SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height )
{
	if( m_pCamera != NULL )
	{
		m_pCamera->UpdateProjection( fNear, fFar, DEG_TO_ANGLE(fov), Width, Height );
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
//[input]
//	style:�p���f�[�^
//=============================================================================
void CCamera::SetTransform( Math::Style style )
{
	if( m_pCamera != NULL )
	{
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ������Ƃ��߂Â�������
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		
		m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform2( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 0.5f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		//mTemp.Translation(0, -0.1, 0);
		//vDirection.TransformCoord( mTemp );		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		/*������Ƃ��߂Â�������*/
		m_vPos = vCameraTarget;
		
		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();
		
		//m_Style.RotationX( m_vRot.x );
		//m_Style.GetStyle
		//m_Style.RotationY( m_vRot.y );

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform3( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 100.0f, 0.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ������Ƃ��߂Â�������
		m_vPos = vCameraTarget;

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransformDemo()
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ������Ƃ��߂Â�������
		if( vCameraTarget.y > 3.0 )
		{	
			m_vPos.y =  m_vTarget.y + 3;
			mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
			vDirection.TransformNormal( mTemp );
		}
		
		m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}





//=============================================================================
//�ʒu�̐ݒ�
//=============================================================================
//[input]
//	vPos:�ʒu
//=============================================================================
void CCamera::SetPosition( Math::Vector3D vPos )
{
	m_vPos = vPos;
}

//=============================================================================
//��]�p�x�̐ݒ�
//=============================================================================
//[input]
//	Angle:�p�x
//=============================================================================
void CCamera::SetRotate( Math::Vector3D vRot )
{
	m_vRot = vRot;
}

//=============================================================================
//�^�[�Q�b�g�̐ݒ�
//=============================================================================
//[input]
//	vTarget:�^�[�Q�b�g�̈ʒu
//=============================================================================
void CCamera::SetTargetPos( Math::Vector3D vTarget )
{
	m_vTarget = vTarget;
}

//=============================================================================
//�p���f�[�^�ݒ�	
//=============================================================================
//[input]
//	style:�p���f�[�^
//=============================================================================
void CCamera::SetStyle( Math::Style style )	
{
	m_Style = style;
}



