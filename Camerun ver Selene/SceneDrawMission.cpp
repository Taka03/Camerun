//*============================================================================
//SceneDrawMission.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneDrawMission.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneDrawMission::CSceneDrawMission( )
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneDrawMission::~CSceneDrawMission(void)
{
	//SAFE_DELETE( pScene );
}

////=============================================================================
////距離スコアの計算
////=============================================================================
//Sint32 CSceneDrawMission::CalcDistScore()
//{
//	int Score = 0;
//	
//	
//	return Score;
//		
//}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneDrawMission::Exec( CScene *pScene )
{
	
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );
	
	static int count = 0;
	
	int PhotoIndex = pMission->GetPhotoIndex();
	
	char Temp[20] = "";
	
	pRender->Begin();
	
	pRender->SetDrawTextFont("MS ゴシック", 48 );	
	
	const Sint32 PosX = 10;
	
	
	pRender->DrawTextA( Math::Point2DI( PosX, 120 ), CColor( 255, 255, 255 ), "Mission%d", pScene->GetMissionMgr()->GetMissionNo() + 1 );
	
	pRender->SetDrawTextFont("MS ゴシック", 48 );
	
	
	pRender->DrawTextA( Math::Point2DI( PosX, 250 ), CColor( 255, 255, 255 ), pMission->GetMissionName().c_str() );
	
	pRender->SetDrawTextFont("MS ゴシック", 30 );
	
	for( Uint32 i = 0;i < pMission->GetMissionData().m_vecMissionContent.size();++i )
	{
		pRender->DrawTextA( Math::Point2DI( PosX, 350 + i * 30 ), CColor( 255, 255, 255 ), pMission->GetMissionData().m_vecMissionContent.at( i ).c_str() );
	}
	
	pRender->SetDrawTextFont("MS ゴシック", 30 );
	
	pRender->DrawTextA( Math::Point2DI( PosX, 490 ), CColor( 225, 0, 0 ), "カメラを持ってスタート地点に戻れ!!");
	
	pRender->End();
	
	if( ++count > 60 * 3 )
	{
		count = 0;
		
		pScene->SetFontSize( 15 );
		
		pScene->SetNextScene( SCENE_DEMO );
		
		pScene->SetFadeTime( 30.0f );
		
		
		pScene->SetSceneState( STATE_FADEOUT );
		
	}
	
}

