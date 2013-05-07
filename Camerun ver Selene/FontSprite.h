//*============================================================================
//FontSprite.h
//*============================================================================
//[history]
//	08/03/16 �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "draw2dobject.h"
#include <vector>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t�H���g�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CFontSprite :	public Draw2DObject
{
	private:
		
		Renderer::Object::IFontSprite2D *m_pFontSpr;//�t�H���g�X�v���C�g�p�n���h��
		string m_Str;//�\�����镶��
		Math::Vector2D m_vOldPos;//�����W
		vector<string> m_vecText;//��b�e�L�X�g
		
		CColor m_FontColor;//�t�H���g�F
		
		Uint32 m_StrCount;//�����J�E���^
		Uint32 m_RefCount;//�����̎Q�ƃJ�E���^
		
		bool m_IsTextEnd;//�e�L�X�g�I���t���O
		
	
	public:
	
		CFontSprite( string name );//�R���X�g���N�^
		CFontSprite( string name, Math::Vector2D vPos );//�R���X�g���N�^
		
		virtual ~CFontSprite(void);//�f�X�g���N�^
		
		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		bool DrawNovelStyle( ICore *pCore, Selene::Peripheral::IInputController *pCtrl );//�ꕶ�����\��
		void DrawMultiLine( );//����������̕`��
		void DrawMultiLine( Math::Point2DF vPos[] );//����������̕`��
		
		void Load( Renderer::IRender *pRender );//�ǂݍ���
		
	public:
	
		void SetDrawString( string str );//�`�悷�镶���̐ݒ�
		
		/*����������̕`��ݒ�*/
		void SetVecTextChat( vector<string> vecStr )
		{
			m_vecText = vecStr;
		}
		
		/*�����Q�ƃJ�E���^�̑���*/
		void SetRefCount( Uint32 count) 
		{
			m_RefCount = count;
		}
		
		/*�e�L�X�g�I���t���O�̐ݒ�*/
		void SetTextEndFlag( bool flag )
		{
			m_IsTextEnd = flag;
		}
		
		/*�����J�E���^�̐ݒ�*/
		void SetStrCount( Uint32 count )
		{
			m_StrCount = count;
		}
		
		/*�t�H���g�F�̐ݒ�*/
		void SetFontColor( CColor color )
		{
			m_FontColor = color;
		}
		
	public:
	
		//�t�H���g�X�v���C�g�p�n���h���̎擾
		Renderer::Object::IFontSprite2D *GetFontSprite() const
		{
			return m_pFontSpr;
		}
		
		/*�\�����镶���̎擾*/
		string GetDrawString() 
		{
			return m_Str;
		}
		
		
		/*�e�L�X�g�I���t���O�̎擾*/
		bool GetTextEndFlag() const
		{
			return m_IsTextEnd;
		}
		
		/*�����J�E���^�̎擾*/
		Uint32 GetStrCount()
		{
			return m_StrCount;
		}
	
		
	
};
