//*============================================================================
//CamObject.h
//*============================================================================
//[history]
//	08/03/14�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "camera.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�J�����I�u�W�F�N�g�p�N���X
//=============================================================================
class CCamObject :	public CCharacter
{
	private:
	
	public:
	
		CCamObject( string name );//�R���X�g���N�^
	
		void Init();//������
		void Exec();//����
		
	public:
	
		void Move( Selene::Peripheral::IInputController *pCtrl );//�ړ�
		void Move( Selene::Peripheral::IJoystick *pJoy, CCamera *pCam );//�ړ�
		void Move( Selene::Peripheral::IJoystick *pJoy );//�ړ�
		void MoveExec( );
		void MoveAdjust( );//�ړ��␳
		
		
};
