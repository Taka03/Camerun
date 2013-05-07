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
//�R���X�g���N�^
//=============================================================================
CGameObject::CGameObject()
{
	m_IsVisible = false;
	
	m_IsStop = false;
	
}

//=============================================================================
//�f�X�g���N�^
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
//�I�u�W�F�N�g�̒ǉ�(���O����)
//=============================================================================
//[input]
//	object:�Q�[���I�u�W�F�N�g
//	name:�f�[�^��
//	autodelete:�폜�Ɠ����ɃI�u�W�F�N�g���폜���邩(�t���O)
//=============================================================================
void CGameObject::AppendObject(CGameObject *object, string name,  bool autodelete)
{
	static int priority = 0;//�D�揇��

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
	
	/*������*/
	object->Init();
	
	/*�\���t���O�̐ݒ�*/
	object->SetVisibleFlag( autodelete );
	
	/*�Ԃɓ����Ƃ��낪�Ȃ���΁A�Ō�ɒǉ�*/
	m_ObjectList.push_back(ld);
	

}

//=============================================================================
//�I�u�W�F�N�g�̒ǉ�(���O����)
//=============================================================================
//[input]
//	name:�f�[�^��
//	autodelete:�폜�Ɠ����ɃI�u�W�F�N�g���폜���邩(�t���O)
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
	
	/*�Ԃɓ����Ƃ��낪�Ȃ���΁A�Ō�ɒǉ�*/
	m_ObjectList.push_back(ld);
	
	ld.priority = (int)( m_ObjectList.size() );
	
	
}

//=============================================================================
//�I�u�W�F�N�g�̍폜
//=============================================================================
//[input]
//	object:�Ώۂ̃I�u�W�F�N�g
//=============================================================================
void CGameObject::RemoveObject(CGameObject *object)
{
	m_IsVisible = false;
	
	list<ListData>::iterator i;
	
	for(i = m_ObjectList.begin();i != m_ObjectList.end();i++)
	{
		if(i->gameobj == object)
		{
			/*�폜�f�[�^�����X�g�ɒǉ�*/
			//removelist.push_back(i);
			
			/*���̂܂܍폜*/
			SAFE_DELETE( i->gameobj );
			
			m_ObjectList.erase(i);
			
			return;
		}
	}
}

//=============================================================================
//�I�u�W�F�N�g����(���O����)
//=============================================================================
//[input]
//	name:�I�u�W�F�N�g��
//[return]
//	(*i).gameobj:���O�̈�v�����I�u�W�F�N�g
//	NULL:������Ȃ������ꍇ�����Ԃ��Ȃ�
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
	
	//_ASSERT("�I�u�W�F�N�g��������܂���");
	
	return NULL;
}

//=============================================================================
//�I�u�W�F�N�g����(�D�揇�ʂ���)
//=============================================================================
//[input]
//	priority:�D�揇��
//[return]
//	(*i).gameobj:�D�揇�ʂ̈�v�����I�u�W�F�N�g
//	NULL:������Ȃ������ꍇ�����Ԃ��Ȃ�
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
//���ׂẴ^�X�N�̎��s
//=============================================================================
void CGameObject::DoAllTasks()
{
	//list<ListData>::iterator i;
	
	//for( i = m_ObjectList.begin(); i != m_ObjectList.end();i++ )
	//{
			/*����*/
			//(*i).gameobj->Exec();
	//}
	
	
	///*�V�[���̕`��J�n*/
	//if( SUCCEEDED( DXUTGetD3DDevice()->BeginScene() ) )
	//{

	//for(i = m_ObjectList.begin(); i != m_ObjectList.end();i++)
	//{
	//	(*i).gameobj->Exec();
	//	
	//}
		
		/*�V�[���̏I��*/
	//	DXUTGetD3DDevice()->EndScene();
		
	//}
	
	

	
				
				

			
	
	
	//else
	//{
	//	for(i = m_ObjectList.begin(); i != m_ObjectList.end();i++)
	//	{
	//		
	//		/*�`��*/
	//		if( i->gameobj->m_IsVisible )
	//		{
	//			if( SUCCEEDED(DXUTGetD3DDevice()->BeginScene() ) )
	//			{
	//				/*�����_�����O*/
	//				(*i).gameobj->Rendering();
	//				
	//				/*�V�[���̏I��*/
	//				DXUTGetD3DDevice()->EndScene();
	//			}
	//				
	//			
	//		}
	//		
	//		/*����*/
	//		(*i).gameobj->Exec();
	//		
	//	}
	//		
	//}
	//
	//if(removelist.size() > 0)
	//{
	//	/*�폜�ꗗ�ɂ���f�[�^���܂Ƃ߂č폜*/
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
////�C�ӃI�u�W�F�N�g�̃����_�����O
////=============================================================================
////[input]
////	name:�擾����I�u�W�F�N�g�̖��O
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
//�C�ӃI�u�W�F�N�g�̃����_�����O
//=============================================================================
//[input]
//	name:�擾����I�u�W�F�N�g�̖��O
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
//�\���t���O�̐ݒ�
//=============================================================================
//[input]
//	IsVisible:�\���t���O
//=============================================================================
void CGameObject::SetVisibleFlag(bool IsVisible)
{
	m_IsVisible = IsVisible;
}


//=============================================================================
//�\���t���O�̐ݒ�
//=============================================================================
//[input]
//	name:�擾�I�u�W�F�N�g�̖��O
//	IsVisible:�\���t���O
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
//�Î~�t���O�̃Z�b�g
//=============================================================================
//[input]
//	IsStop:�Î~�t���O
//=============================================================================
void CGameObject::SetStopFlag( bool IsStop )
{
	m_IsStop = IsStop;
}

//=============================================================================
//�\���t���O�̎擾
//=============================================================================
//[return]
//	�\���t���O	
//=============================================================================
bool CGameObject::GetVisibleFlag()
{
	return m_IsVisible;
}

//=============================================================================
//�Î~�t���O�̎擾
//=============================================================================
//[return]
//	�Î~�t���O
//=============================================================================
bool CGameObject::GetStopFlag()
{
	return m_IsStop;
}







