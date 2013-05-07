//*============================================================================
//SceneGameMain.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ScenePhoto.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScenePhoto::CScenePhoto( )
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScenePhoto::~CScenePhoto(void)
{
	//SAFE_DELETE( pScene );
}

//=============================================================================
//������
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
bool CScenePhoto::Init( CScene *pScene )
{
	return true;
}


//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
void CScenePhoto::Exec( CScene *pScene )
{
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );//CMissionTutorial( dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ) );
	
	Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CSprite3D *objEmotion = dynamic_cast<CSprite3D *>( pScene->Get3DObject()->FindObjectFromName("Emotion") );
	
	//CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ExplainFont") );
	//
	//pExpFont->SetDrawString("R1�Ō��̉�ʂɖ߂�");
	
	
	/*��ʃN���A*/
	pRender->Clear();
	
	/*��ʕ`��J�n*/
	pRender->Begin();
	
	static int count = 0;
	
	count += 90;
	
	pScene->GetAppDevice()->GetRenderer()->SetScissorRect( &Math::Rect2DI( 0, 0, 800, count ) );
	
	if( count >= 600 )
	{
		count = 600;
	}
	
	char Temp[10];
	
	sprintf( Temp, "Photo%d", pScene->GetPhotoIndex() );
	
	CPhoto *pPhoto = dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName( Temp ) );
	
	pPhoto->SetVisibleFlag( true );
	
	pPhoto->Rendering();
	
	/*��ʕ`��I��*/
	pRender->End();
	
	//if( m_pPhoto->GetTargetDistance() > 0.0f && m_pPhoto->GetTargetDistance() < 1.0f )
	//{
	//	pRender->DebugPrint( Math::Point2DI( 100, 200 ), CColor( 255, 255, 255 ), "�߂�����?");
	//}
	//
	//else
	//{
	//	
		//#if defined(DEBUG) | (_DEBUG )
		
		
		#if defined(TEST_RELEASE)
				if( pPhoto->GetExistFlag() )
				{	
					pRender->DebugPrint( Math::Point2DI( 400, 300 ), CColor( 0, 200, 0 ), 
									"����");
				}
				
				pRender->DebugPrint( Math::Point2DI( 100, 200 ), CColor( 255, 255, 255 ), 
									"fDistance:%f", pPhoto->GetTargetDistance());
				pRender->DebugPrint( Math::Point2DI( 100, 300 ), CColor( 255, 255, 255 ),
									 "Pos:%f:%f:%f", pPhoto->GetTargetPosition().x, 
													 pPhoto->GetTargetPosition().y, 
													 pPhoto->GetTargetPosition().z );
		
		#endif
												 
		if( pPhoto->GetExistFlag() )
		{
			float fDistance = pPhoto->GetTargetDistance();
			
			float fDistanceMin = pMission->GetMissionData().m_DistanceMin;
			float fDistanceMax = pMission->GetMissionData().m_DistanceMax;
			
			
			if( fDistance >= fDistanceMin && 
				fDistance <= fDistanceMax  )
			{
				float fDelta = fDistanceMax - fDistanceMin;
				
				
				if( fDistance >= fDistanceMin && fDistance <= fDistanceMin + fDelta / 3 )	
				{
					objEmotion->SetAnimID( Math::Point2DI( 0, 0 ) );
				}
				
				else if( fDistance > fDistanceMin + fDelta / 3 && fDistance <= fDistanceMin + (2 * fDelta) / 3)
				{
					objEmotion->SetAnimID( Math::Point2DI( 1, 0 ) );
				}
				
				else if( fDistance > fDistanceMin + (2 * fDelta) / 3 && fDistance <= fDistanceMax )
				{
					objEmotion->SetAnimID( Math::Point2DI( 2, 0 ) );
				}
				
			}
		}
			
		else
		{
			objEmotion->SetAnimID( Math::Point2DI( 3, 0 ) );
		}

	pPhoto->Exec();
	
	static int PhotoVisibleCount = 0;
	
	#if defined( TEST_RELEASE )	
		
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R1 ) )
		
	#else
	
		if( ++PhotoVisibleCount > 60 )
	
	
	#endif
	{
	
	//if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R1) ) 
	//{
		pScene->SetSceneState( STATE_STANDBY );
		
		pScene->ChangeScene( SCENE_GAMEMAIN );
		
		count = 0;
		
		PhotoVisibleCount = 0;
		
		pScene->SetVisibleCount( 0 );
		
		pPhoto->SetVisibleFlag( false );
		
		objEmotion->SetVisibleFlag( true );
	}
		
		
	//}
	
}

