//*============================================================================
//FontSprite.h
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
#include "draw2dobject.h"
#include <vector>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	フォントスプライト描画用オブジェクト
//=============================================================================
class CFontSprite :	public Draw2DObject
{
	private:
		
		Renderer::Object::IFontSprite2D *m_pFontSpr;//フォントスプライト用ハンドル
		string m_Str;//表示する文字
		Math::Vector2D m_vOldPos;//旧座標
		vector<string> m_vecText;//会話テキスト
		
		CColor m_FontColor;//フォント色
		
		Uint32 m_StrCount;//文字カウンタ
		Uint32 m_RefCount;//文字の参照カウンタ
		
		bool m_IsTextEnd;//テキスト終了フラグ
		
	
	public:
	
		CFontSprite( string name );//コンストラクタ
		CFontSprite( string name, Math::Vector2D vPos );//コンストラクタ
		
		virtual ~CFontSprite(void);//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		bool DrawNovelStyle( ICore *pCore, Selene::Peripheral::IInputController *pCtrl );//一文字ずつ表示
		void DrawMultiLine( );//複数文字列の描画
		void DrawMultiLine( Math::Point2DF vPos[] );//複数文字列の描画
		
		void Load( Renderer::IRender *pRender );//読み込み
		
	public:
	
		void SetDrawString( string str );//描画する文字の設定
		
		/*複数文字列の描画設定*/
		void SetVecTextChat( vector<string> vecStr )
		{
			m_vecText = vecStr;
		}
		
		/*文字参照カウンタの増加*/
		void SetRefCount( Uint32 count) 
		{
			m_RefCount = count;
		}
		
		/*テキスト終了フラグの設定*/
		void SetTextEndFlag( bool flag )
		{
			m_IsTextEnd = flag;
		}
		
		/*文字カウンタの設定*/
		void SetStrCount( Uint32 count )
		{
			m_StrCount = count;
		}
		
		/*フォント色の設定*/
		void SetFontColor( CColor color )
		{
			m_FontColor = color;
		}
		
	public:
	
		//フォントスプライト用ハンドルの取得
		Renderer::Object::IFontSprite2D *GetFontSprite() const
		{
			return m_pFontSpr;
		}
		
		/*表示する文字の取得*/
		string GetDrawString() 
		{
			return m_Str;
		}
		
		
		/*テキスト終了フラグの取得*/
		bool GetTextEndFlag() const
		{
			return m_IsTextEnd;
		}
		
		/*文字カウンタの取得*/
		Uint32 GetStrCount()
		{
			return m_StrCount;
		}
	
		
	
};
