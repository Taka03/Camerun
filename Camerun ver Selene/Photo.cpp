//*============================================================================
//Photo.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Photo.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CPhoto::CPhoto(void) 
{
	m_fTargetDistance = 0;
	m_vTargetPos.Set(0, 0, 0);
	
	m_vPos.Set( 0, 0, 0 );
	
	m_IsExist = false;
	
}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//	vPos:位置
//==============================================================================
CPhoto::CPhoto( string name, Math::Vector2D vPos )
{
	m_DataName = name;
	
	m_fTargetDistance = 0;
	m_vTargetPos.Set(0, 0, 0);
	
	m_vPos.Set( vPos.x, vPos.y, 0 );
	m_vRot.Set( 0, 0, 0 );
	
	m_IsExist = false;
	
	m_Divnum.x = 1;
	m_Divnum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
}

//==============================================================================
//ターゲットの大きさの取得
//==============================================================================
//[input]
//	fDistance:設定する大きさ
//==============================================================================
void CPhoto::SetTargetDistance( float fDistance )
{
	m_fTargetDistance = fDistance;
}

//==============================================================================
//ターゲットの位置の設定
//==============================================================================
//[input]
//	pTex:設定するテクスチャ
//==============================================================================
void CPhoto::SetTargetPos( Math::Vector3D vPos )
{
	m_vTargetPos = vPos;
}

//==============================================================================
//ターゲット存在フラグの設定
//==============================================================================
//[input]
//	flag:設定するフラグ
//==============================================================================
void CPhoto::SetExistFlag( bool flag )
{
	m_IsExist = flag;
}


void CPhoto::SavePhoto( )
{

}

