//*============================================================================
//gameobject.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//============================================================================
//二重インクルード防止
#pragma once

//=============================================================================
//include
//=============================================================================
#include "selene.h"
#include "lua.hpp"

#include <list>

//=============================================================================
//using
//=============================================================================
using namespace Selene;
using namespace std;

//=============================================================================
//variable
//=============================================================================
class CGameObject;

//=============================================================================
//struct
//=============================================================================
struct ListData
{
	int priority;//順番
	string name;//管理名称
	CGameObject* gameobj;//オブジェクトのポインタ
	bool autodelete;//リスト削除と同時にオブジェクトも削除
};

//=============================================================================
//template
//=============================================================================
template< typename T, T var>
T Get( )
{
	return var;
}

//=============================================================================
//define
//=============================================================================
#define BUTTON_R2 BUTTON_01
#define BUTTON_R1 BUTTON_02
#define BUTTON_TRIANGLE BUTTON_03
#define BUTTON_SQUARE BUTTON_04
#define BUTTON_CIRCLE BUTTON_06
#define BUTTON_CROSS BUTTON_09
#define BUTTON_START BUTTON_05
#define BUTTON_L2 BUTTON_08
#define BUTTON_L1 BUTTON_07



//=============================================================================
//class
//=============================================================================
//[desc]
//	ゲームオブジェクト用クラス
//=============================================================================
class CGameObject 
{
	protected:
	
		list<ListData> m_ObjectList;//格納リスト
		list<list<ListData>::iterator> m_RemoveList;//削除リスト
		
	protected:
	
		bool m_IsStop;//静止判定フラグ
		bool m_IsVisible;//表示判定フラグ
		
	public:
	
		CGameObject();//コンストラクタ
		virtual ~CGameObject();//デストラクタ
		
		virtual void Init(){};//初期化
		virtual void Exec(){};//処理
		
		void DoAllTasks();//タスクの実行
		//void RenderingObj(string name);//オブジェクトのレンダリング
		void ExecObj(string name);//オブジェクトの処理
		
		void AppendObject(CGameObject *object, string name, bool autodelete);//オブジェクトの追加
		void AppendObject( string name, bool autodelete );//オブジェクトの追加
		void RemoveObject(CGameObject *object);//オブジェクトの削除
		
		CGameObject *FindObjectFromName(string name);//オブジェクトの検索
		CGameObject *FindObjectFromPriority(int priority);//オブジェクトの検索
		
	/*Set系*/
	public:
	
		void SetVisibleFlag( bool IsVisible );
		void SetVisibleFlag( string name, bool IsVisible );
		void SetStopFlag( bool IsStop );
	
	/*Get系*/
	public:
	
		bool GetVisibleFlag();//表示フラグの取得
		bool GetStopFlag();//静止フラグの取得
		
		//格納リストの取得		
		list<ListData> GetObjectList() const
		{
			return m_ObjectList;
		}

		
};
