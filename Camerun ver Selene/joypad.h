//*============================================================================
//joypad.h
//*============================================================================
//[history]
//	08/03/06�@�C��
//[author]
//	Taka
//============================================================================
//��d�C���N���[�h�h�~
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Selene.h"
#include "lua.hpp"

//=============================================================================
//using
//=============================================================================
using namespace Selene;



//=============================================================================
//class
//=============================================================================
//[desc]
//	�W���C�p�b�h�p�N���X
//=============================================================================
class CJoyPad 
{
	private:
	
		Math::Point2DI deb;
	
	private:
	
		static Peripheral::IInputController *m_pController;//�R���g���[���[�p�f�o�C�X
		Peripheral::IJoystick		 *m_pJoystick;//�W���C�X�e�B�b�N�p�f�o�C�X
		
	public:
	
		CJoyPad();//�R���X�g���N�^
		virtual ~CJoyPad();//�f�X�g���N�^
		
		
	public:
	
		void CreateDevice( ICore *pCore );//�f�o�C�X�̍쐬
		void Initialize();	//������
		void Update();//�X�V
		
		void AddRef();//�Q�ƃJ�E���^����
		
		
		
	/*Get�n*/
	public:
	
		/*�R���g���[���[�p�f�o�C�X�̎擾*/
		Peripheral::IInputController *GetController() const
		{
			return m_pController;
		}
		
		//�W���C�X�e�B�b�N�p�f�o�C�X�̎擾
		Peripheral::IJoystick *GetJoyStick() const
		{
			return m_pJoystick;
		}

	
	
};