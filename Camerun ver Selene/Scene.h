//*============================================================================
//Scene.h
//*============================================================================
//[history]
//	08/03/11　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"
#include "joypad.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "Train.h"
#include "CamObject.h"
#include "FlagObject.h"
#include "SoundEffect.h"
#include "Field.h"
#include "Sprite.h"
#include "FontSprite.h"
#include "BGM.h"
#include "SceneManager.h"
#include "Game.h"
#include "Application.h"
#include "Photo.h"
#include "DebugLine.h"
#include "MissionManager.h"
#include "Menu.h"
#include "Sprite3D.h"
#include "Particle.h"
#include "Flash.h"
#include "MiniMap.h"

//=============================================================================
//enum
//=============================================================================
//シーンタイプ
enum eSceneType
{
	SCENE_INIT,
	SCENE_TITLE,
	SCENE_MISSIONSELECT,
	SCENE_CHAT,
	SCENE_DRAWMISSION,
	SCENE_DEMO,
	SCENE_GAMEMAIN,
	SCENE_STARTMENU,
	SCENE_PHOTOSCREEN,
	SCENE_RESULT,
	SCENE_CALCSCORE,
	SCENE_ENDING,
};

enum eSceneState
{
	STATE_STANDBY,//遷移中
	STATE_FADEIN,//フェードイン
	STATE_FADEOUT,//フェードアウト
	STATE_FINISH,//遷移終了
};

const int BIRD_MAX = 6;
const int MOUSE_MAX = 3;
const int MINI_CHARA_MAX = BIRD_MAX + MOUSE_MAX;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームシーン用クラス
//=============================================================================
class CScene
{
	private:
	
		CApplication	*m_pApp;//ゲーム用デバイス
		CGameObject *m_pGameObj;//ゲームオブジェクト
		CDraw3DObject *m_p3DObj;//3Dモデルオブジェクト
		Draw2DObject  *m_p2DObj;//2D画像オブジェクト
		CSound		*m_pSoundObj;//サウンドオブジェクト
		CSceneManager *m_pSceneMgr[S_MAX];//シーン管理
		MissionManager *m_pMissionMgr;//ミッション管理
		CJoyPad *m_pJoyPad;//ジョイパッド用デバイス
		Selene::Peripheral::IMouse *m_pMouse;//マウス用デバイス
		eSceneType m_eNowScene;//現在のシーン
		eSceneType m_eNextScene;//次のシーン
		bool m_IsFirstBoot;//初期起動判定フラグ
		bool m_IsLoadEnd;//ロード終了フラグ
		
		Sint32 m_PhotoIndex;//表示する写真用
		Sint32 m_FilmCount;//フィルムカウンタ		
		eSceneState m_eSceneState;//シーン状態
		
		tagTime m_ClearTime;//クリア時間
		tagTime m_CurrentTime;//経過時間
		float m_fFadeTime;//フェード時間
		
		Sint32 m_VisibleCount;//表示カウンタ
		
		Sint32 m_FontSize;//フォントサイズ
		
		//Selene::Thread::CThread CThread;//スレッド
		
	private:
	
		void FadeIn();//フェードイン
		void FadeOut();//フェードアウト
		
	public:
	
		CScene(){};
		CScene( CApplication *pApp, CJoyPad *pJoy );//コンストラクタ
		~CScene(void);//デストラクタ
		
		virtual bool Init( CScene *pScene );//初期化
		virtual void Exec( CScene *pScene );//処理
		
		void SceneStateExec();//シーン状態による変化
		void TimeCount();//時間計測
		
		/*フィルムカウンタの増加*/
		void AddFilmCounter( )
		{
			m_FilmCount ++;
		}
		
		/*表示カウンタの加算*/
		void AddVisibleCounter()
		{
			m_VisibleCount++;
			return;
		}
		
		
	/*Set系*/
	public:
	
		void ChangeScene( eSceneType scene );//シーンの移行
		void SetNextScene( eSceneType scene );//次のシーンの設定
		
