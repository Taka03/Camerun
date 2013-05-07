//*============================================================================
//CamObject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "CamObject.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//=============================================================================
CCamObject::CCamObject( string name )
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
	
	m_vScale.Set(2.0f, 2.0f, 2.0f);
	
	m_fGravity = 0.0f;
	
	m_ActorIndex = 0;
	
	m_DataName = name;
	

}

//=============================================================================
//������
//=============================================================================
void CCamObject::Init()
{
	m_vPos.Set(0, 10, 0);
	m_vOldPos = m_vPos;
	m_IsVisible = false;
	
	m_vRot.Set(0, 0, 0);
	
}

//=============================================================================
//�ړ�����
//=============================================================================
void CCamObject::MoveExec()
{
	
}


//=============================================================================
//����
//=============================================================================
void CCamObject::Exec()
{
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->LocalTranslation( 0, -0.1f, 0 );

	m_pActorModel[m_ActorIndex]->RotationX( toI( m_vRot.y ) );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( m_vRot.x - DEG_TO_ANGLE(90) ) );

	/*�ړ��̐ݒ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	// �L�����̕ϊ��X�V
	m_pActorModel[m_ActorIndex]->TransformUpdate();
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pCtrl:�R���g���[���[�p�f�o�C�X
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IInputController *pCtrl )
{
	if ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP )  )
	{
		m_vRot.y -= DEG_TO_ANGLE(1);
		//vCharaDirection.y += 1.0f;						
	}
	// ��
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) )
	{
		m_vRot.y += DEG_TO_ANGLE(1);
		
		// �ړ��̓J�����ɑ΂��čs��
		//vCharaDirection.y -= 1.0f;
		
	}
	// �E
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
	{
		m_vRot.x += DEG_TO_ANGLE(1);
		
		// �ړ��̓J�����ɑ΂��čs��
		//vCharaDirection = +vCameraRight;
		//fAnimationTime += 1.0f;
		
	}
	// ��
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT ) )
	{
		m_vRot.x -= DEG_TO_ANGLE(1);
		// �ړ��̓J�����ɑ΂��čs��
		//vCharaDirection = -vCameraRight;
		//fAnimationTime += 1.0f;
		
	}
	
	MoveAdjust();
}
//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pJoy:�W���C�p�b�h�p�f�o�C�X
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IJoystick *pJoy, CCamera *pCam )
{
	//------------------------------------------------
	// �J������̕������擾
	//------------------------------------------------
	Math::Vector3D vCameraFront, vCameraRight;
	// �O
	pCam->GetStyle().GetFront( vCameraFront );
	// �����͍l�����Ȃ�
	vCameraFront.y = 0.0f;
	vCameraFront.Normalize();
	// �E
	pCam->GetStyle().GetRight( vCameraRight );
	// �����͍l�����Ȃ�
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();
	
	
	const float AXIS_MAX = 4096;
	const float AXIS_MIN = -4096;
	
	Math::Vector2D AxisPos( toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_X ) / AXIS_MAX ), toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_Y ) / AXIS_MAX ) );
	
	
	
		/*�O(�󂭓|�����Ƃ�)*/
		if(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -0.7 && AxisPos.y < -0.3) )
		{
			m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			
			m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.Normalize();
			
			
		}
		
		//�O(�[���|�����Ƃ�)
		ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
		{
			m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			
			m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.Normalize();
			
		}
		
		
		/*��*/
		ef( ( AxisPos.x >= -0.2 && AxisPos.x <= 0.2 ) && ( AxisPos.y <= 1.0 && AxisPos.y > 0.7) )
		{
			m_vDirection = -vCameraFront;
			//m_vRot.x -= DEG_TO_ANGLE(180);
			//m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x * 0.01);
			//
			//m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z * 0.01 );
			//
			////m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			//
			//m_vDirection.Normalize();
			
		}
		
		/*��*/
		ef( ( AxisPos.x <= -0.4 && AxisPos.x >= -1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
		{
			m_vRot.x -= DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1 ) + ( -AxisPos.y ) * vCameraFront.x );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1 ) + ( -AxisPos.y ) * vCameraFront.z );
			//m_vDirection.y = 0;
			//
			//m_vDirection.Normalize();
			
			//m_vDirection.x =  ( ( -vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( -vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
		
		/*�E*/
		ef( ( AxisPos.x >= 0.4 && AxisPos.x <= 1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
		{
			m_vRot.x += DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
		
		
		/*���̑�*/
		ef( ( AxisPos.y <= -0.3 ) && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
		{
			m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
			m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.y = 0;
			
			m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
			
			m_vDirection.Normalize();
		}
		
		ef( AxisPos.y >= 0.3 && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
		{
			m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
			m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.y = 0;

			m_vDirection.Normalize();
			
			
		}
		
		if( m_vDirection.LengthSq() > 0.0f)
		{	
			m_vDirection *= 0.1f;
			
			m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
			
//			m_vRot.y = toF( Math::ATan2(
			
			//m_vRot *= m_vDirection;
		}
	
	MoveAdjust();
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pJoy:�W���C�p�b�h�p�f�o�C�X
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IJoystick *pJoy )
{
	const int AXIS_MAX = 4096;
	const int ROTATE_MAX = 32767;
	
	Math::Vector2D AxisPos( toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_Z ) / AXIS_MAX ), toF( pJoy->GetAxis( PAD_AXIS_POSITION_ROTATE, PAD_AXIS_Z ) / ROTATE_MAX ) );
	
		/*��*/
		if(  ( AxisPos.x >= -1.0 && AxisPos.x <= -0.3 ) /*&& ( AxisPos.y >= -0.5 && AxisPos.y < 0.5)*/ )
		{
		
			m_vRot.x -= DEG_TO_ANGLE(1);
			
		}
		
		////�O(�[���|�����Ƃ�)
		//ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
		//{
		//	m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
		//	
		//	m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
		//	m_vDirection.Normalize();
		//	
		//}
		
		
		/*�E*/
		if( ( AxisPos.x > 0.3 && AxisPos.x <= 1.0 ) /*&& ( AxisPos.y <= 1.0 && AxisPos.y > 0.5)*/ )
		{
			
			m_vRot.x += DEG_TO_ANGLE(1);
			//m_vDirection = -vCameraFront;
			//m_vRot.x -= DEG_TO_ANGLE(180);
			//m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x * 0.01);
			//
			//m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z * 0.01 );
			//
			////m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			//
			//m_vDirection.Normalize();
			
		}
		
		/*�O*/
		if( ( AxisPos.y < -0.5 && AxisPos.y >= -1.0 )  )
		{
			m_vRot.y -= DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1 ) + ( -AxisPos.y ) * vCameraFront.x );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1 ) + ( -AxisPos.y ) * vCameraFront.z );
			//m_vDirection.y = 0;
			//
			//m_vDirection.Normalize();
			
			//m_vDirection.x =  ( ( -vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( -vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
		
		/*�E*/
		if( ( AxisPos.y <= 1.0 && AxisPos.y > 0.5 )  )
		{
			m_vRot.y += DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
//		
//		
//		/*���̑�*/
//		ef( ( AxisPos.y <= -0.3 ) && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
//		{
//			m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
//			m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
//			m_vDirection.y = 0;
//			
//			m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
//			
//			m_vDirection.Normalize();
//		}
//		
//		ef( AxisPos.y >= 0.3 && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
//		{
//			m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
//			m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
//			m_vDirection.y = 0;
//
//			m_vDirection.Normalize();
//			
//			
//		}
//		
//		if( m_vDirection.LengthSq() > 0.0f)
//		{	
//			m_vDirection *= 0.1f;
//			
//			m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
//			
////			m_vRot.y = toF( Math::ATan2(
//			
//			//m_vRot *= m_vDirection;
//		}
	
		MoveAdjust();
}




//==============================================================================
//�ړ��␳
//==============================================================================
void CCamObject::MoveAdjust()
{
	if( m_vRot.y >= DEG_TO_ANGLE(89) )
	{
		m_vRot.y = DEG_TO_ANGLE(89);
	}
	
	if( m_vRot.y <= DEG_TO_ANGLE(-89) )
	{
		m_vRot.y = DEG_TO_ANGLE(-89);
		
	}
	
}



