//*============================================================================
//Menu.h
//*============================================================================
//[history]
//	08/03/05　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "FontSprite.h"
#include "Sprite.h"

//=============================================================================
//enum
//=============================================================================
enum eSelectType
{
	SELECT_YES,
	SELECT_NO,
	SELECT_NONE,
};


//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	メニュー用
//=============================================================================
class CMenu : public  CGameObject
{
	private:
	
		CFontSprite *m_pFontSpr;//フォントスプライト
		CSprite *m_pSpr;//スプライト
		
		string m_CaptionName;//キャプション名
		Renderer::IRender *m_pRender;//レンダラー用デバイス
	
	private:
	
		bool m_IsPopUp;//メニューがポップアップしているか
		bool m_IsYesNoOrder;//はい・いいえの順番かどうか
		Sint32 m_Cursor;//カーソル
		
	public:
	
		CMenu( CFontSprite *pFontSpr, CSprite *pSpr );//コンストラクタ
		~CMenu();//デストラクタ
		
		void Init();//初期化
		void Rendering();//レンダリング
		void Exec();//処理
		
		eSelectType SelectYesNo( Selene::Peripheral::IInputController *pCtrl );//選択肢の選択
		
	public:
	
		//スプライトの設定		
		void SetSprite( CSprite *pSpr )
		{
			m_pSpr = pSpr;
		}
		
		//フォントスプライトの設定		
		void SetFontSprite( CFontSprite *pFontSpr )
		{
			m_pFontSpr = pFontSpr;
		}
		
		/*メニューポップアップフラグの設定*/
		void SetPopUp( bool flag )
		{	
			m_IsPopUp = flag;
		}
		
		void SetYesNoOrderFlag( bool flag )
		{
			m_IsYesNoOrder = flag;
		}
		
		/*キャプション名の設定*/
		void SetCaptionName( string name )
		{
			m_CaptionName = name;
		}
		
		/*レンダラー用デバイスの設定*/
		void SetRenderer( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
			pRender->AddRef();
		}
		
	public:
	
		/*メニューポップアップフラグの取得*/
		bool GetPopUpFlag(  )
		{	
			return m_IsPopUp;
		}
		
		/*カーソル番号の取得*/
		Sint32 GetCursorNo()
		{
			return m_Cursor;
		}
	
		
};