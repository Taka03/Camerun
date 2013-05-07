//*============================================================================
//Menu.h
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
#include "FontSprite.h"
#include "Sprite.h"

//=============================================================================
//enum
//=============================================================================
enum eSelectType
{
	SELECT_YES,
	SELECT_NO,
	SELECT_NONE,
};


//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	���j���[�p
//=============================================================================
class CMenu : public  CGameObject
{
	private:
	
		CFontSprite *m_pFontSpr;//�t�H���g�X�v���C�g
		CSprite *m_pSpr;//�X�v���C�g
		
		string m_CaptionName;//�L���v�V������
		Renderer::IRender *m_pRender;//�����_���[�p�f�o�C�X
	
	private:
	
		bool m_IsPopUp;//���j���[���|�b�v�A�b�v���Ă��邩
		bool m_IsYesNoOrder;//�͂��E�������̏��Ԃ��ǂ���
		Sint32 m_Cursor;//�J�[�\��
		
	public:
	
		CMenu( CFontSprite *pFontSpr, CSprite *pSpr );//�R���X�g���N�^
		~CMenu();//�f�X�g���N�^
		
		void Init();//������
		void Rendering();//�����_�����O
		void Exec();//����
		
		eSelectType SelectYesNo( Selene::Peripheral::IInputController *pCtrl );//�I�����̑I��
		
	public:
	
		//�X�v���C�g�̐ݒ�		
		void SetSprite( CSprite *pSpr )
		{
			m_pSpr = pSpr;
		}
		
		//�t�H���g�X�v���C�g�̐ݒ�		
		void SetFontSprite( CFontSprite *pFontSpr )
		{
			m_pFontSpr = pFontSpr;
		}
		
		/*���j���[�|�b�v�A�b�v�t���O�̐ݒ�*/
		void SetPopUp( bool flag )
		{	
			m_IsPopUp = flag;
		}
		
		void SetYesNoOrderFlag( bool flag )
		{
			m_IsYesNoOrder = flag;
		}
		
		/*�L���v�V�������̐ݒ�*/
		void SetCaptionName( string name )
		{
			m_CaptionName = name;
		}
		
		/*�����_���[�p�f�o�C�X�̐ݒ�*/
		void SetRenderer( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
			pRender->AddRef();
		}
		
	public:
	
		/*���j���[�|�b�v�A�b�v�t���O�̎擾*/
		bool GetPopUpFlag(  )
		{	
			return m_IsPopUp;
		}
		
		/*�J�[�\���ԍ��̎擾*/
		Sint32 GetCursorNo()
		{
			return m_Cursor;
		}
	
		
};