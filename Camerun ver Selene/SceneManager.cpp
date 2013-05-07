//*============================================================================
//SceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneManager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneManager::CSceneManager(void) :m_pSceneMgr(NULL), m_pRenderTex(NULL)
{
	m_vPos.Set(0, 0);
	
	m_RenderTargetWidth = 800;
	m_RenderTargetHeight = 600;
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	SAFE_RELEASE( m_pSceneMgr );
}

//=============================================================================
//デバイスの設定
//=============================================================================
//[input]
//	pRender:レンダラー用デバイス
//=============================================================================
void CSceneManager::CreateDevice( Renderer::IRender *pRender )
{
	m_pSceneMgr = pRender->CreateSceneManager( 512, false );
	
	m_pRenderTex = pRender->CreateTextureRenderTarget( m_RenderTargetWidth, m_RenderTargetHeight, FORMAT_TARGET_32BIT );
	
}

//=============================================================================
//初期パラメーターの設定
//=============================================================================
//[input]
//	IsUseTex:レンダリングターゲット用テクスチャを使うか
//=============================================================================
void CSceneManager::SetInitParameter( bool IsUseTex )
{
	if( m_pSceneMgr != NULL )
	{
		if( IsUseTex )
		{

			m_pSceneMgr->InitParameter_RenderTargetData(
				m_pRenderTex,												// レンダリングターゲットのテクスチャ（NULLでバックバッファへ直接）
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// 描画先のレンダリングターゲットサイズ（↑が指定されている時は↑のテクスチャサイズに自動変換）
				false );											// 描画先のテクスチャサイズを２の累乗にするかどうか
		}
		
		else
		{
			m_pSceneMgr->InitParameter_RenderTargetData(
				NULL,												// レンダリングターゲットのテクスチャ（NULLでバックバッファへ直接）
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// 描画先のレンダリングターゲットサイズ（↑が指定されている時は↑のテクスチャサイズに自動変換）
				false );											// 描画先のテクスチャサイズを２の累乗にするかどうか
		
		}

		// シーンに対するエフェクトの初期化
		//   シーンに対して行う各種レンダリングエフェクトはここで行います。
		m_pSceneMgr->InitParameter_Shading( SHADING_TYPE_NORMAL );							// シェーディング
		//m_pSceneMgr->InitParameter_Fog( FOG_TYPE_DISABLE, FOG_EFFECT_LINEAR );				// フォグ
		//m_pSceneMgr->InitParameter_HighDynamicRange( HDR_TYPE_ENABLE, HDR_EFFECT_CROSS );		// HDRレンダリング
	//		m_pSceneMgr->InitParameter_MotionBlur( MOTION_BLUR_TYPE_DISABLE );					// モーションブラー
	//		m_pSceneMgr->InitParameter_DepthOfField( DOF_TYPE_DISABLE );							// 被写界深度
		m_pSceneMgr->InitParameter_Shadow( SHADOW_TYPE_SHADOWMAP, SHADOW_QUARITY_MIDDLE );	// 影生成
	//		m_pSceneMgr->InitParameter_AntiAliasType( AA_TYPE_DISABLE, 0.0f );					// アンチエイリアス

		// シーンの初期化系パラメーターの更新
		m_pSceneMgr->InitParameter_Update();
		
		
	}
}

//=============================================================================
//スカイドームの生成
//=============================================================================
//[input]
//	pTex:テクスチャハンドル
//	pRender:レンダラー用デバイス
//=============================================================================
void CSceneManager::CreateSkyDoom( Renderer::ITexture *pTex, Renderer::IRender *pRender )
{

	// スカイドーム生成
	//  空を表現するためのスカイドームを生成します。
	m_pSceneMgr->SceneSkydoom_Create(
		100.0f,						// 半径
		CColor(121,154,255),		// 地表色
		CColor(121,154,255),		// 天頂色
		pTex );					// 空テクスチャ
		
}

//=============================================================================
//パラメーターの設定
//=============================================================================
void CSceneManager::SetParameter()
{
	if( m_pSceneMgr != NULL )
	{
		m_pSceneMgr->Reset();

		// シーンの背景の色
		//m_pSceneMgr->SetParameter_BGColor( Math::Vector4D(0.0f,0.0f,0.0f,1.0f) );
		
		/*描画先領域*/
		m_pSceneMgr->SetParameter_RenderRect( Math::Rect2DF( m_vPos.x, m_vPos.y, toF(m_vPos.x + m_RenderTargetWidth), toF(m_vPos.y + m_RenderTargetHeight) ) );
		
		//m_pSceneMgr->SetParameter_Fog(
		//	Math::Vector3D( 0.8f, 0.8f, 0.8f ),		// フォグ色
		//	50.0f,									// フォグ開始位置
		//	300.0f );								// フォグ終了位置
		//	
		
	}
}



//=============================================================================
//描画領域サイズの設定
//=============================================================================
//[input]
//	width:設定する幅
//	height:設定する高さ
//=============================================================================
void CSceneManager::SetRenderSize( Sint32 width, Sint32 height )
{
	m_RenderTargetWidth = width;
	m_RenderTargetHeight = height;
}

//=============================================================================
//描画位置の設定
//=============================================================================
//[input]
//	vPos:設定する位置
//=============================================================================
void CSceneManager::SetRenderPos( Selene::Math::Vector2D vPos )
{
	m_vPos = vPos;
}

