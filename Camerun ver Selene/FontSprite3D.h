//*============================================================================
//FontSprite3D.h
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
#include "c3dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t�H���g�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CFontSprite3D :	public CDraw3DObject
{
	private:
		
		Renderer::Object::IFontSprite3D *m_pFontSpr;//�t�H���g�X�v���C�g�p�n���h��
		Scene::ISpriteActor *m_pActorSprite[S_MAX];//�X�v���C�g�A�N�^�[
		string m_Str;//�\�����镶��
	
	public:
	
		CFontSprite3D( string name );//�R���X�g���N�^
		CFontSprite3D( string name, Math::Vector3D vPos );//�R���X�g���N�^
		
		virtual ~CFontSprite3D(void);//�f�X�g���N�^
		
		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		void Load( Renderer::IRender *pRender );//�ǂݍ���
		
	public:
	
		void SetDrawString( string str );//�`�悷�镶���̐ݒ�
		
	public:
	
		//�t�H���g�X�v���C�g�p�n���h���̎擾
		Renderer::Object::IFontSprite3D *GetFontSprite() const
		{
			return m_pFontSpr;
		}
		
	
};
