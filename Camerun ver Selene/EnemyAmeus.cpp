//*=============================================================================
//EnemyAmeus.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyAmeus.h"
#include <fstream>
#include <vector>

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//	vPos:設定する座標
//	filename:敵の動きのファイル名
//=============================================================================
CEnemyAmeus::CEnemyAmeus( string name, Math::Vector3D vPos, string filename )  
{
	m_DataName = name;
	m_eType = OBJ_ENEMY;
	
	m_IsVisible = true;
	m_IsStop	= false;	
	m_IsSetFlag = false;
	
	m_IsHit = false;
	
	float Scale = 1.0f;
	
	m_vPos = vPos;
	m_vOldPos = vPos;
	m_vRot.Set( 0, -DEG_TO_ANGLE(60), 0 );
	m_vScale.Set( Scale, Scale, Scale );
	
	m_pModel = NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 0.0f;
		m_AnimID[Anim] = 0;
	} 

	m_fKeyTime = 0.0f;
	
	m_fSpeed = 2.0f;
	
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
		}
		
	} 
	
	m_fWeight = 0.0f;
	
	m_KeyIndex = 0;
	
	m_IsChangeKeyTime = false;
	
	m_IsStopKeyTime = false;
	
	//m_pAnim->SetKey
	
}


//=============================================================================
//初期化
//=============================================================================
void CEnemyAmeus::Init()
{
	m_fKeyTime = 0.0f;
	
	m_vRot.Set( 0, -DEG_TO_ANGLE(60), 0 );
	
	m_KeyIndex = 0;
	
	m_fWeight = 0.0f;
	
	m_IsChangeKeyTime = false;
	
	m_IsStopKeyTime = false;
	
	m_IsStop	= false;	
	
	m_IsSetFlag = false;
	
}

