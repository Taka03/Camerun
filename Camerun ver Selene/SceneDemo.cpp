//*============================================================================
//SceneDemo.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneDemo.h"
#include "EnemyAmeus.h"
#include "EnemyMouse.h"
#include "EnemyBird.h"
#include "EnemyManta.h"
#include <math.h>
#include <iostream>
#include <fstream>


//=============================================================================
//コンストラクタ
//=============================================================================
CSceneDemo::CSceneDemo( )
{
	m_vOldPos.Set( 0, 0, 0 );
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneDemo::~CSceneDemo(void)
{
	//SAFE_DELETE( pScene );
}

//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
void CSceneDemo::Exec( CScene *pScene )
{
	CFontSprite *pChatFont = dynamic_cast<CFontSprite *>( pScene->GetGameObject()->FindObjectFromName("ChatFont") );
	
	pChatFont->SetRefCount( 0 );
	pChatFont->SetStrCount( 1 );
	pChatFont->SetTextEndFlag( false );
	
	CMission *pMission = pScene->GetMissionMgr()->GetMission( pScene->GetMissionMgr()->GetMissionNo() );//CMissionTutorial( dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ) );
	
	CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
	
	CField *objField = dynamic_cast<CField *>( pScene->Get3DObject()->FindObjectFromName("Field") );
	
	CPlayer *objPlayer = dynamic_cast<CPlayer *>( pScene->Get3DObject()->FindObjectFromName("Player") );
	CTrain *objTrain = dynamic_cast<CTrain *>( pScene->Get3DObject()->FindObjectFromName("Train") );
	
	CSoundEffect *sndTrain	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("STrain") );
	CSoundEffect *sndSetFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Flag") );
	CSoundEffect *sndRecallFlag	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("RecallFlag") );
	
	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("GameBGM") );
	CBGM *pChatMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("ChatBGM") );
	
	pChatMusic->GetBGMDevice()->Stop() ;
	
	CCharacter *objTarget	= dynamic_cast<CCharacter *>( pMission->GetTarget() );//dynamic_cast<CEnemy *>( pScene->Get3DObject()->FindObjectFromName("Ameus") );

	CCharacter *objStar = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Star") );
	
	CSprite *objReady = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Ready") );
	CSprite *objGo = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Go") );
	
	CParticle *objRunEffect[RUN_EFFECT_NUM];
	
	for( int i = 0;i < RUN_EFFECT_NUM;++i )
	{	
		char Temp[12];
		
		sprintf( Temp, "RunEffect%d", i);
		
		objRunEffect[i] = dynamic_cast<CParticle *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	
	for	( int i = 0;i < RUN_EFFECT_NUM;++i )
	{
		objRunEffect[i]->SetRenderDevice( pScene->GetAppDevice()->GetRenderer() );
	}
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{	
		pGameMusic->GetBGMDevice()->Play( );
		
	}
	
	if( pScene->GetSceneState() == STATE_FADEOUT )
	{
		objReady->SetVisibleFlag( false );
	}
	
	/*プレイヤー用にコントローラーデバイスを取得*/
	objPlayer->SetController( pScene->GetJoyPad()->GetController(), pScene->GetJoyPad()->GetJoyStick() );
	
	CCamObject *objCamObj = dynamic_cast<CCamObject *>( pScene->Get3DObject()->FindObjectFromName("CamObj") );
	CCharacter *objFlag	  = dynamic_cast<CCharacter *>( pScene->Get3DObject()->FindObjectFromName("Flag") );
	
	/*利便性を考えて、プレイヤーに埋め込む*/
	objPlayer->GetCamObject( objCamObj );
	//objPlayer->GetFlagObject( objFlag );
	
	/*全キャラに対して当たり判定データを作成*/
	pScene->Get3DObject()->CreateCollision();
	
	//-------------------------------------------------------------------------
	//描画開始
	//-------------------------------------------------------------------------
	pScene->GetAppDevice()->GetRenderer()->Begin();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーンマネージャーの内容を実際にレンダリング
	/////////////////////////////////////////////////////////////////////////////////////////////
	pScene->GetAppDevice()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Rendering( false );
	
	if( objReady->GetVisibleFlag() )
	{	
		objReady->Rendering();
	}
	
	else if( objGo->GetVisibleFlag() )
	{
		objGo->Rendering();
	}
	

	CEnemyAmeus *objAmeus = dynamic_cast<CEnemyAmeus *>( pScene->Get3DObject()->FindObjectFromName("Ameus") ); 
	CEnemyBird *objBird[BIRD_MAX];
	
	for( int i = 0;i < BIRD_MAX;++i )
	{	
		char Temp[20];
		
		sprintf( Temp, "Bird%d", i+1 );
		objBird[i]  = dynamic_cast<CEnemyBird *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	CEnemyMouse *objMouse[MOUSE_MAX];
	
	for( int i = 0;i < MOUSE_MAX;++i )
	{	
		char Temp[20];
		
		sprintf( Temp, "Mouse%d", i+1 );
		
		objMouse[i] = dynamic_cast<CEnemyMouse *>( pScene->Get3DObject()->FindObjectFromName(Temp) );
	}
	
	CEnemyManta *objManta = dynamic_cast<CEnemyManta *>( pScene->Get3DObject()->FindObjectFromName("Manta") );
	
	CSoundEffect *sndMouse = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Mouse") );
	CSoundEffect *sndBird = dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Bird") );
	
	
	/*幽霊を撮れのときのみアメウスを表示させる*/
	if( pScene->GetMissionMgr()->GetMissionNo() == 1 )
	{
		objAmeus->SetVisibleFlag( true );
	}
	
	else
	{
		objAmeus->SetVisibleFlag( false );
	}
	
	/*マンタを撮れのときのみマンタを表示させる*/
	if( pScene->GetMissionMgr()->GetMissionNo() == 4 )
	{
		objManta->SetVisibleFlag( true );
	}
	
	else
	{
		objManta->SetVisibleFlag( false );
	}
	
	/*気絶エフェクトの導入*/
	for( int i = 0;i < BIRD_MAX;++i )
	{
		objBird[i]->GetStunEffect( objStar );
	}
	
	for( int i = 0;i < MOUSE_MAX;++i )
	{
		objMouse[i]->GetStunEffect( objStar );
	}
	
	if( pScene->GetSceneState() == STATE_STANDBY )
	{
		float fDistance = objPlayer->CheckDistance( objTrain );
		
		objTrain->PlaySnd( sndTrain->GetSEDevice(), fDistance );
	
		for( int i = 0;i < BIRD_MAX;++i )
		{
			fDistance = objPlayer->CheckDistance( objBird[i] );
			
			objBird[i]->PlaySnd( sndBird->GetSEDevice(), fDistance );
		}
		
		for( int i = 0;i < MOUSE_MAX;++i )
		{
			fDistance = objPlayer->CheckDistance( objMouse[i] );
				
			objMouse[i]->PlaySnd( sndMouse->GetSEDevice(), fDistance );
		
		}
	}
	
	/*描画終了*/
	pScene->GetAppDevice()->GetRenderer()->End();
	
	objPlayer->Move( objCamMain, objRunEffect );
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーン情報構築
	/////////////////////////////////////////////////////////////////////////////////////////////


	//--------------------------------------------------------------------------
	//メイン画面
	//--------------------------------------------------------------------------
	// シーン情報リセット
	//   Scene::ISceneManagerインターフェイスを使ったシーン管理情報を初期化します。
		
	/*描画位置の設定*/
	pScene->GetSceneMgr(S_MAIN)->SetRenderPos( Math::Vector2D(0, 0) );
	
	/*パラメータの設定*/
	pScene->GetSceneMgr(S_MAIN)->SetParameter();

	// 平行光源
	//   シーンに対して平行光源を設定します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Directional(
		Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ライトの方向
		Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ライトの色

	// アンビエント
	// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SetLightParameter_Ambient(
		Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// 天球の色
		Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// 地表の色

	// カメラの注視目標
	objCamMain->SetTargetPos( objPlayer->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f) );

	/*トランスフォームの設定*/
	objCamMain->SetTransformDemo();
	
	const int MAX_KEY = 4;
	
	//Math::Animation AnimX(MAX_KEY);
	//Math::Animation AnimY(MAX_KEY);
	//Math::Animation AnimZ(MAX_KEY);
	//
	//for( int i = 0;i < MAX_KEY;++i )
	//{	
	//	AnimX.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	AnimY.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	AnimZ.SetKey( i, 10.0f * toF(MAX_KEY), i * 100 );
	//	
	//}
	
	static float fAnimTime = 0.0f;
	
	fAnimTime += 1.0f / 60.0f;
	
	// 雲の移動
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );
	
	//objCamMain->SetPosition( Math::Vector3D( AnimX.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ),
											 //AnimY.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ),
											 //AnimZ.GetParameter(fAnimTime, ANIMATION_TYPE_LINEAR, 0.0f ) ) );											 
											 
	if( fAnimTime >= 40.0f )
	{
		fAnimTime = 0.0f;
	}											 
											 

	objCamMain->SetRotate( Math::Vector3D( objPlayer->GetRotate().y,  DEG_TO_ANGLE( 90 ) -objPlayer->GetRotate().x , objCamMain->GetRotate().z ) );
	
	
	//------------------------------------------------
	//地面チェック
	//------------------------------------------------
	
	/*マップとの判定*/
	if( objPlayer->GroundCheck( objField ) )
	{
		
	}

	pScene->Get3DObject()->SetActorIndex(S_MAIN);

	pScene->Get3DObject()->MoveExec();
	
	/*処理*/
	pScene->Get3DObject()->Exec();
	
	objReady->Exec();
	objGo->Exec();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// シーンへのレンダリングリクエスト
	/////////////////////////////////////////////////////////////////////////////////////////////

	// シーン管理
	//   Scene::ISceneManagerインターフェイスを使ったシーン管理を開始します。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->Begin( false );
	
	// スカイドームのレンダリング
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->SceneSkydoom_Rendering();

	objField->Rendering(S_MAIN);
	
	//レンダリング
	pScene->Get3DObject()->Rendering(S_MAIN);
	
	// シーン管理を終了
	//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
	pScene->GetSceneMgr(S_MAIN)->GetSceneMgr()->End();
	
	static int count = 0;
	
	count ++;
	
	if( count > 0 && count <= 60 )
	{
		//objReady->SetVisibleFlag( true );
	}
	
	if( count > 60 )
	{
		objReady->SetVisibleFlag( false );
		objGo->SetVisibleFlag( true );
	}
	
	pScene->SetNextScene( SCENE_GAMEMAIN );
	
	if( count >= 120 )
	{	
		objReady->SetVisibleFlag( false );
		objGo->SetVisibleFlag( false );
		
		pScene->SetFadeTime( 10.0f );
		
		pScene->SetSceneState( STATE_FADEOUT );
		
		count = 0;
		
		
	}
		

}

