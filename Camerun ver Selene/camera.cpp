//*============================================================================
//camera.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "camera.h"

//=============================================================================
//コンストラクタ
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
//デストラクタ
//=============================================================================
CCamera::~CCamera()
{
	SAFE_RELEASE( m_pCamera ); 
}

//=============================================================================
//初期化
//=============================================================================
void CCamera::Init()
{
	m_vPos.Set( 0, 50.0f, 50.0f );
	m_vRot.Set( -15, 0, 0 );
	
}

//=============================================================================
//処理
//=============================================================================
void CCamera::Exec()
{

}


//=============================================================================
//カメラのセット
//=============================================================================
//[input]
//	pScene:シーン管理デバイス
//=============================================================================
void CCamera::SetCamera( Scene::ISceneManager *pScene )
{
	/*シーンからカメラを取得*/
	m_pCamera = pScene->GetCamera();
	
}

//=============================================================================
//カメラのセット
//=============================================================================
//[input]
//	pScene:シーン管理デバイス
//=============================================================================
//void CCamera::SetCamera( Scene::ICustomizedSceneManager *pScene )
//{
//	/*シーンからカメラを取得*/
//	m_pCamera = pScene->GetCamera();
//	
//}




//=============================================================================
//プロジェクションの設定
//=============================================================================
//[input]
//	fNear:近Z平面クリップ
//	fFar:遠Z面クリップ
//	fov:視野角
//	Width:画面幅
//	Height:画面高さ
//=============================================================================
void CCamera::SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height )
{
	if( m_pCamera != NULL )
	{
		m_pCamera->UpdateProjection( fNear, fFar, DEG_TO_ANGLE(fov), Width, Height );
	}
}

//=============================================================================
//変形の設定
//=============================================================================
//[input]
//	style:姿勢データ
//=============================================================================
void CCamera::SetTransform( Math::Style style )
{
	if( m_pCamera != NULL )
	{
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ちょっとずつ近づく感じに
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		
		m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform2( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
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

		/*ちょっとずつ近づく感じに*/
		m_vPos = vCameraTarget;
		
		// カメラのトランスフォーム
		m_Style.TransformReset();
		
		//m_Style.RotationX( m_vRot.x );
		//m_Style.GetStyle
		//m_Style.RotationY( m_vRot.y );

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform3( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 100.0f, 0.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ちょっとずつ近づく感じに
		m_vPos = vCameraTarget;

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransformDemo()
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_vRot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_vRot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_vRot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ちょっとずつ近づく感じに
		if( vCameraTarget.y > 3.0 )
		{	
			m_vPos.y =  m_vTarget.y + 3;
			mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
			vDirection.TransformNormal( mTemp );
		}
		
		m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}





//=============================================================================
//位置の設定
//=============================================================================
//[input]
//	vPos:位置
//=============================================================================
void CCamera::SetPosition( Math::Vector3D vPos )
{
	m_vPos = vPos;
}

//=============================================================================
//回転角度の設定
//=============================================================================
//[input]
//	Angle:角度
//=============================================================================
void CCamera::SetRotate( Math::Vector3D vRot )
{
	m_vRot = vRot;
}

//=============================================================================
//ターゲットの設定
//=============================================================================
//[input]
//	vTarget:ターゲットの位置
//=============================================================================
void CCamera::SetTargetPos( Math::Vector3D vTarget )
{
	m_vTarget = vTarget;
}

//=============================================================================
//姿勢データ設定	
//=============================================================================
//[input]
//	style:姿勢データ
//=============================================================================
void CCamera::SetStyle( Math::Style style )	
{
	m_Style = style;
}



