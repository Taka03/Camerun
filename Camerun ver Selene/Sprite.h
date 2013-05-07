//*============================================================================
//Sprite.h
//*============================================================================
//[history]
//	08/03/19　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "draw2dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	スプライト描画用オブジェクト
//=============================================================================
class CSprite :	public Draw2DObject
{
	private:
	
		bool m_IsMissionVisible;//ミッションで表示させるかどうか
	
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//テクスチャ用ハンドル
		Selene::Renderer::Object::ISprite2D *m_pSpr;//スプライト用ハンドル
	
	protected:
	
		Math::Point2DI m_Divnum;//分割数
		Math::Point2DI m_Anim;//アニメID
	
		Sint32 m_Width;//幅
		Sint32 m_Height;//高さ
		
	public:
	
		CSprite(){};
		CSprite( string name );//コンストラクタ
		CSprite( string name, Math::Vector2D vPos );//コンストラクタ
		~CSprite(void);//デストラクタ
		
		virtual void Load( Renderer::IRender *pRender );//ファイル読み込み

		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		void DrawMultiGraph( Math::Point2DF pos[], Math::Point2DF AnimID[],  int DrawNum );//複数の描画
		void DrawGrayScale( Renderer::IRender *pRender );//グレースケール描画
		void DrawAnimation( int animNum, int animTime );//アニメーションの描画
		void Move();//移動
		
	/*Set系*/
	public:
	
		//分割数の設定	
		void SetDivnum( Math::Point2DI divnum )
		{
			m_Divnum = divnum;
		}
		
		//アニメーションIDの設定
		void SetAnimID( Math::Point2DI anim )
		{
			m_Anim = anim;
		}
		
		/*画像サイズの設定*/
		void SetGraphSize( Math::Point2DI Size )
		{
			m_Width = Size.x;
			m_Height = Size.y;
		}
		
		/*ミッションでの表示フラグを設定*/
		void SetMissionVisible( bool flag )
		{
			m_IsMissionVisible = flag;	
		}
		
	/*Get系*/
	public:

		//テクスチャ用ハンドルの取得
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//スプライト用ハンドルの取得
		Selene::Renderer::Object::ISprite2D *GetSprite() const
		{
			return m_pSpr;
		}
		
		/*画像幅の取得*/
		Sint32 GetWidth() const
		{
			return m_Width;
		}
		
		/*画像高さの取得*/
		Sint32 GetHeight() const
		{
			return m_Height;
		}
		
		/*ミッションでの表示判定フラグの設定*/
		bool GetMissionVisible()
		{
			return m_IsMissionVisible;
		}
		
		
};
