//*============================================================================
//Photo.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/04/01  スプライトの継承に変更
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	写真用クラス
//=============================================================================
class CPhoto :public CSprite
{
	private:
	
		bool m_IsExist;//写真にターゲットが存在するか
		float m_fTargetDistance;//ターゲットの大きさ
		Math::Vector3D m_vTargetPos;//ターゲットの位置
		
	public:
	
		CPhoto(void);//コンストラクタ
		CPhoto( string name, Math::Vector2D vPos );//コンストラクタ
		
	/*Set系*/
	public:
	
		void SetTargetDistance( float fDistance );//ターゲットの大きさのセット
		void SetExistFlag( bool flag );//ターゲット存在フラグの設定
		void SetTargetPos( Math::Vector3D vPos );//ターゲットの位置の設定
		void SavePhoto();//写真の保存

	/*Get系*/
	public:
	
		//ターゲットの大きさの取得
		float GetTargetDistance()
		{
			return m_fTargetDistance;
		}
		
		//ターゲットの位置の取得		
		Math::Vector3D GetTargetPosition()
		{
			return m_vTargetPos;
		}
		
		/*ターゲット存在フラグの取得*/
		bool GetExistFlag( )
		{
			return m_IsExist;
		}
		
};
