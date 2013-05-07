//*============================================================================
//SceneEffect.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneEffect.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	eEffect:�ݒ肷��G�t�F�N�g
//	count:�t�F�[�h����
//=============================================================================
CSceneEffect::CSceneEffect( eSceneEffect eEffect, int count ): m_eEffect(eEffect), m_FadeTime(count)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneEffect::~CSceneEffect()
{

}

//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
void CSceneEffect::Exec( CScene *pScene )
{
	if( m_eEffect == FADE_IN )
	{
		FadeIn( pScene );
	}
	
	else if( m_eEffect == FADE_OUT )
	{
		FadeOut( pScene );
	}
}

//=============================================================================
//�t�F�[�h�C��
//=============================================================================
//[input]
//	pScene:�V�[��
//=============================================================================
void CSceneEffect::FadeIn( CScene *pScene )
{
	static Sint32 Alphacount = 0;
	
	static Sint32 Alpha	= 255;
	
	Alphacount++;
	
	Alpha = Interpolation::Flat(255, 0, toI(60*m_FadeTime), Alphacount);

	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ),toF(  pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
	
	if( Alpha <= 0 )
	{
		Alpha = 255;
		Alphacount = 0;
		
		pScene->SetSceneState( STATE_STANDBY );
		
		pScene->ChangeScene( pScene->GetNextScene() );

		//pScene->Get2DObject()->RemoveObject( pTitle );
	}
	
}

//=============================================================================
//�t�F�[�h�A�E�g
//=============================================================================
//[input]
//	pScene:�V�[��
//=============================================================================
void CSceneEffect::FadeOut( CScene *pScene )
{
	static Sint32 Alphacount = 0;
	
	static Sint32 Alpha	= 0;
	
	Alphacount++;
	
	Alpha = Interpolation::Flat(0, 255, toI(60*m_FadeTime), Alphacount);

	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ),toF(  pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
	
	if( Alpha >= 255 )
	{
		Alpha = 0;
		Alphacount = 0;

		pScene->SetSceneState( STATE_STANDBY );
		
		pScene->ChangeScene( pScene->GetNextScene() );

		//pScene->Get2DObject()->RemoveObject( pTitle );
	}
	
	
	
}

//=============================================================================
//���C�v
//=============================================================================
//[input]
//	pScene:�V�[��
//=============================================================================
void CSceneEffect::Wipe( CScene *pScene )
{
	
	static Sint32 Alphacount = 0;
	
	static Sint32 Alpha	= 255;
	
	Alphacount++;
	
	Alpha = Interpolation::Flat(255, 0, toI(60*m_FadeTime), Alphacount);

	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	pScene->GetAppDevice()->GetRenderer()->FillRect( Math::Rect2DF( 0, 0, toF( pScene->GetAppDevice()->GetScreenWidth() ),toF(  pScene->GetAppDevice()->GetScreenHeight() ) ), CColor( 0, 0, 0, Alpha ) );
	
	if( Alpha <= 0 )
	{
		Alpha = 255;
		Alphacount = 0;
		
		pScene->SetSceneState( STATE_STANDBY );
		
		pScene->ChangeScene( pScene->GetNextScene() );

		//pScene->Get2DObject()->RemoveObject( pTitle );
	}
	
}



