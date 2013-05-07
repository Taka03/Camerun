//*============================================================================
//C3DObject.h
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
#include "drawobject.h"

//=============================================================================
//enum
//=============================================================================
//スクリーンタイプ
enum eScreenType
{
	S_MAIN,//メイン画面
	S_SUB,//サブ画面
	S_MAX,
};


//キャラクタータイプ
enum eDraw3DType
{
	OBJ_PLAYER,//プレイヤー
	OBJ_ENEMY,//敵
	OBJ_MAP,//マップ
	OBJ_OTHER,//その他
	
};


//=============================================================================
//class
//=============================================================================
//[desc]
//	3Dオブジェクト描画用クラス
//=============================================================================
class CDraw3DObject :public CDrawObject
{
	private:
	
	protected:
	
		int m_ActorIndex;//アクターインデックス
		Dynamics::IRigidModel *m_pRigidModel;//剛体用モデル
		eDraw3DType m_eType;//オブジェクトタイプ
		Selene::Renderer::Shader::IShader *m_pShader;//シェーダー
		
	public:
	
		CDraw3DObject(void){};//コンストラクタ
		CDraw3DObject( string name );//コンストラクタ
		virtual ~CDraw3DObject(void);//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		virtual void MoveExec();//移動処理
		void Rendering(int index);//レンダリング
		
		virtual void Load( Renderer::IRender *pRender );//ファイル読み込み
		void LoadShader( Renderer::IRender *pRender, string name );//シェーダーの読み込み
		
		virtual void CreateActor( int index,  Scene::ISceneManager *pSceneMgr );//アクターの生成
		
		virtual void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//剛体モデルの生成
		virtual void CreateCollision();//コリジョンデータの作成
		
		virtual bool HitCheck( CDraw3DObject **ppChara );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj );
		//virtual bool HitCheck( Selene::Collision::CBox &Box, CDraw3DObject **ppHitObj)
		
		virtual void FlashedState( );//フラッシュを浴びた状態の処理
	//	virtual void RecallFlag( Peripheral::IInputController *m_pCtrl );
		
		//virtual void CreateActor( int index,  Scene::ICustomizedSceneManager *pSceneMgr );//アクターの生成
		
		//virtual void SetActor( Math::Style *pStyle );//アクターのセット
		
	/*Set系*/
	public:
	
		virtual void SetActorIndex( int index );//アクターインデックスのセット
	
	
	/*Get系*/
	public:
	
		/*アクターインデックスの取得*/
		int GetActorIndex()
		{
			return m_ActorIndex;
		}
		
		Dynamics::IRigidModel *GetRigidModel() const
		{
			return m_pRigidModel;
		}
		
		//オブジェクトタイプの取得	
		eDraw3DType GetObjectType()
		{
			return m_eType;
		}
		
		

		
		
};
