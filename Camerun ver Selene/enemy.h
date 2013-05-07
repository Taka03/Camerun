//*============================================================================
//enemy.h
//*============================================================================
//[history]
//	08/03/09　修正開始
//[author]
//	Taka
//=============================================================================

#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "Sprite3D.h"
#include <vector>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	敵用クラス
//=============================================================================
class CEnemy :public CCharacter
{
	protected:
	
		CCharacter *m_pStunEffect;//気絶エフェクト
		
		Math::Animation *m_pAnimX;//X軸のアニメーション
		Math::Animation *m_pAnimY;//Y軸のアニメーション
		Math::Animation *m_pAnimZ;//Z軸のアニメーション
		Math::Animation *m_pAnimRotX;//X方向回転のアニメーション
		Math::Animation *m_pAnimSpeed;//キースピード
		float m_fKeyTime;//キーアニメーション時間
		float m_fKeySpeed;//キースピード
		
		float m_fMaxKeyTime;//最大キー時間
		
		vector< float > m_vDeltaKey;//キー時間の差分
		vector< float > m_vKeySpeed;//キースピード
		vector< float > m_vKeyTime;//キー時間
		
		int m_AnimID[ANIM_MAX];//アニメーションID
		float m_fAnimTime[ANIM_MAX];//現在のアニメーション時間
		
		bool m_IsChangeKeyTime;//キータイムが変更されたかどうか
		Uint32 m_KeyIndex;//現在参照しているキーのインデックス
		
		bool m_IsStopKeyTime;//キータイムが止まっているかどうか
	
	public:
	
		CEnemy(){};//コンストラクタ
		CEnemy( string name, Math::Vector3D vPos );//コンストラクタ
		~CEnemy();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		virtual void MoveExec(){};//移動処理
		
	public:
	
		void FlashedState( );//フラッシュを浴びた状態の処理
		void ChangeAnimation( );//アニメーションの変更
		
		void ChangeKeyTime( Peripheral::IMouse *pMouse );//キータイムの変更
		void ChangeKeySpeed( Peripheral::IInputController *pCtrl );//キースピードの変更
		
		
	public:

		void SetAnimationID( eAnimType index,  int animID );//アニメIDの設定
		
		/*気絶エフェクトの取得*/
		void GetStunEffect( CCharacter *pEffect )
		{
			m_pStunEffect = pEffect;
			pEffect->AddRef();
		}
		
	
		
	public:
	
		/*アニメーションIDの取得*/
		int GetAnimationID( int index )
		{
			return m_AnimID[index];
		}
		
		/*現在のアニメーション時間の取得*/	
		float GetAnimationTime( int index )
		{
			return m_fAnimTime[index];
		}
		
		/*キーアニメーション時間の取得*/
		float GetKeyTime( )
		{
			return m_fKeyTime;
		}
	
	
};