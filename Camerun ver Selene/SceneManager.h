//*============================================================================
//SceneManager.h
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
//[Desc]
//	シーン管理用クラス
//=============================================================================
class CSceneManager
{
	private:
	
		Scene::ISceneManager *m_pSceneMgr;//シーン管理用デバイス
		//Scene::ICustomizedSceneManager *m_pSceneMgr;//シーン管理用デバイス
		
	private:
	
		Math::Vector2D m_vPos;//表示位置
		Sint32 m_RenderTargetWidth;//描画領域幅
		Sint32 m_RenderTargetHeight;//描画領域高さ
	
		Renderer::ITexture *m_pRenderTex;//レンダリングターゲット用テクスチャ
	
	public:
	
		CSceneManager(void);//コンストラクタ
		~CSceneManager(void);//デストラクタ
		
	public:
	
		void CreateDevice( Renderer::IRender *pRender );//デバイスの生成
		void SetParameter( );//パラメーターの設定
		void SetInitParameter( bool IsUseTex );//初期パラメータの設定
		void CreateSkyDoom( Renderer::ITexture *pTex, Renderer::IRender *pRender );//スカイドームの生成
	
	/*Set系*/
	public:
	
		void SetRenderSize( Sint32 width, Sint32 height );//描画領域サイズの設定
		void SetRenderPos( Math::Vector2D vPos );//描画位置の設定
		
		
	/*Get系*/
	public:
		
		/*シーン管理用デバイスの取得*/
		Scene::ISceneManager *GetSceneMgr() const
		{
			return m_pSceneMgr;
		}
		
		/*シーン管理用デバイスの取得*/
		//Scene::ICustomizedSceneManager *GetSceneMgr() const
		//{
		//	return m_pSceneMgr;
		//}
		
		
		//描画領域幅の取得	
		Sint32 GetRenderWidth() const
		{
			return m_RenderTargetWidth;
		}
		
		//描画領域幅の取得		
		Sint32 GetRenderHeight() const
		{
			return m_RenderTargetHeight;
		}
		
		//レンダリングターゲット用テクスチャの取得
		Renderer::ITexture *GetRenderTex() const
		{
			return m_pRenderTex;
		}
		
		
};
