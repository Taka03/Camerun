//*=============================================================================
//EnemyManta.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyManta.h"
#include <vector>
#include <fstream>

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//	vPos:設定する座標
//	filename:敵の動きのファイル名
//=============================================================================
CEnemyManta::CEnemyManta( string name, Math::Vector3D vPos, string filename )  
{
	m_DataName = name;
	m_eType = OBJ_ENEMY;
	
	m_IsVisible = true;
	m_IsStop	= false;	
	m_IsSetFlag = false;
	m_IsStopKeyTime = false;
	
	float Scale = 15.0f;
	
	m_vPos = vPos;
	m_vOldPos = vPos;
	m_vScale.Set( Scale, Scale, Scale );
	
	m_vSetFlagPos.Set( 0, 0.5, 0 );
	
	m_pModel = NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 1.0f;
		m_AnimID[Anim] = 0;
	} 

	m_fKeyTime = 0.0f;
	
	m_fSpeed = 1.0f;
	
	std::ifstream ifs(filename.c_str());
	
	vector< float > vecKeyX;
	vector< float > vecKeyZ;
	vector< float > vecKeyRotX;
	
	while( !ifs.eof() )
	{
		float KeyTime = 0.0f;
		float KeyX = 0;
		float KeyZ = 0;
		float KeyRotX = 0;
		float fKeySpeed = 0;
		
		ifs >> fKeySpeed >> KeyX >> KeyZ >> KeyRotX;
		
		vecKeyX.push_back( KeyX );
		vecKeyZ.push_back( KeyZ );
		vecKeyRotX.push_back( KeyRotX );
		m_vKeySpeed.push_back( fKeySpeed );
				
	}
	
	Sint32 MaxKey = vecKeyX.size(); 
	
	m_pAnimX = new Math::Animation(MaxKey);
	m_pAnimZ = new Math::Animation(MaxKey);
	m_pAnimRotX = new Math::Animation(MaxKey);
	m_pAnimSpeed = new Math::Animation(MaxKey);
	
	/*キー時間の最初を0に設定しておく*/
	m_vDeltaKey.push_back( 0.0f );
	
	/*キーの差分時間を求める*/
	for( Sint32 i = 0;i < MaxKey - 1;++i )
	{
		float Delta = Abs( vecKeyZ.at( i + 1 ) - vecKeyZ.at( i ) );
		
		if( Delta <= 1.0f )
		{
			Delta = 3.0f;
		}
		
		float KeyTime = Delta / m_fSpeed;
		
		m_vDeltaKey.push_back( KeyTime );
		
		//float Delta = m_vKeyTime.at( i + 1 ) - m_vKeyTime.at( i );
		//
		//m_vDeltaKey.push_back( Delta );
	}
	
	/*キーをセット*/
	for( int Key = 0;Key < MaxKey; ++Key )
	{	
		static float KeyTime = 0.0f;
		
		KeyTime += m_vDeltaKey.at(Key);
		
		m_vKeyTime.push_back( KeyTime );

		m_pAnimX->SetKey( Key, KeyTime, vecKeyX.at(Key) );
		m_pAnimZ->SetKey( Key, KeyTime, vecKeyZ.at(Key) );
		m_pAnimRotX->SetKey( Key, KeyTime, vecKeyRotX.at(Key) );
		m_pAnimSpeed->SetKey( Key, KeyTime, m_vKeySpeed.at(Key) );
		
		if( Key == MaxKey - 1 )
		{
			m_fMaxKeyTime = KeyTime;
			KeyTime = 0.0f;
		}
		
	} 
	
	m_fWeight = 0.0f;
	
	m_KeyIndex = 0;
	
	m_IsChangeKeyTime = false;
	
	m_IsStopKeyTime = false;
	
}


//=============================================================================
//初期化
//=============================================================================
void CEnemyManta::Init()
{
	m_fKeyTime = 0.0f;
	
	m_KeyIndex = 0;
	
	m_IsChangeKeyTime = false;
	
	m_IsStopKeyTime = false;
	
	m_IsStop	= false;	
	
	m_IsSetFlag = false;
	
	m_IsLimitTime = false;
}

//=============================================================================
//移動処理
//=============================================================================
void CEnemyManta::MoveExec()
{
	if( !m_IsLimitTime )
	{
			
		#if defined(TEST_RELEASE)	
		
		#else
			
			m_fKeyTime += m_pAnimSpeed->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
			
		#endif
		
		
		#if defined( DEBUG_MAP_SEE )	
		
			
			if( m_fKeyTime >= m_vKeyTime.at( m_KeyIndex ) )
			{
				if( m_KeyIndex <= 0 )
				{	
					m_fKeyTime = 0.0f;
				}
				
				else
				{
					m_fKeyTime = m_vKeyTime.at( m_KeyIndex - 1 );
				}
			}	
		
		#else
			
				if( m_fKeyTime >=  m_vKeyTime.at( m_vKeyTime.size()-1 ) )
				{
					m_fKeyTime = 0.0f;
					m_IsLimitTime = true;
				}
			
			
		#endif
			
		
		
		//Move();
		
		static float fCount = 0;
		
		fCount = m_vKeyTime.at(m_KeyIndex);

		if( m_fKeyTime >= fCount ) 
		{
			m_KeyIndex++;
		}
		
		if( m_KeyIndex >= m_vDeltaKey.size() )
		{
			m_KeyIndex = 0;
		}	
		
		m_vPos.x = m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
		m_vPos.z = m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
		
		m_vRot.x = m_pAnimRotX->GetParameter( m_fKeyTime, ANIMATION_TYPE_TCB, 0.0f );
	}
	
	else
	{
		m_vPos.x += 1;
		m_vPos.z -= 1;
		
	}
	
}


//=============================================================================
//処理
//=============================================================================
void CEnemyManta::Exec()
{
		
	/*アニメカウンタの加算*/
	m_fAnimTime[ANIM_NOW] += 0.1f;
	
	float fLast = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[ANIM_NOW] );
	
	/*時間が最後まで到達*/
	while( m_fAnimTime[ANIM_NOW] > fLast ) 
	{
		/*最初に戻す*/
		m_fAnimTime[ANIM_NOW] -= fLast;
	}
	
	/*アニメーションの切り替え*/
	ChangeAnimation();
	
	//Update( m_Anim*m_AnimSpeed );
	
	//m_vPos.z -= m_pAnim->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	
	/*ターゲット矢印位置の設定*/
	m_vArrowPos = m_vPos + Math::Vector3D( 0, 2, 0 );
	
	m_vSetFlagPos = m_vPos + Math::Vector3D( 0, 0.1f, 0 );
	
	//m_vPos.z = Selene::Interpolation::Add( -40, -80, 5.0f, m_fKeyTime );//m_pAnim->GetParameter( m_fKeyTime, ::ANIMATION_TYPE_TCB, 0.0f );//Interpolation::Neville( m_pAnim->GetParameter( 0, ANIMATION_TYPE_TCB, 0.0f ), m_pAnim->GetParameter( 1, ANIMATION_TYPE_TCB, 1.0f ), m_pAnim->GetParameter( 2, ANIMATION_TYPE_TCB, 7.0f ), m_fKeyTime/60.0f );
	
	/*姿勢のリセット*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.x ) + DEG_TO_ANGLE(90) );
	
	/*移動の設定*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );

	// キャラに対してアニメーションを更新
	m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW] );
	
	// キャラの変換更新
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}
