//*=============================================================================
//EnemyBird.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyBird.h"
#include <fstream>

//==============================================================================
//enum
//==============================================================================
//鳥アニメーションタイプ
enum eBirdAnimType
{
	ANIM_STAND,
	ANIM_WALK,
	ANIM_FLY_START,
	ANIM_FLY,
	ANIM_FLY_END,
	ANIM_STUN,
};


//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//	vPos:設定する座標
//	filename:敵の動きのファイル名
//=============================================================================
CEnemyBird::CEnemyBird( string name, Math::Vector3D vPos, string filename )  
{
	m_DataName = name;
	m_eType = OBJ_ENEMY;
	
	m_IsVisible = true;
	m_IsStop	= false;	
	m_IsSetFlag = false;
	m_IsStopKeyTime = false;
	
	float Scale = 1.0f;
	
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
	vector< float > vecKeyY;
	vector< float > vecKeyZ;
	vector< float > vecKeyRotX;
	
	while( !ifs.eof() )
	{
		float KeyTime = 0.0f;
		float KeyX = 0;
		float KeyY = 0;
		float KeyZ = 0;
		float KeyRotX = 0;
		float fKeySpeed = 0;
		
		ifs >> fKeySpeed >> KeyX >> KeyY >> KeyZ >> KeyRotX;
		
		vecKeyX.push_back( KeyX );
		vecKeyY.push_back( KeyY );
		vecKeyZ.push_back( KeyZ );
		vecKeyRotX.push_back( KeyRotX );
		m_vKeySpeed.push_back( fKeySpeed );
				
	}
	
	Sint32 MaxKey = vecKeyX.size(); 
	
	m_pAnimX = new Math::Animation(MaxKey);
	m_pAnimY = new Math::Animation(MaxKey); 
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
		m_pAnimY->SetKey( Key, KeyTime, vecKeyY.at(Key) );
		
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
void CEnemyBird::Init()
{
	m_fKeyTime = 0.0f;
	
	m_KeyIndex = 0;
	
	m_IsChangeKeyTime = false;
	
	m_IsStopKeyTime = false;
	
	m_IsStop	= false;	
	
	m_IsSetFlag = false;
	
	m_IsFly = true;
	
}

//=============================================================================
//処理
//=============================================================================
void CEnemyBird::Exec()
{
	//if( m_fKeyTime >= 20.0f && m_fKeyTime <= 20.1f && !m_IsStop  )
	//{
	//	m_AnimID[ANIM_NEXT] = ANIM_STAND;
	//}
	//
	if( m_IsStop )
	{
		m_AnimID[ANIM_NOW] = ANIM_STUN;
	}
	
	else if( m_IsFly )
	{
		m_AnimID[ANIM_NEXT] = ANIM_FLY;
	}
	
	else
	{
		m_AnimID[ANIM_NEXT] = ANIM_WALK;
	}
	
	//Update( m_Anim*m_AnimSpeed );
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] += 0.5f;
		
		float fLast = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] );
		
		/*時間が最後まで到達*/
		while( m_fAnimTime[Anim] > fLast ) 
		{
			/*最初に戻す*/
			m_fAnimTime[Anim] -= fLast;
		}
	}
	
	/*アニメーションの切り替え*/
	ChangeAnimation();
	
	if( m_IsStop )
	{	
		m_pStunEffect->SetPosition( m_vPos + Math::Vector3D( 0, 1.2f, 0 ) );
	}
	
	static Math::Vector3D vRot;
	
	vRot.x -= DEG_TO_ANGLE(1);
	vRot.y = DEG_TO_ANGLE(1);
	vRot.z = DEG_TO_ANGLE(1);
	
	m_pStunEffect->SetRotate( vRot );
	
	/*処理*/
	m_pStunEffect->Exec();
	
	m_vSetFlagPos = m_vPos + Math::Vector3D( 0, 0.5f, 0 );
	
	/*姿勢のリセット*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.x ) + DEG_TO_ANGLE(90) );
	
	/*移動の設定*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );

	// キャラに対してアニメーションを更新
	m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW],
												  m_AnimID[ANIM_NEXT], m_fAnimTime[ANIM_NEXT], m_fWeight );
	
	// キャラの変換更新
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
	
}

//=============================================================================
//移動処理
//=============================================================================
void CEnemyBird::MoveExec()
{
	if( !m_IsStopKeyTime )
	{	
		m_fKeyTime += m_pAnimSpeed->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	}
	
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
			}
		
	#endif
		
	static float fCount = 0;
	
	fCount = m_vKeyTime.at(m_KeyIndex);
	
	m_vPos.x =  m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
	m_vPos.y =  m_pAnimY->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
	m_vPos.z =  m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
	
	static int count = 0;
	
	static int flycount = 0;
	
	static bool IsGround = false;//グラウンド
	
	int Count_Speed = 1;
	
	const int FLY_COUNT_MAX = 60*10;
	
	//if( m_IsFly )
	//{
	//	m_vPos.y = m_vOldPos.y;
	//}
	//
	//else
	//{
	//	m_vPos.y = ::Interpolation::Sin( m_vOldPos.y, 0.0f, FLY_COUNT_MAX, flycount );
	//	flycount += Count_Speed;
	//	
	//}
	
	
	if( m_IsFly )
	{
		if( m_vPos.y <= 0.0f )
		{
			m_IsFly = false;
		}
		
	}
	
	if( !m_IsFly )
	{
		if( m_vPos.y > 0.0f )
		{
			m_IsFly = true;
		}
	
	}
	
	m_vRot.x = m_pAnimRotX->GetParameter( m_fKeyTime, ANIMATION_TYPE_TCB, 0.0f );
	

}

//=============================================================================
//レンダリング
//=============================================================================
//[input]
//	index:インデックス
//=============================================================================
void CEnemyBird::Rendering( int index )
{
	m_pActorModel[index]->RenderingRequest();
		
	if( m_IsStop )
	{	
		m_pStunEffect->Rendering(index);
	}
}

//=============================================================================
//鳥の鳴き声の再生
//=============================================================================
//[input]
//	pSound:サウンドデバイス
//	fDistance:距離
//=============================================================================
void CEnemyBird::PlaySnd(Selene::Sound::ISound *pSound, float fDistance )
{
	static float Pan = -100.0f;
	
	Pan += 1.0f;
	
	if( Pan >= 100 )
	{
		Pan = 100;
	}
	
	pSound->SetVolume( 0, 100 - (fDistance * 0.5f) );
	
	pSound->Play( 0, true );
	
	
}
