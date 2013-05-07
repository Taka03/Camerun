//*============================================================================
//character.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "c3dobject.h"

//=============================================================================
//enum
//=============================================================================

enum eAnimType
{
	ANIM_NOW,
	ANIM_NEXT,
	ANIM_MAX,
};

//アニメーションの状態
enum eAnimState
{
	ANIM_STANDBY,//待機中
	ANIM_CHANGESTART,//切り替え開始
	ANIM_CHANGE,//切り替え中
	ANIM_CHANGEEND,//切り替え終了
};

//#define DEBUG_MAP


//=============================================================================
//class
//=============================================================================
//[Desc]
//	キャラクター用クラス
//=============================================================================
class CCharacter :public CDraw3DObject
{
	private:
	
	protected:
	
		Renderer::Object::IModel *m_pModel;//モデルデータ	
		Scene::IModelActor		 *m_pActorModel[S_MAX];//モデルアクター	
		Dynamics::IRigidBody	 *m_pRigidBody;//剛体
		
	protected:
	
	
		Math::Vector3D m_vDirection;//キャラの向いている方向
		
		Math::Vector3D m_vOldPos;//位置のバックアップ用
		Math::Vector3D m_vSetFlagPos;//フラグ設置位置
		Math::Vector3D m_vArrowPos;//ターゲット矢印位置
		
		float m_fGravity;//重力
		
		float m_fWeight;//重み
		float m_fSpeed;//移動速度
		
		bool m_IsSetFlag;//フラグ設置判定フラグ
	
	public:
	
		CCharacter(){}; //コンストラクタ
		CCharacter( string name ); //コンストラクタ
		CCharacter( string name, Math::Vector3D vPos );//コンストラクタ
		
		~CCharacter(); //デストラクタ
	
		void Init();//初期化
		void Exec();//処理
		void Rendering( int index );//レンダリング
		virtual void MoveExec(){};
		
		virtual void Load( Renderer::IRender *pRender );//ファイル読み込み
		virtual void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//剛体モデルの生成
		void CreateCollision();//コリジョンデータの作成
		
		virtual void SetActorIndex( int index );//アクターインデックスのセット
		
		bool HitCheck( CCharacter *pChara );
		bool HitCheck( CDraw3DObject **ppChara );//当たり判定
		bool HitCheck( Selene::Collision::CLine3D &vRay );//当たり判定
		bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		
		float CheckDistance( CCharacter *pChara );//キャラ距離を測る
		
		virtual bool GroundCheck( CCharacter *pChara, int index );//地面チェック
		bool GroundCheck( CCharacter *pChara );//地面チェック
		virtual bool GroundCheck( Scene::IMapActor *pActor );//地面チェック
		bool GroundCheck2( Scene::IMapActor *pActor );//地面チェック
		
		void AddRef();//参照カウンタの増加
		
	/*Set系*/
	public:
	
		void SetFlag( bool flag );//フラグ設置判定フラグの設置
		void SetGravity( Float fGravity );//重力の設定	
		void SetOldPosition( Math::Vector3D vPos );//バックアップ座標の設定
		
		/*矢印の位置の設定*/
		void SetArrowPos( Math::Vector3D vPos )
		{
			m_vArrowPos = vPos;	
		}
		
	/*Get系*/
	public:
	
		/*モデルデータの取得*/
		Renderer::Object::IModel *GetModel() const
		{
			return m_pModel;
		}
		
		/*モデルアクターの取得*/
		Scene::IModelActor *GetModelActor( int index ) const
		{
			return m_pActorModel[index];
		}
		
		/*剛体の取得*/
		Dynamics::IRigidBody *GetRigidBody() const
		{
			return m_pRigidBody;
		}
		
		/*フラグ設置位置の取得*/
		Math::Vector3D GetSetFlagPosition()
		{
			return m_vSetFlagPos;
		}
		
		/*重力加速度の取得*/
		Float GetGravity()
		{
			return m_fGravity;									
		}
		
		/*移動速度の取得*/
		float GetSpeed()
		{
			return m_fSpeed;
		}
		
		/*フラグ設置判定フラグの取得*/
		bool GetSetFlag()
		{
			return m_IsSetFlag;
		}
		
		/*旧座標の取得*/
		Math::Vector3D GetOldPosition()
		{
			return m_vOldPos;
		}
		
		/*ターゲット矢印位置の取得*/
		Math::Vector3D GetArrowPosition()
		{
			return m_vArrowPos;
		}
		
		
		
		
};