//=============================================================================
//処理
//=============================================================================
void CEnemyAmeus::Exec()
{
	
	
	
	//Update( m_Anim*m_AnimSpeed );
	
	static Sint32 counter = 0;
	
	counter++;
	
	
	
	//if( m_vPos.z < -540.0f )
	//{
	//	m_vPos.z = -40.0f;
	//	counter = 0;
	//}
	
	//m_vPos.z = Selene::Interpolation::Flat( m_pAnimZ->GetParameter( 0, ANIMATION_TYPE_TCB, 0.0f ),
	//										m_pAnimZ->GetParameter( 20, ANIMATION_TYPE_TCB, 0.0f ),
	//										m_fMaxKeyTime,
	//										m_fKeyTime );
	/*ターゲット矢印位置の設定*/
	m_vArrowPos = m_vPos + Math::Vector3D( 0, 1.5, 0 );

	
	m_vSetFlagPos = m_vPos + Math::Vector3D( 0, 1, 0 );
	
	/*姿勢のリセット*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationX( toI( -m_vRot.y ) - DEG_TO_ANGLE(90)  );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.x ) + DEG_TO_ANGLE(90) );
	
	/*移動の設定*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	//m_fNowAnimTime += 1.0f;

	/*時間が最後まで到達*/
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] ++;
		
		/*時間が最後まで到達*/
		if ( m_fAnimTime[Anim] > m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] ) )
		{
			/*最初に戻す*/
			m_fAnimTime[Anim] = 1.0f;
		}
	}

	// キャラに対してアニメーションを更新
	m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW] );
	
	// キャラの変換更新
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//移動
//=============================================================================
void CEnemyAmeus::MoveExec()
{
	if( m_IsHit )
	{
		static int count = 0;
		
		count ++;
		
		m_vRot.x += DEG_TO_ANGLE( 30 );
		
		Sint32 MeshCount = m_pActorModel[m_ActorIndex]->GetMeshCount();
		
		for( Sint32 mesh = 0;mesh < MeshCount;++mesh )	
		{
			Sint32 MateCount = m_pActorModel[m_ActorIndex]->GetMeshMaterialCount( mesh );
			
			for( Sint32 mate = 0;mate < MateCount;++mate )	
			{
				//m_pActorModel[m_ActorIndex]->MeshMaterial_SetDrawType( mesh, mate, DRAW_TYPE_ADD );
				
				//m_pActorModel[m_ActorIndex]->me( mesh, mate, Math::Vector4D( 200, 200, 200, 128 ) );
				//
			}
			
		}
		
		if( count > 60 )
		{	
			count = 0;
			m_IsHit = false;
			
			for( Sint32 mesh = 0;mesh < MeshCount;++mesh )	
			{
				Sint32 MateCount = m_pActorModel[S_MAIN]->GetMeshMaterialCount( mesh );
				
				for( Sint32 mate = 0;mate < MateCount;++mate )	
				{
					//m_pActorModel[m_ActorIndex]->MeshMaterial_SetDrawType( mesh, mate, DRAW_TYPE_NORMAL );
				}
				
			}
			
			Math::CRandom CRand;
			
			if( m_pCore != NULL )
			{	
				CRand.Seed( m_pCore->GetSyncCount() );
			}
			
			float Rand = CRand.GetFloat( 0, 20 );
			
			m_fKeyTime = m_vKeyTime.at( Rand );
			
			
			#if defined(TEST_RELEASE)	
			
			#else
			
			#endif
		}
		
	}
	
	else
	{
		#if defined(TEST_RELEASE)	
		
		#else
			
			m_fKeyTime += m_pAnimSpeed->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
		#endif
		
			
			
	
		#if defined( DEBUG_MAP_SEE )	
		
			if( m_fKeyTime >=  m_vKeyTime.at( m_vKeyTime.size()-1 ) )
			{
				m_fKeyTime = 0.0f;
			}
		
		
			
			//if( m_fKeyTime >= m_vKeyTime.at( m_KeyIndex ) )
			//{
			//	if( m_KeyIndex <= 0 )
			//	{	
			//		m_fKeyTime = 0.0f;
			//	}
			//	
			//	else
			//	{
			//		m_fKeyTime = m_vKeyTime.at( m_KeyIndex - 1 );
			//	}
			//}	
		
		#else
			
			if( m_fKeyTime >=  m_vKeyTime.at( m_vKeyTime.size()-1 ) )
			{
				m_fKeyTime = 0.0f;
			}
			
			
		#endif
			
		
		
		//Move();
		
		
		m_vPos.x =  m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
		m_vPos.z =  m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f ) ;
		
//		static float fCount = 0;
		
//		fCount = m_vKeyTime.at(m_KeyIndex);
		//
		//m_vPos.x = Interpolation::Flat( m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_TCB, 0.0f ) ,
		//								m_pAnimX->GetParameter( m_fKeyTime + m_vDeltaKey.at(m_KeyIndex), ANIMATION_TYPE_TCB, 0.0f ),
		//								fCount,
		//								m_fKeyTime );
		//							
		//m_vPos.z = Interpolation::Flat( m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_TCB, 0.0f ) ,
		//								m_pAnimZ->GetParameter( m_fKeyTime + m_vDeltaKey.at(m_KeyIndex), ANIMATION_TYPE_TCB, 0.0f ),
		//								fCount,
		//								m_fKeyTime );
		//
		//if( m_fKeyTime >= fCount ) 
		//{
		//	m_KeyIndex++;
		//}
		//
		//if( m_KeyIndex >= m_vDeltaKey.size() )
		//{
		//	m_KeyIndex = 0;
		//}	
											
										
		m_vRot.x = m_pAnimRotX->GetParameter( m_fKeyTime, ANIMATION_TYPE_TCB, 0.0f );
	}
	

}

//=============================================================================
//アニメーションキーのセット
//=============================================================================
//[input]
//	L:Luaの状態
//=============================================================================
int CEnemyAmeus::SetAnimKey(lua_State *L)
{
	//int x = lua_tonumber( L, 1 );
	//int y = lua_tonumber( L, 2 );
	//int z = lua_tonumber( L, 3 );
	
	return 1;
}



