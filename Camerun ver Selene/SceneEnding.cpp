//*============================================================================
//SceneEnding.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneEnding.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneEnding::CSceneEnding( )
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneEnding::~CSceneEnding(void)
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
void CSceneEnding::Exec( CScene *pScene )
{
	
	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );
	
	static int count = 0;
	
	int PhotoIndex = pMission->GetPhotoIndex();
	
	char Temp[20] = "";
	
	pRender->Begin();
	
	pRender->SetDrawTextFont("MS �S�V�b�N", 50 );	
	
	pRender->DrawTextA( Math::Point2DI( 300, 300 ), CColor( 255, 255, 255 ), "Thank you for Playing" );
	
	pRender->End();
	
	if( ++count > 60 * 2 )
	{
		count = 0;
		
		pScene->SetFontSize( 15 );
		
		pScene->SetNextScene( SCENE_TITLE );
		
		pScene->SetSceneState( STATE_FADEOUT );
		
	}
	
}

