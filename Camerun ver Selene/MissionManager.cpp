//*============================================================================
//MissionManager.cpp
//*============================================================================
#include "MissionManager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
MissionManager::MissionManager(void)
{
	m_MissionNo = 1;
}

//=============================================================================
//デストラクタ
//=============================================================================
MissionManager::~MissionManager(void)
{
	list<MissionList>::iterator it;
	
	for( it = m_MissionList.begin();it != m_MissionList.end();it++ )
	{
		SAFE_DELETE( it->m_pMission );
	}
}

//=============================================================================
//ミッションの追加
//=============================================================================
//[input]
//	no:ミッション番号
//	pMission:追加するミッション
//=============================================================================
void MissionManager::AppendMission( int no, CMission *pMission )
{
	if( pMission == NULL )
	{
		return;
	}	
	
	MissionList liMission;//ミッションリスト
	
	liMission.m_MissionNo = no;
	liMission.m_pMission = pMission;
	
	m_MissionList.push_back(liMission);
}

//=============================================================================
//ミッションの取得
//=============================================================================
//[input]
//	no:ミッション番号
//=============================================================================
CMission *MissionManager::GetMission( int no )
{
	list<MissionList>::iterator it;
	
	for( it = m_MissionList.begin();it != m_MissionList.end();it++ )
	{
		if( it->m_MissionNo == no )
		{
			return it->m_pMission;
		}
	}
	
	return NULL;
}



