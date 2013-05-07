//*============================================================================
//DrawObject.h
//*============================================================================
//[history]
//	08/03/03 �C���J�n
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�`��p�I�u�W�F�N�g
//=============================================================================
class CDrawObject :	public CGameObject
{
	protected:
	
		Math::Vector3D m_vPos; //���W
		Math::Vector3D m_vRot;//�p�x
		Math::Vector3D m_vScale;//�g�k
		
		string m_DataName;//�f�[�^��
		
	public:
	
		CDrawObject(void){};//�R���X�g���N�^
		CDrawObject( string name );//�R���X�g���N�^
		virtual ~CDrawObject(void){};//�f�X�g���N�^
		
		virtual void Init(){};//������
		virtual void Exec(){};//����
		virtual void Rendering(int index){};//�����_�����O
		virtual void Rendering( ){};//�����_�����O
		
		virtual void Load(Renderer::IRender *pRender){};//�t�@�C���ǂݍ���
		
	public:
	
		void SetPosition( Math::Vector3D vPos );//�ʒu�̐ݒ�
		void SetRotate( Math::Vector3D vRot );//��]�p�x�̐ݒ�
		void SetScale( Math::Vector3D vScale );//�g�k�̎擾
		
	public:
	
		Math::Vector3D GetPosition();//�ʒu�̎擾
		Math::Vector3D GetRotate();//��]�p�x�̎擾
		Math::Vector3D GetScale();//�g�k�̎擾
		
		string GetFileName()
		{
			return m_DataName;
		}
		
};
