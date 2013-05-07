//*============================================================================
//Game.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Game.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CGame::CGame(void) :m_pCore(NULL), m_pGraphicCard(NULL), m_pFileMgr(NULL), 
					m_ScreenWidth(800), m_ScreenHeight(600)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame(void)
{
	SAFE_RELEASE( m_pRender );
	SAFE_RELEASE( m_pFileMgr );
	SAFE_RELEASE( m_pGraphicCard );
	SAFE_RELEASE( m_pCore );
	
}

//=============================================================================
//コアの生成
//=============================================================================
void CGame::CreateCore()
{
	
	#if defined(DEBUG) | defined(_DEBUG)
		/*システムの初期化*/
		System::Initialize();
		
	#else
	
		//System::Initialize( true, false );
		System::Initialize();
		
	#endif
	
	/*コアの生成*/
	m_pCore = System::CreateCore();
	
}

//=============================================================================
//初期化
//=============================================================================
bool CGame::Initialize()
{
	/*初期化*/
	m_pCore->Initialize( "キャメRUN", FRAME_RATE_60 );
	
	//-----------------------------------------------------------------
	// タイトルバーに情報を表示
	//-----------------------------------------------------------------
	#if defined(DEBUG) | (_DEBUG)	
		m_pCore->EnableDrawTitleInformation( true );
	#endif

	//-----------------------------------------------------------------
	// ファイル登録
	//-----------------------------------------------------------------
	// ファイルマネージャーを生成
	m_pFileMgr = m_pCore->CreateFileManager();
	// コアに設定
	m_pCore->SetFileManager( m_pFileMgr );
	// ルートディレクトリを設定
	#if defined(DEBUG) | (_DEBUG)
		
		m_pFileMgr->SetRootPath( 0, "../data" );
		
	#else
	
		m_pFileMgr->SetRootPath( 0, "./data", "LXfj6MhP" );
	
	#endif

	//-----------------------------------------------------------------
	// グラフィックカードを取得
	//-----------------------------------------------------------------
	// グラフィックカードに関しての初期化を行います。
	// IGraphicCardインターフェイスからは接続された
	// グラフィックカードの能力を取得する事が可能です。
	// IGraphicCardインターフェイスは1つのICoreインターフェイスに対して1つしか存在しません。
	m_pGraphicCard = m_pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
	
	if( m_pGraphicCard == NULL )
	{
		return false;
	}

	//-----------------------------------------------------------------
	// ウィンドウ作成
	//-----------------------------------------------------------------
	// ICoreインターフェイス内の情報に従ってアプリケーション
	// ウィンドウを生成します。
	// IGraphicCardからの情報を元に画面解像度などを変更する場合は、
	// ICore::Start()を呼び出す前に行ってください。
	m_pCore->Start( m_ScreenWidth, m_ScreenHeight, true );

	//-----------------------------------------------------------------
	// レンダラーを取得
	//-----------------------------------------------------------------
	// 作成したグラフィックカードから画面描画用のレンダラーを取得します。
	// Renderer::IRenderインターフェイスは1つのIGraphicCardインターフェイスに対して1つしか存在しません。
	m_pRender = m_pGraphicCard->CreateRender();
	
	if ( m_pRender == NULL ) 
	{
		return false;
	}
	
	Renderer::CTextureConfig Config;
	
	// テクスチャフォーマット
	Config.SetColorKey( CColor(0,0,0,0) );
	Config.SetFormat( FORMAT_TEXTURE_32BIT );
	Config.SetMipmapEnable( true );
	m_pRender->SetTextureConfig( Config );
	
	return true;
}

//=============================================================================
//テクスチャフィルタの設定
//=============================================================================
void CGame::SetTextureFilter()
{
	// フィルタリング   
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_LIGHT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_ENVIRONMENT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_SPECULAR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_NORMAL, TEXTURE_FILTER_3D_LOW );
}

//=============================================================================
//参照カウンタ増加
//=============================================================================
void CGame::AddRef()
{
	m_pRender->AddRef();
	m_pGraphicCard->AddRef();
	m_pFileMgr->AddRef();
	m_pCore->AddRef();
}
	



