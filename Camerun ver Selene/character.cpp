//*============================================================================
//character.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "character.h"


//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//=============================================================================
CCharacter::CCharacter( string name ) :m_pModel(NULL)
{
	m_DataName = name;
	
	m_vPos.Set( 0, 0, 0 );
	m_vRot.Set( 0, 0, 0 );
	m_vScale.Set( 15, 15, 15 );
	
	m_IsVisible = true;
	m_IsStop	= false;	
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//	vPos:設定する座標
//=============================================================================
CCharacter::CCharacter( string name, Math::Vector3D vPos ) :m_pModel(NULL), m_pRigidBody(NULL)
{
	m_DataName = name;
	
	m_IsVisible = true;
	m_IsStop	= false;
	m_IsSetFlag = false;	
	m_eType = OBJ_OTHER;
	
	
	m_vPos = vPos;
	m_vRot.Set( 0, 0, 0 );
	m_vScale.Set( 1, 1, 1 );
	
	
	
	m_vOldPos = vPos;
	m_vSetFlagPos.Set( 0, 0, 0 );
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_ActorIndex = 0;
	
	m_fSpeed = 0.0f;
	
	m_fWeight = 0.0f;
	
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		SAFE_RELEASE( m_pActorModel[numActor] ); 
	}
	
	SAFE_RELEASE( m_pModel );
	
}

//=============================================================================
//処理
//=============================================================================
void CCharacter::Init()
{
	
}



//=============================================================================
//処理
//=============================================================================
void CCharacter::Exec()
{
	m_vArrowPos = m_vPos + Math::Vector3D( 0, 1, 0 );
	
	/*姿勢のリセット*/
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->RotationX( toI( -m_vRot.y ) );
	
	
	m_pActorModel[m_ActorIndex]->RotationY( toI(m_vRot.x) - DEG_TO_ANGLE(90) );
	
	/*拡大縮小*/
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	/*移動*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	/*姿勢の更新*/
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
	//m_pRigidBody->SetPosition( m_vPos );
	
//	m_pRigidBody->SetRotation( m_vRot.y );	
	
}

//=============================================================================
//レンダリング
//=============================================================================
//[input]
//	index:インデックスに設定する値
//=============================================================================
void CCharacter::Rendering( int index )
{
	m_pActorModel[index]->RenderingRequest();
}

//=============================================================================
//参照カウンタの増加
//=============================================================================
void CCharacter::AddRef()
{
	m_pModel->AddRef();
	
	for( int actornum = 0;actornum < S_MAX;++actornum )
	{
		m_pActorModel[actornum]->AddRef();
	}	
}



//=============================================================================
//ファイル読み込み
//=============================================================================
//[input]
//	pRender:レンダリング用オブジェクト
//=============================================================================
void CCharacter::Load( Renderer::IRender *pRender )
{
	if( !m_DataName.empty() ) 
	{
		m_pModel = pRender->CreateModelFromFile( m_DataName.c_str() );
	}
}

//==============================================================================
//アクターの生成
//==============================================================================
//[input]
//	index:生成するアクターインデックス
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CCharacter::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	if( m_pModel != NULL )
	{
		m_pActorModel[index] = pSceneMgr->CreateActor( m_pModel );
	}
}

//=============================================================================
//コリジョンデータの作成
//=============================================================================
void CCharacter::CreateCollision()
{
	this->GetModelActor(S_MAIN)->Collision_Create();
}


//==============================================================================
//距離チェック
//==============================================================================
//[input]
//	pChara:チェックするキャラクター
//[return]
//	距離
//==============================================================================
float CCharacter::CheckDistance( CCharacter *pChara )
{
	Math::Vector3D vDirection = pChara->GetPosition() - m_vPos;
	
	return vDirection.Length();
	
}


//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pActor:チェックするマップアクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck( Scene::IMapActor *pActor )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// 一定値以上にしない（ゲーム的演出）
		m_fGravity = 1.0f;
	}
	
	if( m_fGravity > 0.0f )
	{
		//m_AnimID[ANIM_NOW] = 2;
		
	}

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	#if defined(DEBUG_MAP)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pActor->HitCheckByRay( vRay, Ret ) )
	{
		// 衝突位置に移動
		m_vPos = Ret.vHitPosition;
		// 重力加速初期化
		m_fGravity = 0.0f;
		
		return true;
	}
	
	return false;

}

//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pActor:チェックするマップアクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck2( Scene::IMapActor *pActor )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// 一定値以上にしない（ゲーム的演出）
		m_fGravity = 1.0f;
	}
	
	if( m_fGravity > 0.0f )
	{
		//m_AnimID[ANIM_NOW] = 2;
		
	}

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	m_vPos.y -= m_fGravity;
	
	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.1f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pActor->HitCheckByRay( vRay, Ret ) )
	{
		// 衝突位置に移動
		m_vPos = Ret.vHitPosition;
		// 重力加速初期化
		m_fGravity = 0.0f;
		
		
		return true;
	}
	
	
	return false;

}

//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pChara:判定するキャラクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara, int index )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	
	//if ( m_fGravity > 1.0f )
	//{
	//	// 一定値以上にしない（ゲーム的演出）
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.5f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(index)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// 衝突位置に移動
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
			
			//m_vDirection += pChara->GetSpeed();
			// 重力加速初期化
			m_fGravity = 0.0f;
		}
		
		return true;
	}
	
	return false;

}

//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pChara:判定するキャラクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	//
	//if ( m_fGravity > 1.0f )
	//{
	//	// 一定値以上にしない（ゲーム的演出）
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,5.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(S_MAIN)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// 衝突位置に移動
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
		
		
		//m_vDirection += pChara->GetSpeed();
		// 重力加速初期化
		
			return true;
		}
	}
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	pChara:判定するキャラクター
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( CCharacter *pChara )
{
	if( this->GetModelActor(S_MAIN)->Collision_Check( pChara->GetModelActor( S_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input/output]
//	ppChara:判定するキャラクター
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( CDraw3DObject **ppChara )
{
	CCharacter *obj = dynamic_cast<CCharacter *>( *ppChara );
	
	if( this->GetModelActor(S_MAIN)->Collision_Check( obj->GetModelActor( S_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	vRay:判定用のレイ
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay )
{
	if( this->GetModelActor(S_MAIN)->HitCheckByRay( vRay ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突結果格納用
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	if( this->GetModelActor(S_MAIN)->HitCheckByRay( vRay, Out ) )
	{
		return true;
	}	
	
	return false;
}


//=============================================================================
//剛体モデルの生成
//=============================================================================
//[input]
//	pWorld:物理シミュレーション用デバイス
//=============================================================================
void CCharacter::CreateRigidModel( Dynamics::ISimulationWorld *pWorld )
{
	m_pRigidModel = pWorld->CreateModel( m_pModel, true );
	
//	m_pRigidBody = pWorld->( m_pModel, true );
}


//=============================================================================
//アクターインデックスのセット
//=============================================================================
//[input]
//	index:インデックスに設定する値
//=============================================================================
void CCharacter::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

//=============================================================================
//フラグ設置判定フラグのセット
//=============================================================================
//[input]
//	flag:設定するフラグ
//=============================================================================
void CCharacter::SetFlag( bool flag )
{
	m_IsSetFlag = flag;
}

//=============================================================================
//旧座標の設定
//=============================================================================
//[input]
//	vPos:設定する座標
//=============================================================================
void CCharacter::SetOldPosition( Selene::Math::Vector3D vPos )
{
	m_vOldPos = vPos;
}


















