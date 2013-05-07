//*============================================================================
//Game.h
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
#include "Selene.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//class
//=============================================================================
//[desc]
//	ゲーム用クラス
//=============================================================================
class CGame
{
	private:
	
		ICore	*m_pCore;//コアデバイス
		IGraphicCard	*m_pGraphicCard;//グラフィックカードデバイス
		File::IFileManager	*m_pFileMgr;//ファイル管理デバイス
		Renderer::IRender	*m_pRender;//レンダラー用デバイス
		
	private:
	
		const Sint32 m_ScreenWidth;//画面幅
		const Sint32 m_ScreenHeight;//画面高さ
		
	public:
		CGame(void);//コンストラクタ
		~CGame(void);//デストラクタ
		
	public:
	
		void CreateCore();//コアの生成
		bool Initialize();//初期化
		void SetTextureFilter();//テクスチャフィルタの設定
		
		virtual void AddRef();
		
	/*Get系*/
	public:
	
		/*コアデバイスの取得*/
		ICore	*GetCore() const
		{
			return m_pCore;
		}
		
		/*グラフィックカードデバイスの取得*/
		IGraphicCard	*GetGraphicCard() const
		{
			return m_pGraphicCard;
		}
		
		/*ファイル管理デバイスの取得*/
		File::IFileManager	*GetFileMgr() const
		{
			return m_pFileMgr;
		}
		
		/*レンダラー用デバイスの取得*/
		Renderer::IRender	*GetRenderer() const
		{
			return m_pRender;
		}
		
		//画面幅の取得		
		Sint32 GetScreenWidth()
		{
			return m_ScreenWidth;
		}
		
		//画面高さの取得
		Sint32 GetScreenHeight()
		{
			return m_ScreenHeight;
		}
		
};
