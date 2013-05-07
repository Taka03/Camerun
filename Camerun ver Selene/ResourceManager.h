//*============================================================================
//ResourceManager.h
//*============================================================================
//[history]
//	08/07/04　作成
//[author]
//	Taka
//=============================================================================

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//enum
//=============================================================================
//リソースタイプ
enum eResourceType
{
	TEXTURE,
	MODEL,
	MAP,
	SOUND,
	BGM,
	OTHER,
};


//=============================================================================
//class
//=============================================================================
//[desc]
//	リソース管理用クラス
//=============================================================================
class CResourceManager
{
	private:
	
		ICore *m_pCore;//コアデバイス
		Selene::File::IFileManager *m_pFileMgr;//ファイル管理デバイス
		Renderer::IRender *m_pRender;//レンダラー用デバイス
		
	private:
	
		CGameObject *m_pGameObj;//ゲームオブジェクト
		
	private:
	
		Thread::CThread	m_Thread;//スレッド用ハンドル
		Thread::CCriticalSection m_CS;//クリティカルセクション
		Thread::CEvent m_Event;//イベント
	
		
	protected:
	
	private:
	
		static void LoadedProc( void *pData ) ;//ロード用スレッド
		virtual void Run();//読み込み
		
	public:
	
		CResourceManager( ICore *pCore, File::IFileManager *pFileMgr, Renderer::IRender *pRender );//コンストラクタ
		~CResourceManager();//デストラクタ
		
		void AppendObject( eResourceType type );//オブジェクトの追加
		
		//virtual Bool IsLoading(){};//ロード中かどうか
		
	/*Set系*/
	public:
	
	/*Get系*/
	public:
	
		/*ゲーム用オブジェクトの取得*/
		CGameObject *GetGameObject()
		{
			return m_pGameObj;
		}
};


