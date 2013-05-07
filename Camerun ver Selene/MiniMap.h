//*============================================================================
//MiniMap.h
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
#include "Sprite.h"
#include "character.h"


//=============================================================================
//class
//=============================================================================
//[Desc]
//	�~�j�}�b�v�`��p�I�u�W�F�N�g
//=============================================================================
class CMiniMap :	public CSprite
{
	private:
	
		Math::Point2DF m_Scroll;//�X�N���[�����W
		Math::Point2DF m_MapScroll;//�}�b�v�X�N���[��
		Math::Point2DF m_DrawSize;//�`��T�C�Y
		
		Renderer::IRender *m_pRender;//�����_���[�p�f�o�C�X
	
	public:
	
		CMiniMap(){};
		CMiniMap( string name );//�R���X�g���N�^
		CMiniMap( string name, Math::Vector2D vPos );//�R���X�g���N�^
		~CMiniMap();//�f�X�g���N�^

		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		void Move( CCharacter *pChara );//�X�N���[��
		
		void ScrollAdjust();//�X�N���[���␳
		
		void SetMiniCharaPos( CCharacter *pChara, CSprite *pSpr, bool IsPlayer );//�L�����N�^�[�̃~�j�}�b�v�ʒu�̐ݒ�
		
	/*Set�n*/
	public:
	
		void SetRenderer( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
		}
	
	/*Get�n*/
	public:
	
		/*�X�N���[�����W�̎擾*/
		Math::Point2DF GetScroll()
		{
			return m_Scroll;
		}
		
		/*�`��T�C�Y�̎擾*/
		Math::Point2DF GetDrawSize()
		{
			return m_DrawSize;
		}

		
		
};
