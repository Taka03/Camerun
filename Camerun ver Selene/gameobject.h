//*============================================================================
//gameobject.h
//*============================================================================
//[history]
//	08/03/03�@�C���J�n
//[author]
//	Taka
//============================================================================
//��d�C���N���[�h�h�~
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
	int priority;//����
	string name;//�Ǘ�����
	CGameObject* gameobj;//�I�u�W�F�N�g�̃|�C���^
	bool autodelete;//���X�g�폜�Ɠ����ɃI�u�W�F�N�g���폜
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
//	�Q�[���I�u�W�F�N�g�p�N���X
//=============================================================================
class CGameObject 
{
	protected:
	
		list<ListData> m_ObjectList;//�i�[���X�g
		list<list<ListData>::iterator> m_RemoveList;//�폜���X�g
		
	protected:
	
		bool m_IsStop;//�Î~����t���O
		bool m_IsVisible;//�\������t���O
		
	public:
	
		CGameObject();//�R���X�g���N�^
		virtual ~CGameObject();//�f�X�g���N�^
		
		virtual void Init(){};//������
		virtual void Exec(){};//����
		
		void DoAllTasks();//�^�X�N�̎��s
		//void RenderingObj(string name);//�I�u�W�F�N�g�̃����_�����O
		void ExecObj(string name);//�I�u�W�F�N�g�̏���
		
		void AppendObject(CGameObject *object, string name, bool autodelete);//�I�u�W�F�N�g�̒ǉ�
		void AppendObject( string name, bool autodelete );//�I�u�W�F�N�g�̒ǉ�
		void RemoveObject(CGameObject *object);//�I�u�W�F�N�g�̍폜
		
		CGameObject *FindObjectFromName(string name);//�I�u�W�F�N�g�̌���
		CGameObject *FindObjectFromPriority(int priority);//�I�u�W�F�N�g�̌���
		
	/*Set�n*/
	public:
	
		void SetVisibleFlag( bool IsVisible );
		void SetVisibleFlag( string name, bool IsVisible );
		void SetStopFlag( bool IsStop );
	
	/*Get�n*/
	public:
	
		bool GetVisibleFlag();//�\���t���O�̎擾
		bool GetStopFlag();//�Î~�t���O�̎擾
		
		//�i�[���X�g�̎擾		
		list<ListData> GetObjectList() const
		{
			return m_ObjectList;
		}

		
};
