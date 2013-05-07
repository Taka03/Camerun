//*============================================================================
//DrawObject.h
//*============================================================================
//[history]
//	08/03/03 修正開始
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	描画用オブジェクト
//=============================================================================
class CDrawObject :	public CGameObject
{
	protected:
	
		Math::Vector3D m_vPos; //座標
		Math::Vector3D m_vRot;//角度
		Math::Vector3D m_vScale;//拡縮
		
		string m_DataName;//データ名
		
	public:
	
		CDrawObject(void){};//コンストラクタ
		CDrawObject( string name );//コンストラクタ
		virtual ~CDrawObject(void){};//デストラクタ
		
		virtual void Init(){};//初期化
		virtual void Exec(){};//処理
		virtual void Rendering(int index){};//レンダリング
		virtual void Rendering( ){};//レンダリング
		
		virtual void Load(Renderer::IRender *pRender){};//ファイル読み込み
		
	public:
	
		void SetPosition( Math::Vector3D vPos );//位置の設定
		void SetRotate( Math::Vector3D vRot );//回転角度の設定
		void SetScale( Math::Vector3D vScale );//拡縮の取得
		
	public:
	
		Math::Vector3D GetPosition();//位置の取得
		Math::Vector3D GetRotate();//回転角度の取得
		Math::Vector3D GetScale();//拡縮の取得
		
		string GetFileName()
		{
			return m_DataName;
		}
		
};
