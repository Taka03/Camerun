//*============================================================================
//SceneMissionSelect.h
//*============================================================================
//[history]
//	08/05/01�@�쐬
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
//	�~�b�V�����Z���N�g��ʃN���X
//=============================================================================
class CSceneMissionSelect : public CScene
{
	private:
	
	public:
	
		CSceneMissionSelect(void);//�R���X�g���N�^
		~CSceneMissionSelect(void);//�f�X�g���N�^
		
		void Exec( CScene *pScene );//����
	
};