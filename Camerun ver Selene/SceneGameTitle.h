//*============================================================================
//SceneGameTitle.h
//*============================================================================
//[history]
//	08/03/22　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "scene.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	タイトルシーン
//=============================================================================
class CSceneGameTitle :	public CScene
{
	public:
	
		CSceneGameTitle();//コンストラクタ
		~CSceneGameTitle(void);//デストラクタ
		
		void Exec( CScene *pScene );//処理
};
