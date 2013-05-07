//*============================================================================
//GameSceneManager.h
//*============================================================================
//[history]
//	08/03/05�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"
#include "player.h"
#include "Scene.h"
#include "Game.h"
#include "Fiber.h"


//=============================================================================
//struct
//=============================================================================
struct SceneList
{
	eSceneType m_eSceneType;//�V�[���^�C�v
	CScene *m_pScene;//�V�[��
};

//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[���Ǘ��p�N���X
//=============================================================================
class CGameSceneManager
{
	private:
	
		list<SceneList> m_SceneList;//�V�[�����X�g
		CScene *m_pScene;//�V�[��
		Fiber::IFiberController *m_pFiberCtrl;//�t�@�C�o�[�R���g���[��
		
	
	private:
	
	public:
	
		CGameSceneManager( CScene *pScene );//�R���X�g���N�^
		~CGameSceneManager();//�f�X�g���N�^
		
		void Exec();//����
		
		void AddScene( eSceneType Type, CScene *pScene );//�V�[���̒ǉ�
		void RemoveScene( CScene *pScene );//�V�[���̍폜
		
		CScene *FindScene( eSceneType Type );//�V�[���̎Q��
		
	public:
	
		//void GetGameScene( CScene *pScene );//�Q�[���V�[���̎擾
		
};