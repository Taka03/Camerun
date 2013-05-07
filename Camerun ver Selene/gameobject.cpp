//*============================================================================
//gameobject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"
#include "selene.h"

#define MAP_DEBUG 2




//=============================================================================
//コンストラクタ
//=============================================================================
CGameObject::CGameObject()
{
	m_IsVisible = false;
	
	m_IsStop = false;
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CGameObject::~CGameObject()
{
	m_IsVisible = false;
	
	//list<ListData>::iterator i;
	
	//for(i = m_ObjectList.begin();i != m_ObjectList.end();i++)
	//{
	//	SAFE_DELETE(i->gameobj);
	//}
	
}


//=============================================================================
//オブジェクトの追加(名前あり)
//=============================================================================
//[input]
//	object:ゲームオブジェクト
//	name:データ名
//	autodelete:削除と同時にオブジェクトも削除するか(フラグ)
//=============================================================================
void CGameObject::AppendObject(CGameObject *object, string name,  bool autodelete)
{
	static int priority = 0;//優先順位

	if(object == NULL)
	{
		return;
	}
	
	//CGameObject *gameObj = FindObjectFromName(name);
	//
	//list<ListData>::iterator i;
	//
	//for(i = m_ObjectList.begin();i != m_ObjectList.end();i++)
	//{
	//	if(i->gameobj == gameObj)
	//	{
	//		return;
	//	}
	//}
	
	m_IsVisible = true;
	
	priority++;
	
	ListData ld;
	
	ld.priority = priority;
	
	ld.name = name;
	
	ld.gameobj = object;
	ld.autodelete = autodelete;
	
	/*初期化*/
	object->Init();
	
	/*表示フラグの設定*/
	object->SetVisibleFlag( autodelete );
	
	/*間に入れるところがなければ、最後に追加*/
	m_ObjectList.push_back(ld);
	

}

//=============================================================================
//オブジェクトの追加(名前あり)
//=============================================================================
//[input]
//	name:データ名
//	autodelete:削除と同時にオブジェクトも削除するか(フラグ)
//=============================================================================
void CGameObject::AppendObject(string name, bool autodelete )
{
	CGameObject *object;
	
	object = FindObjectFromName(name);
	
	if(object == NULL)
	{
		return;
	}
	
	
	
	m_IsVisible = true;
	
	ListData ld;
	
	ld.name = name;
	
	ld.gameobj = object;
	//AddRef
	ld.autodelete = autodelete;
	
	/*間に入れるところがなければ、最後に追加*/
	m_ObjectList.push_back(ld);
	
	ld.priority = (int)( m_ObjectList.size() );
	
	
}

//=============================================================================
//オブジェクトの削除
//=============================================================================
//[input]
//	object:対象のオブジェクト
//=============================================================================
void CGameObject::RemoveObject(CGameObject *object)
{
	m_IsVisible = false;
	
	list<ListData>::iterator i;
	
	for(i = m_ObjectList.begin();i != m_ObjectList.end();i++)
	{
		if(i->gameobj == object)
		{
			/*削除データをリストに追加*/
			//removelist.push_back(i);
			
			/*そのまま削除*/
			SAFE_DELETE( i->gameobj );
			
			m_ObjectList.erase(i);
			
			return;
		}
	}
}

//=============================================================================
//オブジェクト検索(名前から)
//=============================================================================
//[input]
//	name:オブジェクト名
//[return]
//	(*i).gameobj:名前の一致したオブジェクト
//	NULL:見つからなかった場合何も返さない
//=============================================================================
CGameObject *CGameObject::FindObjectFromName(string name)
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin(); i != m_ObjectList.end();i++ )
	{
		if(strcmp( i->name.c_str(), name.c_str() ) == 0)
		{
			return i->gameobj;
		}
	}
	
	//_ASSERT("オブジェクトが見つかりません");
	
	return NULL;
}

//=============================================================================
//オブジェクト検索(優先順位から)
//=============================================================================
//[input]
//	priority:優先順位
//[return]
//	(*i).gameobj:優先順位の一致したオブジェクト
//	NULL:見つからなかった場合何も返さない
//=============================================================================
CGameObject *CGameObject::FindObjectFromPriority(int priority)
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin(); i != m_ObjectList.end();i++ )
	{
		if( i->priority == priority)
		{
			return i->gameobj;
		}
	}
	
	return NULL;
	
}


