//*============================================================================
//SceneStartMenu.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneStartMenu.h"
#include "player.h"
#include "FontSprite.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneStartMenu::CSceneStartMenu(void)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneStartMenu::~CSceneStartMenu(void)
{

}

//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
void CSceneStartMenu::Exec( CScene *pScene )
{
	const int ITEM_MAX = 3;//�ő區�ڐ�
	
	static Sint32 Cursor = 0;
	
	Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
	
	CSprite *objBack	= dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Pause") );
	CSprite *objHighScore = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("HighScore") );
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );
	
	CSoundEffect *sndTrain	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("STrain") );
	CSoundEffect *sndMouse = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Mouse") );
	CSoundEffect *sndBird = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Bird") );

	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("GameBGM") );
	
	CMenu *objPopMenu = dynamic_cast<CMenu *>( pScene->GetGameObject()->FindObjectFromName("PopMenu") );
	
	CFontSprite *pMiContFont2 = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ContentFont2") );
	
	pMiContFont2->SetVecTextChat( pMission->GetMissionData().m_vecMissionContent );
	
	pMiContFont2->SetPosition( Math::Vector3D( 370, 360, 0 ) );
	
	CFontSprite *pExpFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ExplainFont") );
	
	vector< string > vecText;
	
	vecText.push_back( "R2 ����" );
	
	//pExpFont->SetVecTextChat( vecText );
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{
		objBack->SetVisibleFlag( true );
		
		if( pMission->GetHiScore() == 0  )
		{	
			objHighScore->SetVisibleFlag( false );
		}
		
		else
		{
			objHighScore->SetVisibleFlag( true );
		}
	}
	
	/*��ʂ̃N���A*/
	pRender->Clear();
	
	/*�`��J�n*/
	pRender->Begin();
	
	objBack->Rendering();
	
	//pExpFont->Rendering();
	
	/*�Q�[������*/
	//pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 600, 10 ), CColor( 255, 255, 255 ), 
	//													"R2 ����" );
	//													
	//pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 600, 30 ), CColor( 255, 255, 255 ), 
	//													"�X�^�[�g�{�^���@�Q�[���ɖ߂�" );
	
	
	if( objHighScore->GetVisibleFlag() )
	{	
		objHighScore->Rendering();
	}
	
	Math::Vector2D vPos[] =
	{
		Math::Vector2D(30,60),
		Math::Vector2D(30,160),
		Math::Vector2D(30,260),
		Math::Vector2D(30,360),
		Math::Vector2D(15,481),
		Math::Vector2D(145,481),
		Math::Vector2D(275,481),
		Math::Vector2D(405,481),
		Math::Vector2D(535,481),
		Math::Vector2D(665,481),
		
	};
	
	for( int i = 0;i < pScene->GetFilmCount(); ++i )
	{
		char Temp[10] = "";
		
		sprintf( Temp, "Photo%d", i+1 );
		
		string strTemp;
		
		strTemp += Temp;
		
		CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
		
		pRender->DrawTexture( Math::Rect2DF( vPos[i].x, vPos[i].y, toF( 120 ), toF( 90 ) ), CColor( 255, 255, 255 ), Math::Rect2DF( 0, 0, toF( pPhoto->GetTexture()->GetOriginalSize().x ), toF( pPhoto->GetTexture()->GetOriginalSize().y ) ), pPhoto->GetTexture() );
		
		//pPhoto->SetPosition( Math::Vector3D( vPos[i].x, vPos[i].y, 0 ) );
		
		//pPhoto->Rendering();
		
	}
	
	CSprite *objReady = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Ready") );
	
	objPopMenu->Rendering();
	
	const char *pItemName[] =
	{
		"���g���C",
		"�Q�[���ɖ߂�",
		"�Q�[�����I���",
	};
	
	
	for( int i = 0;i < ITEM_MAX;++i )
	{
		if( Cursor == i )
		{	
			pRender->DrawTextA( Math::Point2DI( 230, 155+i*30 ), CColor( 0, 0, 0 ), pItemName[i] );
		}
		
		else
		{
			pRender->DrawTextA( Math::Point2DI( 230, 155+i*30 ), CColor( 245, 152, 157 ), pItemName[i] );
		}
	}
	
	
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2) )
	{
		/*���g���C*/
		if( Cursor == 0 )
		{
			vecText.clear();
			
			pExpFont->SetVecTextChat( vecText );
			
			
			pScene->Get3DObject()->Init();
			
			CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
			
			CCharacter *objFlag = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
			
			objFlag->SetVisibleFlag( false );
			
			objCamMain->Init();
			
			tagTime Time;
			
			pScene->SetCurrentTime( Time );
			
			pGameMusic->GetBGMDevice()->Stop();
			
			sndTrain->GetSEDevice()->Stop( 0 );
			sndBird->GetSEDevice()->Stop( 0 );
			sndMouse->GetSEDevice()->Stop( 0 );
			
			for( int i = 0;i < pScene->GetFilmCount(); ++i )
			{
				char Temp[10] = "";
				
				sprintf( Temp, "Photo%d", i+1 );
				
				string strTemp;
				
				strTemp += Temp;
				
				CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
				
				pPhoto->SetVisibleFlag( false );
				
				pScene->Get2DObject()->RemoveObject( pPhoto );
			}
			
			pScene->SetFilmCount( 0 );
			
			objBack->SetVisibleFlag( false );
			objHighScore->SetVisibleFlag( false );
			
			pScene->SetFontSize( 15 );			
			
			pScene->SetNextScene( SCENE_DEMO );
			
			objReady->SetVisibleFlag( true );
			
			Cursor = 0;
			
			
			
			
			pScene->SetSceneState( STATE_FADEOUT );
	
				
		}
		
		/*�Q�[���ɖ߂�*/
		else if( Cursor == 1 )
		{
			vecText.clear();
			
			pExpFont->SetVecTextChat( vecText );
			
			
			
			pScene->SetNextScene( SCENE_GAMEMAIN );

			pScene->SetFadeTime( 30.0f );
			
			objBack->SetVisibleFlag( false );
			objHighScore->SetVisibleFlag( false );
			
			pScene->SetFontSize( 15 );
			
			Cursor = 0;
			
			
			pScene->SetSceneState( STATE_FADEOUT );
		
		}
		
		/*�Q�[�����I���*/
		else if( Cursor == 2 )
		{
			vecText.clear();
			
			pExpFont->SetVecTextChat( vecText );
			
		
			pScene->SetNextScene( SCENE_MISSIONSELECT );
			
			pScene->Get3DObject()->Init();
			
			CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
			
			
			objCamMain->Init();
			
			CCharacter *objFlag = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
			
			objFlag->SetVisibleFlag( false );
			
			
			tagTime Time;
			
			pScene->SetCurrentTime( Time );
			
			pGameMusic->GetBGMDevice()->Stop();
			
			sndTrain->GetSEDevice()->Stop( 0 );
			sndBird->GetSEDevice()->Stop( 0 );
			sndMouse->GetSEDevice()->Stop( 0 );
			
			for( int i = 0;i < pScene->GetFilmCount(); ++i )
			{
				char Temp[10] = "";
				
				sprintf( Temp, "Photo%d", i+1 );
				
				string strTemp;
				
				strTemp += Temp;
				
				CPhoto *pPhoto	= dynamic_cast<CPhoto *>( pScene->Get2DObject()->FindObjectFromName(strTemp) );
				
				pPhoto->SetVisibleFlag( false );
				
				pScene->Get2DObject()->RemoveObject( pPhoto );
			}
			
			pScene->SetFilmCount( 0 );
			
			objBack->SetVisibleFlag( false );
			objHighScore->SetVisibleFlag( false );
			
			pScene->SetFontSize( 15 );
			
			objReady->SetVisibleFlag( true );
			
			pScene->SetFadeTime( 30.0f );
			
			Cursor = 0;
			
			
			pScene->SetSceneState( STATE_FADEOUT );
		
		}
	}
	
	/*�X�^�[�g�ł��Q�[���ɖ߂��悤�ɂ���*/
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_START ) )
	{
		pScene->SetNextScene( SCENE_GAMEMAIN );

		pScene->SetFadeTime( 30.0f );
		
		objBack->SetVisibleFlag( false );
		objHighScore->SetVisibleFlag( false );
		
		pScene->SetFontSize( 15 );
		
		Cursor = 0;
		
		
		pScene->SetSceneState( STATE_FADEOUT );
		
	}
		
		
	
	/*�n�C�X�R�A����������A�n�C�X�R�A�\��*/
	if( objHighScore->GetVisibleFlag() )
	{
		pRender->DrawText( Math::Point2DI( 670, 160 ), CColor( 245, 152, 157 ), "%d", pMission->GetHiScore() );
	}
	
	Math::Point2DF vExpPos[] =
	{
		Math::Point2DF( 550, 0 ),
	};
	
	//pExpFont->DrawMultiLine( vExpPos );
	
	/*�~�b�V�������̕\��*/
	pRender->DrawText( Math::Point2DI( 215, 95 ), CColor( 13, 167, 217 ) , pMission->GetMissionName().c_str() );
	
	
	//if( objPopMenu->GetPopUpFlag() )
	//{
	//			eSelectType Select = objPopMenu->SelectYesNo( pScene->GetJoyPad()->GetController() );
	//			
	//			if( Select == SELECT_YES )
	//			{
	//			}
	//			
	//			
	//			
	//			
	//		
	//			eSelectType Select = objPopMenu->SelectYesNo( pScene->GetJoyPad()->GetController() );
	//			
	//			if( Select == SELECT_YES )
	//			{
	//			
	//			}
	//		}
	//}
	//
	pMiContFont2->Rendering();
	
	
	/*�`��I��*/
	pRender->End();
	
	objBack->Exec();
	
	objHighScore->Exec();
	
	objPopMenu->Exec();
	
	pMiContFont2->DrawMultiLine();
	
	eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorClampUpDown
									 ( 0, Cursor, ITEM_MAX );
}
