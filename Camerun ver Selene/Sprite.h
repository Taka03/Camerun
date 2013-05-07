//*============================================================================
//Sprite.h
//*============================================================================
//[history]
//	08/03/19�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "draw2dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CSprite :	public Draw2DObject
{
	private:
	
		bool m_IsMissionVisible;//�~�b�V�����ŕ\�������邩�ǂ���
	
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//�e�N�X�`���p�n���h��
		Selene::Renderer::Object::ISprite2D *m_pSpr;//�X�v���C�g�p�n���h��
	
	protected:
	
		Math::Point2DI m_Divnum;//������
		Math::Point2DI m_Anim;//�A�j��ID
	
		Sint32 m_Width;//��
		Sint32 m_Height;//����
		
	public:
	
		CSprite(){};
		CSprite( string name );//�R���X�g���N�^
		CSprite( string name, Math::Vector2D vPos );//�R���X�g���N�^
		~CSprite(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender );//�t�@�C���ǂݍ���

		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		void DrawMultiGraph( Math::Point2DF pos[], Math::Point2DF AnimID[],  int DrawNum );//�����̕`��
		void DrawGrayScale( Renderer::IRender *pRender );//�O���[�X�P�[���`��
		void DrawAnimation( int animNum, int animTime );//�A�j���[�V�����̕`��
		void Move();//�ړ�
		
	/*Set�n*/
	public:
	
		//�������̐ݒ�	
		void SetDivnum( Math::Point2DI divnum )
		{
			m_Divnum = divnum;
		}
		
		//�A�j���[�V����ID�̐ݒ�
		void SetAnimID( Math::Point2DI anim )
		{
			m_Anim = anim;
		}
		
		/*�摜�T�C�Y�̐ݒ�*/
		void SetGraphSize( Math::Point2DI Size )
		{
			m_Width = Size.x;
			m_Height = Size.y;
		}
		
		/*�~�b�V�����ł̕\���t���O��ݒ�*/
		void SetMissionVisible( bool flag )
		{
			m_IsMissionVisible = flag;	
		}
		
	/*Get�n*/
	public:

		//�e�N�X�`���p�n���h���̎擾
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//�X�v���C�g�p�n���h���̎擾
		Selene::Renderer::Object::ISprite2D *GetSprite() const
		{
			return m_pSpr;
		}
		
		/*�摜���̎擾*/
		Sint32 GetWidth() const
		{
			return m_Width;
		}
		
		/*�摜�����̎擾*/
		Sint32 GetHeight() const
		{
			return m_Height;
		}
		
		/*�~�b�V�����ł̕\������t���O�̐ݒ�*/
		bool GetMissionVisible()
		{
			return m_IsMissionVisible;
		}
		
		
};
