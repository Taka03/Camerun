//*============================================================================
//FontSprite3D.h
//*============================================================================
//[history]
//	08/03/16 作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "c3dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	フォントスプライト描画用オブジェクト
//=============================================================================
class CFontSprite3D :	public CDraw3DObject
{
	private:
		
		Renderer::Object::IFontSprite3D *m_pFontSpr;//フォントスプライト用ハンドル
		Scene::ISpriteActor *m_pActorSprite[S_MAX];//スプライトアクター
		string m_Str;//表示する文字
	
	public:
	
		CFontSprite3D( string name );//コンストラクタ
		CFontSprite3D( string name, Math::Vector3D vPos );//コンストラクタ
		
		virtual ~CFontSprite3D(void);//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		void Load( Renderer::IRender *pRender );//読み込み
		
	public:
	
		void SetDrawString( string str );//描画する文字の設定
		
	public:
	
		//フォントスプライト用ハンドルの取得
		Renderer::Object::IFontSprite3D *GetFontSprite() const
		{
			return m_pFontSpr;
		}
		
	
};
