//*============================================================================
//Mission.h
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
#include "Selene.h"
#include "enemy.h"
#include "Sprite.h"

//=============================================================================
//struct
//=============================================================================
struct tagTime
{
	Sint32 MinSec;//ミリ秒
	Sint32 Sec;//秒
	Sint32 Min; //分
	Sint32 Hour;//時間
	
	tagTime()
	{
		MinSec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
	}
	
	void Initialize()
	{
		MinSec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
	}
};

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//struct
//=============================================================================
struct MissionData
{
	string m_MissionName;//ミッション名
	string m_MissionChat;//ミッション会話
	vector< string > m_vecChat;//会話内容
	vector< string > m_vecMissionContent;//ミッション内容
	string m_TargetName;//ターゲット名
	CSprite *m_pFontSpr;//ミッションフォントスプライト
	CSprite *m_pPhotoSpr;//ミッションの写真スプライト
	Sint32 m_ClearPoint;//クリア可能となるポイント
	Sint32 m_FilmNum;//ミッションのフィルム枚数
	tagTime m_LimitTime;//制限時間
	tagTime m_TimeBorder;//タイムボーダー
	float m_DistanceMax;//ターゲット距離のMax
	float m_DistanceMin;//ターゲット距離のMin
	float m_TargetPosMax;//ターゲット位置のMin
	float m_TargetPosMin;//ターゲット位置のMin
	
};


//=============================================================================
//class
//=============================================================================
//[Desc]
//	ミッション用クラス
//=============================================================================
class CMission 
{
	protected:
	
		MissionData m_datMission;//ミッションデータ
		CDraw3DObject *m_pTarget;//ターゲットとなるオブジェクト
		bool m_IsGameClear;//ミッションクリアしたかどうか
		bool m_IsFirstPlay;//初期プレイ時
		Sint32 m_HiScore;//ミッションのハイスコア
		//Sint32 m_ExistScore;//存在スコア
		//Sint32 m_PosScore;//位置スコア
		//Sint32 m_DistScore;//距離スコア
		Sint32 m_ClearTime;//クリア時間
		Sint32 m_PhotoIndex;//選択された写真のインデックス
		
	public:
		
		CMission(void);//コンストラクタ
		CMission( CDraw3DObject *pTarget, MissionData datMission );//コンストラクタ
		~CMission(void);//デストラクタ
		
		void Exec();//処理
		void Rendering();//レンダリング
		
	/*Set系*/
	public:
	
		/*ターゲットの設定*/
		void SetTarget( CDraw3DObject *pTarget )
		{
			m_pTarget = pTarget;
		}
		
		/*ミッションクリアフラグの設定*/
		void SetGameClearFlag( bool flag )
		{
			m_IsGameClear = flag;
		}
		
		/*ハイスコアの設定*/
		void SetHiScore( Sint32 HiScore )
		{
			m_HiScore = HiScore;
		}
		
		/*初期プレイフラグの設定*/
		void SetFirstPlayFlag( bool flag )
		{
			m_IsFirstPlay = flag;
		}
		
		///*存在スコアの設定*/
		//void SetExistScore( Sint32 Score )
		//{
		//	m_ExistScore = Score;
		//}
		//
		///*位置スコアの設定*/
		//void SetPosScore( Sint32 Score )
		//{
		//	m_PosScore = Score;
		//}

		///*大きさスコアの設定*/
		//void SetDistScore( Sint32 Score )
		//{
		//	m_DistScore = Score;
		//}
		
		
		/*写真用スプライトの設定*/
		void SetPhotoSprite( CSprite *pSpr )
		{
			m_datMission.m_pPhotoSpr = pSpr;
		}
		
		/*選択写真のインデックスのセット*/
		void SetPhotoIndex( Sint32 index )
		{
			m_PhotoIndex = index;
		}
		
		
	/*Get系*/
	public:

		/*ミッションデータの取得*/
		MissionData GetMissionData() const
		{
			return m_datMission;
		}
		
		/*ミッション名の取得*/
		string GetMissionName() const
		{
			return m_datMission.m_MissionName;
		}

		//ターゲットとなるオブジェクトの取得
		CDraw3DObject *GetTarget() const
		{
			return m_pTarget;
		}
		
		//クリア可能となるポイントの取得		
		Sint32 GetClearPoint() const
		{
			return m_datMission.m_ClearPoint;
		}
		
		/*フィルム枚数の取得*/
		Sint32 GetFilmNum() const
		{
			return m_datMission.m_FilmNum;
		}
		
		/*制限時間の取得*/
		tagTime GetLimitTime() const
		{
			return m_datMission.m_LimitTime;
		}
		
		/*ミッションクリア判定フラグの取得*/
		bool GetGameClearFlag()
		{
			return m_IsGameClear;
		}
		
		/*初期プレイフラグの取得*/
		bool GetFirstPlayFlag()
		{
			return m_IsFirstPlay;
		}
		
		/*ハイスコアの取得*/
		Sint32 GetHiScore()
		{
			return m_HiScore;
		}
		//
		///*存在スコアの取得*/
		//Sint32 GetExistScore()
		//{
		//	return m_ExistScore;
		//}

		///*位置スコアの取得*/
		//Sint32 GetPosScore()
		//{
		//	return m_PosScore;
		//}

		///*大きさスコアの取得*/
		//Sint32 GetDistScore()
		//{
		//	return m_DistScore;
		//}
		
		
		/*タイムボーダーの取得*/
		tagTime GetTimeBorder()
		{
			return m_datMission.m_TimeBorder;
		}
		
		/*選択写真のインデックス*/
		Sint32 GetPhotoIndex()
		{
			return m_PhotoIndex;
		}
	
};
