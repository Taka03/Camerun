//*============================================================================
//DebugLine.h
//*============================================================================
//[history]
//	08/4/04　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "C3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	デバッグライン用クラス
//=============================================================================
class CDebugLine :	public CDraw3DObject
{
	private:
	
		Renderer::Object::ILine3D *m_pLine;//ライン
		Scene::IPrimitiveActor *m_pActorLine;//ライン用アクター
	
	public:
	
		CDebugLine(void);//コンストラクタ
		virtual ~CDebugLine(void);//デストラクタ
		
		void CreateLine( Renderer::IRender *pRender );//ラインの生成
		void CreateActor( Scene::ISceneManager *pSceneMgr );//アクターの生成
		
		void AddLine( Renderer::SLineVertex3D *pLine, int LineNum );//ラインの追加
		void AddBox( Collision::CBox &Box, CColor Color );//ボックスの追加
		void Rendering();//レンダリング
		
	/*Get系*/
	public:
	
		//ラインの取得
		Renderer::Object::ILine3D *GetLine() const
		{
			return m_pLine;
		}
		
		//ライン用アクターの取得
		Scene::IPrimitiveActor *GetLineActor() const
		{
			return m_pActorLine;
		}
		
		
		
		
		
	
		
};