//=============================================================================
//すべてのタスクの実行
//=============================================================================
void CGameObject::DoAllTasks()
{
	//list<ListData>::iterator i;
	
	//for( i = m_ObjectList.begin(); i != m_ObjectList.end();i++ )
	//{
			/*処理*/
			//(*i).gameobj->Exec();
	//}
	
	
	///*シーンの描画開始*/
	//if( SUCCEEDED( DXUTGetD3DDevice()->BeginScene() ) )
	//{

	//for(i = m_ObjectList.begin(); i != m_ObjectList.end();i++)
	//{
	//	(*i).gameobj->Exec();
	//	
	//}
		
		/*シーンの終了*/
	//	DXUTGetD3DDevice()->EndScene();
		
	//}
	
	

	
				
				

			
	
	
	//else
	//{
	//	for(i = m_ObjectList.begin(); i != m_ObjectList.end();i++)
	//	{
	//		
	//		/*描画*/
	//		if( i->gameobj->m_IsVisible )
	//		{
	//			if( SUCCEEDED(DXUTGetD3DDevice()->BeginScene() ) )
	//			{
	//				/*レンダリング*/
	//				(*i).gameobj->Rendering();
	//				
	//				/*シーンの終了*/
	//				DXUTGetD3DDevice()->EndScene();
	//			}
	//				
	//			
	//		}
	//		
	//		/*処理*/
	//		(*i).gameobj->Exec();
	//		
	//	}
	//		
	//}
	//
	//if(removelist.size() > 0)
	//{
	//	/*削除一覧にあるデータをまとめて削除*/
	//	list<list<ListData>::iterator>::iterator j;
	//	
	//	for(j = removelist.begin();j != removelist.end();j++)
	//	{
	//		if( (**j).autodelete == true)
	//		{
	//			delete (**j).gameobj;
	//		}
	//		
	//		m_ObjectList.erase(*j);
	//	}
	//	
	//	removelist.clear();
	//}
}

////=============================================================================
////任意オブジェクトのレンダリング
////=============================================================================
////[input]
////	name:取得するオブジェクトの名前
////=============================================================================
//void CGameObject::RenderingObj(string name)
//{
//	CGameObject *obj;
//	
//	obj = FindObjectFromName(name);
//	
//	if( obj == NULL )
//	{
//		return;
//	}
//	
//	if( obj->m_IsVisible )
//	{
//		obj->Rendering();
//	}
//}

//=============================================================================
//任意オブジェクトのレンダリング
//=============================================================================
//[input]
//	name:取得するオブジェクトの名前
//=============================================================================
void CGameObject::ExecObj(string name)
{
	CGameObject *obj;
	
	obj = FindObjectFromName(name);
	
	if( obj == NULL )
	{
		return;
	}
	
	if( !obj->m_IsStop )
	{
		obj->Exec();
	}
}

//=============================================================================
//表示フラグの設定
//=============================================================================
//[input]
//	IsVisible:表示フラグ
//=============================================================================
void CGameObject::SetVisibleFlag(bool IsVisible)
{
	m_IsVisible = IsVisible;
}


//=============================================================================
//表示フラグの設定
//=============================================================================
//[input]
//	name:取得オブジェクトの名前
//	IsVisible:表示フラグ
//=============================================================================
void CGameObject::SetVisibleFlag( string name, bool IsVisible)
{
	CGameObject *obj;
	
	obj = FindObjectFromName( name );
	
	if( obj == NULL )
	{
		return;
	}
	
	obj->m_IsVisible = IsVisible;
}

//=============================================================================
//静止フラグのセット
//=============================================================================
//[input]
//	IsStop:静止フラグ
//=============================================================================
void CGameObject::SetStopFlag( bool IsStop )
{
	m_IsStop = IsStop;
}

//=============================================================================
//表示フラグの取得
//=============================================================================
//[return]
//	表示フラグ	
//=============================================================================
bool CGameObject::GetVisibleFlag()
{
	return m_IsVisible;
}

//=============================================================================
//静止フラグの取得
//=============================================================================
//[return]
//	静止フラグ
//=============================================================================
bool CGameObject::GetStopFlag()
{
	return m_IsStop;
}







