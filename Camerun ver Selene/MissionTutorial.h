//*============================================================================
//MissionTutorial.h
//*============================================================================
//[history]
//	08/04/27�@�쐬
//[author]
//	Taka
//*===========================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "mission.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�`���[�g���A���~�b�V����
//============================================================================
class CMissionTutorial : public CMission
{
	public:
	
		CMissionTutorial(void){};//�R���X�g���N�^
		CMissionTutorial( CDraw3DObject *pTarget );//�R���X�g���N�^
		~CMissionTutorial(void);//�f�X�g���N�^
};