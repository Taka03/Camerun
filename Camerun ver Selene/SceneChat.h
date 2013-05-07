//*============================================================================
//SceneChat.h
//*============================================================================
//[history]
//	08/05/23　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//class
//=============================================================================
#include "scene.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	会話画面クラス
//=============================================================================
class CSceneChat : public CScene
{
	private:
	
	public:
	
		CSceneChat(void);//コンストラクタ
		~CSceneChat(void);//デストラクタ
		
		void Exec( CScene *pScene );//処理
	
};
