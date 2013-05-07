//*============================================================================
//FlagObject.h
//*============================================================================
//[history]
//	08/05/22�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t���O�I�u�W�F�N�g�p�N���X
//=============================================================================
class CFlagObject :	public CCharacter
{
	private:
	
		Math::Matrix m_matBone;//�v���C���[�̃{�[��
	
	public:
	
		CFlagObject( string name );//�R���X�g���N�^
	
		void Init();//������
		void Exec();//����
		
	public:
	
		/*�{�[���}�g���b�N�X�̃Z�b�g*/
		void SetBoneMatrix( Math::Matrix matBone )
		{
			m_matBone = matBone;
		}
	
		
		
};