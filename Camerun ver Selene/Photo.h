//*============================================================================
//Photo.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//	08/04/01  �X�v���C�g�̌p���ɕύX
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�ʐ^�p�N���X
//=============================================================================
class CPhoto :public CSprite
{
	private:
	
		bool m_IsExist;//�ʐ^�Ƀ^�[�Q�b�g�����݂��邩
		float m_fTargetDistance;//�^�[�Q�b�g�̑傫��
		Math::Vector3D m_vTargetPos;//�^�[�Q�b�g�̈ʒu
		
	public:
	
		CPhoto(void);//�R���X�g���N�^
		CPhoto( string name, Math::Vector2D vPos );//�R���X�g���N�^
		
	/*Set�n*/
	public:
	
		void SetTargetDistance( float fDistance );//�^�[�Q�b�g�̑傫���̃Z�b�g
		void SetExistFlag( bool flag );//�^�[�Q�b�g���݃t���O�̐ݒ�
		void SetTargetPos( Math::Vector3D vPos );//�^�[�Q�b�g�̈ʒu�̐ݒ�
		void SavePhoto();//�ʐ^�̕ۑ�

	/*Get�n*/
	public:
	
		//�^�[�Q�b�g�̑傫���̎擾
		float GetTargetDistance()
		{
			return m_fTargetDistance;
		}
		
		//�^�[�Q�b�g�̈ʒu�̎擾		
		Math::Vector3D GetTargetPosition()
		{
			return m_vTargetPos;
		}
		
		/*�^�[�Q�b�g���݃t���O�̎擾*/
		bool GetExistFlag( )
		{
			return m_IsExist;
		}
		
};
