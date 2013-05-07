//*============================================================================
//camera.h
//*============================================================================
//[history]
//	08/03/11　修正
//[author]
//	Taka
//============================================================================

//二重インクルード防止
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[desc]
//	カメラ用クラス
//=============================================================================
class CCamera :public CGameObject
{
	private:
	
		Scene::ICamera *m_pCamera;//カメラデバイス
		
	private:
	
		Math::Vector3D m_vPos;//位置
		Math::Vector3D m_vTarget;//ターゲット
		Math::Vector3D m_vRot;//回転角度
		Math::Style	   m_Style;//姿勢データ
		
		bool m_IsChangeTopView;//トップビュー切り替え判定フラグ
	
	public:
	

		CCamera();//コンストラクタ
		~CCamera();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
	public:
	
		void SetCamera( Scene::ISceneManager *pScene );//カメラのセット
		//void SetCamera( Scene::ICustomizedSceneManager *pScene );//カメラのセット
		
		void SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height );//プロジェクションの設定
		void SetTransform( Math::Style style );//変形の適用	
		void SetTransform( );//変形の適用
		void SetTransform2();//変形の適用
		void SetTransform3();//変形の適用
		void SetTransformDemo();//デモ用のカメラ移動
		void SetPosition( Math::Vector3D vPos );//位置の設定
		void SetAngle( Sint32 Angle );//角度の設定
		void SetTargetPos( Math::Vector3D vTarget );//ターゲットの位置セット
		void SetStyle( Math::Style style );//姿勢データ設定		
		void SetRotate( Math::Vector3D vRot );//角度の設定
		
		/*トップビューフラグの設定*/
		void SetTopViewFlag( bool flag)
		{
			m_IsChangeTopView = flag;
		}
	
		
	/*Get系*/
	public:
	
		//カメラデバイスの取得
		Scene::ICamera *GetCamera()
		{
			return m_pCamera;
		}
		
		//位置の取得		
		Math::Vector3D GetPosition()
		{
			return m_vPos;
		}
		//ターゲットの取得
		Math::Vector3D GetTarget()
		{
			return m_vTarget;
		}
		
		//姿勢データの取得		
		Math::Style GetStyle()
		{
			return m_Style;
		}
		
		//回転角度の設定
		Math::Vector3D GetRotate()
		{
			return m_vRot;
		}
		
		/*トップビュー判定フラグの取得*/
		bool GetTopViewFlag()
		{
			return m_IsChangeTopView;
		}

		
		
		
		
		
};