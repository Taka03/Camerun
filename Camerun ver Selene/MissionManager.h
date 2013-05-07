//*============================================================================
//MissionManager.h
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
#include "Mission.h"
#include <iostream>

using namespace std;

//=============================================================================
//struct
//=============================================================================
//ミッションリスト
struct MissionList
{
	int m_MissionNo;//ミッションNo
	CMission *m_pMission;//ミッション
};

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ミッション管理用クラス
//=============================================================================
class MissionManager
{
	private:
		
		list<MissionList> m_MissionList;//ミッションリスト
		
		Sint32 m_MissionNo;//選択されているミッション番号
	
	public:
	
		MissionManager(void);//コンストラクタ
		~MissionManager(void);//デストラクタ
		
		void AppendMission( int no, CMission *pMission );//ミッションの追加
		
	/*Set系*/
	public:
	
		//ミッション番号のセット	
		void SetMissionNo( int no )
		{
			m_MissionNo = no;
		}
		
	/*Get系*/
	public:
	
		CMission *GetMission( int no );//ミッションの取得
		
		/*選択中のミッション番号の取得*/
		Sint32 GetMissionNo()
		{
			return m_MissionNo;
		}
		
		/*ミッション数の取得*/
		Sint32 GetMissionNum()
		{
			return m_MissionList.size();
		}
};
