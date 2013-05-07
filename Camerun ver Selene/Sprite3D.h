//*============================================================================
//Sprite3D.h
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
#include "c3dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CSprite3D :	public CDraw3DObject
{
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//�e�N�X�`���p�n���h��
		Selene::Renderer::Object::ISprite3D *m_pSpr;//�X�v���C�g�p�n���h��
		Selene::Scene::ISpriteActor *m_pActorSprite[S_MAX];//�X�v���C�g�A�N�^�[
	
	protected:
	
		Math::Matrix m_matWorld;//���[�J���s��
		
		Math::Point2DI m_Divnum;//������
		Math::Point2DI m_Anim;//�A�j��ID
	
		Sint32 m_Width;//��
		Sint32 m_Height;//����
	
	public:
	
		CSprite3D(){};
		CSprite3D( string name );//�R���X�g���N�^
		CSprite3D( string name, Math::Vector3D vPos );//�R���X�g���N�^
		~CSprite3D(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender );//�t�@�C���ǂݍ���
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���

		void Init(){};//������
		void Exec();//����
		void Rendering( int index );//�����_�����O
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
	/*Set�n*/
	public:
	
		/*���[�J���s��̐ݒ�*/
		void SetMatWorld( Math::Matrix &mat )
		{
			m_matWorld = mat;
		}
		
		/*�������̐ݒ�*/
		void SetDivnum( Math::Point2DI Divnum )
		{
			m_Divnum = Divnum;
		}
		
		/*�A�j���[�V����ID�̐ݒ�*/
		void SetAnimID( Math::Point2DI animID )
		{
			m_Anim = animID;
		}
		
	/*Get�n*/
	public:

		//�e�N�X�`���p�n���h���̎擾
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//�X�v���C�g�p�n���h���̎擾
		Selene::Renderer::Object::ISprite3D *GetSprite() const
		{
			return m_pSpr;
		}
		
};
