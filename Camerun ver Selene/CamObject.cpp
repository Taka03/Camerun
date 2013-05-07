//*============================================================================
//CamObject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "CamObject.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
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
//初期化
//=============================================================================
void CCamObject::Init()
{
	m_vPos.Set(0, 10, 0);
	m_vOldPos = m_vPos;
	m_IsVisible = false;
	
	m_vRot.Set(0, 0, 0);
	
}

//=============================================================================
//移動処理
//=============================================================================
void CCamObject::MoveExec()
{
	
}


//=============================================================================
//処理
//=============================================================================
void CCamObject::Exec()
{
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->LocalTranslation( 0, -0.1f, 0 );

	m_pActorModel[m_ActorIndex]->RotationX( toI( m_vRot.y ) );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( m_vRot.x - DEG_TO_ANGLE(90) ) );

	/*移動の設定*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	// キャラの変換更新
	m_pActorModel[m_ActorIndex]->TransformUpdate();
}

//==============================================================================
//移動処理
//==============================================================================
//[input]
//	pCtrl:コントローラー用デバイス
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IInputController *pCtrl )
{
	if ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP )  )
	{
		m_vRot.y -= DEG_TO_ANGLE(1);
		//vCharaDirection.y += 1.0f;						
	}
	// 後
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) )
	{
		m_vRot.y += DEG_TO_ANGLE(1);
		
		// 移動はカメラに対して行う
		//vCharaDirection.y -= 1.0f;
		
	}
	// 右
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
	{
		m_vRot.x += DEG_TO_ANGLE(1);
		
		// 移動はカメラに対して行う
		//vCharaDirection = +vCameraRight;
		//fAnimationTime += 1.0f;
		
	}
	// 左
	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT ) )
	{
		m_vRot.x -= DEG_TO_ANGLE(1);
		// 移動はカメラに対して行う
		//vCharaDirection = -vCameraRight;
		//fAnimationTime += 1.0f;
		
	}
	
	MoveAdjust();
}
//==============================================================================
//移動処理
//==============================================================================
//[input]
//	pJoy:ジョイパッド用デバイス
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IJoystick *pJoy, CCamera *pCam )
{
	//------------------------------------------------
	// カメラ基準の方向を取得
	//------------------------------------------------
	Math::Vector3D vCameraFront, vCameraRight;
	// 前
	pCam->GetStyle().GetFront( vCameraFront );
	// 高さは考慮しない
	vCameraFront.y = 0.0f;
	vCameraFront.Normalize();
	// 右
	pCam->GetStyle().GetRight( vCameraRight );
	// 高さは考慮しない
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();
	
	
	const float AXIS_MAX = 4096;
	const float AXIS_MIN = -4096;
	
	Math::Vector2D AxisPos( toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_X ) / AXIS_MAX ), toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_Y ) / AXIS_MAX ) );
	
	
	
		/*前(浅く倒したとき)*/
		if(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -0.7 && AxisPos.y < -0.3) )
		{
			m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			
			m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.Normalize();
			
			
		}
		
		//前(深く倒したとき)
		ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
		{
			m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
			
			m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
			m_vDirection.Normalize();
			
		}
		
		
		/*後*/
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
		
		/*左*/
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
		
		/*右*/
		ef( ( AxisPos.x >= 0.4 && AxisPos.x <= 1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
		{
			m_vRot.x += DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
		
		
		/*その他*/
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
//移動処理
//==============================================================================
//[input]
//	pJoy:ジョイパッド用デバイス
//==============================================================================
void CCamObject::Move( Selene::Peripheral::IJoystick *pJoy )
{
	const int AXIS_MAX = 4096;
	const int ROTATE_MAX = 32767;
	
	Math::Vector2D AxisPos( toF( pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_Z ) / AXIS_MAX ), toF( pJoy->GetAxis( PAD_AXIS_POSITION_ROTATE, PAD_AXIS_Z ) / ROTATE_MAX ) );
	
		/*左*/
		if(  ( AxisPos.x >= -1.0 && AxisPos.x <= -0.3 ) /*&& ( AxisPos.y >= -0.5 && AxisPos.y < 0.5)*/ )
		{
		
			m_vRot.x -= DEG_TO_ANGLE(1);
			
		}
		
		////前(深く倒したとき)
		//ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
		//{
		//	m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
		//	
		//	m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
		//	m_vDirection.Normalize();
		//	
		//}
		
		
		/*右*/
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
		
		/*前*/
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
		
		/*右*/
		if( ( AxisPos.y <= 1.0 && AxisPos.y > 0.5 )  )
		{
			m_vRot.y += DEG_TO_ANGLE(1.5);
			
			//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
			//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
			
		}
//		
//		
//		/*その他*/
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
//移動補正
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



