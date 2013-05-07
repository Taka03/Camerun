//*============================================================================
//ScenePhoto.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
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
//	�Q�[���V�[��(�ʐ^)�N���X
//=============================================================================
class CScenePhoto :	public CScene
{
	private:
	
		CPhoto *m_pPhoto;//�ʐ^�p�I�u�W�F�N�g
	
	public:
	
		CScenePhoto();//�R���X�g���N�^
		virtual ~CScenePhoto(void);//�f�X�g���N�^
		
	public:
		
		bool Init( CScene *pScene );//������
		void Exec( CScene *pScene );//����
		
	public:
	
		//�\������ʐ^�̃Z�b�g	
		void SetPhoto( CPhoto *pPhoto )
		{
			m_pPhoto = pPhoto;
		}
		
};