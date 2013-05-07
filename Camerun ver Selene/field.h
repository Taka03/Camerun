//*============================================================================
//field.h
//*============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "C3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	フィールド用クラス
//=============================================================================
class CField :public CDraw3DObject
{
	private:
	
		Renderer::Object::IMapModel *m_pMapModel;//マップのモデルデータ
		Scene::IMapActor			*m_pActorMap[S_MAX];//マップアクター
		Renderer::Object::ILine3D   *m_pLine;//デバッグライン
		
	public:
	
		CField(){};//コンストラクタ
		CField( string name );//コンストラクタ
		~CField();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void Rendering(int index);//レンダリング
		
		virtual void Load( Renderer::IRender *pRender );//ファイル読み込み
		
		//virtual void SetActor( Math::Style *pStyle );//アクターのセット	
		virtual void SetActorIndex( int index );//アクターインデックスのセット
		
		void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//剛体モデルの生成
	public:
		
		void	CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		//void	CreateActor( int index, Scene::ICustomizedSceneManager *pSceneMgr );//アクターの生成
		
		
		/*衝突判定用ライン*/
		void SetCollisionLine( Renderer::Object::ILine3D *pLine )
		{
			m_pLine = pLine;
		}
	
	/*Get系*/
	public:
	
		/*マップモデルデータの取得*/
		Renderer::Object::IMapModel *GetMapModel() const
		{
			return m_pMapModel;
		}
		
		/*マップアクターの取得*/
		Scene::IMapActor *GetMapActor( int index ) const
		{
			return m_pActorMap[index];
		}

		
	
		
		
};