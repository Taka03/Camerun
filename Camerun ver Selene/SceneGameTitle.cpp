//*============================================================================
//SceneGameTitle.h
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameTitle.h"
#include "Sprite.h"
#include "FontSprite.h"
#include "SceneEffect.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneGameTitle::CSceneGameTitle( )
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameTitle::~CSceneGameTitle()
{

}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneGameTitle::Exec( CScene *pScene )
{
	CFontSprite *pFontSpr = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("TitleFont") );

	CSprite *pTitle = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Title") );
	
	CBGM *pTitleMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("TitleBGM") );
	
	pTitleMusic->GetBGMDevice()->SetVolume( 100 );
	
	
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{	
		pTitle->SetVisibleFlag( true );
	}
	
	pScene->GetAppDevice()->GetRenderer()->Clear();
	
	pScene->GetAppDevice()->GetRenderer()->Begin();
	
	static int count = 0;//アニメーション用カウンタ
	
	++count;	
	
	pTitle->Rendering();
	
	Sound::SPlayBlock Tbl[] =
	{
		{
			1,
			Sound::PLAY_TIME_AUTO,
			Sound::PLAY_TIME_AUTO,
		},
		
		{
			-1,
			4.0f,
			Sound::PLAY_TIME_AUTO,
		},
	};
	
	/*BGMの再生*/
	pTitleMusic->GetBGMDevice()->Play( Tbl, 2 );
	
	if( count >= 0 && count <= 30 )
	{	
		pFontSpr->Rendering();
	}
	
	else if( count >= 30 && count <= 60 )
	{
		
	}
	
	else
	{
		count = 0;
	}
	
	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_START ) )
	{
		CSoundEffect *snd	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Enter") );
		
		if( pScene->GetSceneState() == STATE_STANDBY )
		{
			snd->GetSEDevice()->Play( 0 );
		}
		
		pTitle->SetVisibleFlag( false );		
		
		pScene->SetNextScene( SCENE_MISSIONSELECT );
		
		pScene->SetSceneState( STATE_FADEOUT );
		
	}
	
	pScene->GetAppDevice()->GetRenderer()->End();
	
	pTitle->Exec();
	
	pFontSpr->Exec();
	
	CSprite *pFlagIcon = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("FlagIcon") );
	
	pFlagIcon->SetVisibleFlag( false );
	
}
