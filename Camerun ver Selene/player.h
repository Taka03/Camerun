//*============================================================================
//player.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "CamObject.h"
#include "SoundEffect.h"
#include "camera.h"
#include "Particle.h"
#include "Menu.h"
#include "Flash.h"
#include "field.h"
#include "Sprite3D.h"

//=============================================================================
//enum
//=============================================================================
enum ePlayerAnim
{
	ANIM_STAND,
	ANIM_WALK,
	ANIM_RUN,
	ANIM_DASH,
	ANIM_FALL_START,
	ANIM_FALL,
	ANIM_FALL_END,
	ANIM_SET_GROUND,
	ANIM_SET_MOVE,
};

//enum eSetType
//{
//	SET_GROUND,
//	
//}

const int RUN_EFFECT_NUM = 4;
const int FLASH_EFFECT_NUM = 6;
const int FLASH_CHARA_NUM = 4;//フラッシュでとめることができる敵の数

//#define POP_UP 


//=============================================================================
//class
//=============================================================================
//[Desc]
//	プレイヤー用クラス
//=============================================================================
class CPlayer :public CCharacter
{
	private:

		Peripheral::IInputController *m_pCtrl;//コントローラー用デバイス	
		Peripheral::IJoystick *m_pJoy;//ジョイパッド用デバイス		
		
	private:
	
		CCamObject *m_pCamObj;//カメラオブジェクト
		
	
	private:
	
		bool	m_IsCameraMode;//カメラモードになっているかどうか
		bool	m_IsFlashMode;//フラッシュモードになっているかどうか
		bool	m_IsJumpFlag;//ジャンプ中かどうか
		bool	m_IsSettingFlag;//フラグ設置中かどうか
		
		Sint32 m_HoldTime;//ボタンを押している時間
		
		Collision::CLine3D m_vRay;//当たり判定用レイ
		
		int m_AnimID[ANIM_MAX];//アニメーションID
		float m_fAnimTime[ANIM_MAX];//現在のアニメーション時間
		eAnimState m_eAnimState;//アニメーション状態
		
	public:
	
		CPlayer(){};//コンストラクタ
		CPlayer( string name );//コンストラクタ
		CPlayer( string name, Math::Vector3D vPos );//コンストラクタ
		
		~CPlayer();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void AnimExec();//アニメーション用処理
		void MoveExec(){};//移動処理
		
	public:
	
		//void SetObject(  vPos, CDrawObject *obj );//オブジェクトの設置
		void SetFlash( CCharacter *obj[], Uint32 CharaMax, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] );//フラッシュ処理
		void SetFlash( CCharacter *obj, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] );//フラッシュ処理
		
		void SettingFlag( );//フラグ設置
		bool SetFlagToGround( Sound::ISound *pSound, CCharacter *pFlag );
		//bool SetFlagToObject( CCharacter *pChara[FLASH_CHARA_NUM], Sound::ISound *pSound, Scene::IMapActor *pMapActor );//オブジェクトへのフラグ設置
		bool SetFlagToObject( CCharacter *pChara, Sound::ISound *pSound );//オブジェクトへのフラグ設置
		
		void AdjustDirection();//方向補正
		void Jump(  );//ジャンプ処理
		void Move( CCamera *pCam, CParticle *pParticle[RUN_EFFECT_NUM] );//移動処理
		void Move( );//移動処理
		void Move( Peripheral::IInputController *pCtrl );//移動処理
		bool MoveCheck( Scene::IMapActor *pActor );//移動チェック
		bool MoveCheck( Scene::IModelActor *pActor );//移動チェック
		bool MoveCheck( CCharacter *pChara );//移動チェック
		bool GroundCheck( CField *pField );	//地面チェック
		bool GroundCheck( CCharacter *pChara, int index );//地面チェック
		bool FlagCheck( Scene::IMapActor *pMapActor );//フラグが設置できるかどうか
		bool FlagObjectCheck( CCharacter *pChara[], Uint32 CharaMax, Sound::ISound *pSnd, CCharacter  **ppFlashedChara );//フラグが設置できるか判定
		bool SettableFlagCheck( CCharacter *pChara, CSprite3D *pSpr );//フラグ設置可能チェック
		
		void MoveAdjust();//移動補正
		void GroundAdjust();//地面補正
		
		void RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CMenu *pMenu );//フラグの回収
		void RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CSprite3D *pSpr, CCharacter *pFlag );//フラグの回収
		
		
		void ChangeCameraMode( Sound::ISound *pSnd );//カメラモードの切り替え
		void UpdateAnimation( );//アニメーションの変更
		void ChangeAnimation( int animID );//アニメーションの切り替え
		
		//カメラオブジェクトの設定		
		void GetCamObject( CCamObject *pCamObj )
		{
			m_pCamObj = pCamObj;
		}
		
		
		
	/*Set系*/
	public:
	
		void SetCameraModeFlag( bool flag );//カメラモード判定フラグのセット
		void SetFlashModeFlag( bool flag );//フラッシュモード判定フラグのセット
		void SetDirection();//位置の設定
		void SetController( Peripheral::IInputController *pCtrl, Peripheral::IJoystick *pJoy );//コントローラー用デバイスの設定
		void SetAnimationID( eAnimType index,  int animID );//アニメIDの設定
		
		/*アニメーション状態の設定*/
		void SetAnimState( eAnimState state )
		{
			m_eAnimState = state;
		}
		
		/*フラグ設置アニメーション中フラグの設定*/
		void SetSettingFlag( bool flag )
		{
			m_IsSettingFlag = flag;
		}
		
		/*アニメーション時間の設定*/
		void SetAnimationTime( int index, float Time )
		{
			m_fAnimTime[index] = Time;	
		}
		
		

	/*Get系*/
	public:
	
		//カメラモードになっているかどうかの取得	
		bool	IsCameraMode()
		{
			return m_IsCameraMode;
		}
		
		//フラッシュモードになっているかどうかの取得	
		bool	IsFlashMode()
		{
			return m_IsFlashMode;
		}
		
		//当たり判定用レイの取得
		Collision::CLine3D GetRay() const
		{
			return m_vRay;
		}
		
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
		
		/*フラグ設置アニメーション中フラグの設定*/
		bool GetSettingFlag()
		{
			return m_IsSettingFlag;
		}
		
};