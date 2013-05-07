//*============================================================================
//SceneDrawMission.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneDrawMission.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneDrawMission::CSceneDrawMission( )
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneDrawMission::~CSceneDrawMission(void)
{
	//SAFE_DELETE( pScene );
}

////=============================================================================
////�����X�R�A�̌v�Z
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
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
void CSceneDrawMission::Exec( CScene *pScene )
{
	
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );
	
	static int count = 0;
	
	int PhotoIndex = pMission->GetPhotoIndex();
	
	char Temp[20] = "";
	
	pRender->Begin();
	
	pRender->SetDrawTextFont("MS �S�V�b�N", 48 );	
	
	const Sint32 PosX = 10;
	
	
	pRender->DrawTextA( Math::Point2DI( PosX, 120 ), CColor( 255, 255, 255 ), "Mission%d", pScene->GetMissionMgr()->GetMissionNo() + 1 );
	
	pRender->SetDrawTextFont("MS �S�V�b�N", 48 );
	
	
	pRender->DrawTextA( Math::Point2DI( PosX, 250 ), CColor( 255, 255, 255 ), pMission->GetMissionName().c_str() );
	
	pRender->SetDrawTextFont("MS �S�V�b�N", 30 );
	
	for( Uint32 i = 0;i < pMission->GetMissionData().m_vecMissionContent.size();++i )
	{
		pRender->DrawTextA( Math::Point2DI( PosX, 350 + i * 30 ), CColor( 255, 255, 255 ), pMission->GetMissionData().m_vecMissionContent.at( i ).c_str() );
	}
	
	pRender->SetDrawTextFont("MS �S�V�b�N", 30 );
	
	pRender->DrawTextA( Math::Point2DI( PosX, 490 ), CColor( 225, 0, 0 ), "�J�����������ăX�^�[�g�n�_�ɖ߂�!!");
	
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