		/*写真インデックスの設定*/
		void SetPhotoIndex( Sint32 index )
		{
			m_PhotoIndex = index;
		}
		
		/*クリア時間の設定*/
		void SetClearTime( tagTime Time )
		{
			m_ClearTime = Time;			
		}
		
		/*経過時間の設定*/
		void SetCurrentTime( tagTime Time )
		{
			m_CurrentTime = Time;
		}
		
		/*ロード終了フラグの設定*/
		void SetLoadEndFlag( bool flag )
		{
			m_IsLoadEnd = flag;
		}
		
		/*シーン状態の設定*/
		void SetSceneState( eSceneState state )
		{
			m_eSceneState = state;
		}
		
		/*フェード時間の設定*/
		void SetFadeTime( float fTime )
		{
			m_fFadeTime = fTime;
		}
		
		/*フィルムカウントのセット*/
		void SetFilmCount( Sint32 count )
		{
			m_FilmCount = count;
		}
		
		/*フォントサイズの設定*/
		void SetFontSize( Sint32 Size )
		{
			m_FontSize = Size;
		}
		
		void SetVisibleCount( Sint32 count )
		{
			m_VisibleCount = count;
		}
		
		
	/*Get系*/
	public:
		
		//アプリケーション用デバイスの取得		
		CApplication *GetAppDevice() const
		{
			return m_pApp;
		}

		//ゲームオブジェクトの取得		
		CGameObject *GetGameObject() const
		{
			return m_pGameObj;
		}

		//3Dモデルオブジェクトの取得		
		CDraw3DObject *Get3DObject() const 
		{
			return m_p3DObj;
		}

		//2D画像オブジェクトの取得		
		Draw2DObject  *Get2DObject() const
		{
			return m_p2DObj;
		}
		
		//サウンドオブジェクトの取得
		CSound		*GetSoundObj() const
		{
			return m_pSoundObj;
		}
		
		//シーン管理の取得
		CSceneManager *GetSceneMgr( int index ) const
		{
			return m_pSceneMgr[index];
		}
		
		/*ジョイパッドの取得*/
		CJoyPad *GetJoyPad() const
		{
			return m_pJoyPad;
		}
		
		/*ミッションマネージャの取得*/
		MissionManager *GetMissionMgr()
		{
			return m_pMissionMgr;
		}
		
		//マウス用デバイスの取得
		Selene::Peripheral::IMouse *GetMouse() const
		{
			return m_pMouse;
		}
		
		/*シーン状態の取得*/
		eSceneState GetSceneState() const
		{
			return m_eSceneState;
		}
		
		/*今のシーンの取得*/
		eSceneType GetNowScene() const
		{
			return m_eNowScene;
		}
		
		/*次のシーンの取得*/
		eSceneType GetNextScene() const
		{
			return m_eNextScene;
		}
		
		/*写真表示用のインデックス*/
		Sint32 GetPhotoIndex() const
		{
			return m_PhotoIndex;
		}
		
		/*フィルムカウンタの取得*/
		Sint32 GetFilmCount() const
		{
			return m_FilmCount;
		}
		
		/*経過時間の取得*/
		tagTime GetCountTime() const
		{
			return m_CurrentTime;
		}
		
		/*クリア時間の取得*/
		tagTime GetClearTime() const
		{
			return m_ClearTime;
		}
		
		/*現在の時間の取得*/
		tagTime GetCurrentTime() const
		{
			return m_CurrentTime;
		}
		
		/*初期ブートフラグの取得*/
		bool GetFirstBootFlag() const
		{
			return m_IsFirstBoot;
		}
		
		/*ロード終了フラグの取得*/
		bool GetLoadEndFlag()
		{
			return m_IsLoadEnd;
		}
		
		/*表示カウンタの取得*/
		Sint32 GetVisibleCount()
		{
			return m_VisibleCount;
		}
		
		
		
		
};
