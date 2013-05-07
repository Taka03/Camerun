//*============================================================================
//camera.h
//*============================================================================
//[history]
//	08/03/11�@�C��
//[author]
//	Taka
//============================================================================

//��d�C���N���[�h�h�~
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[desc]
//	�J�����p�N���X
//=============================================================================
class CCamera :public CGameObject
{
	private:
	
		Scene::ICamera *m_pCamera;//�J�����f�o�C�X
		
	private:
	
		Math::Vector3D m_vPos;//�ʒu
		Math::Vector3D m_vTarget;//�^�[�Q�b�g
		Math::Vector3D m_vRot;//��]�p�x
		Math::Style	   m_Style;//�p���f�[�^
		
		bool m_IsChangeTopView;//�g�b�v�r���[�؂�ւ�����t���O
	
	public:
	

		CCamera();//�R���X�g���N�^
		~CCamera();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
	public:
	
		void SetCamera( Scene::ISceneManager *pScene );//�J�����̃Z�b�g
		//void SetCamera( Scene::ICustomizedSceneManager *pScene );//�J�����̃Z�b�g
		
		void SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height );//�v���W�F�N�V�����̐ݒ�
		void SetTransform( Math::Style style );//�ό`�̓K�p	
		void SetTransform( );//�ό`�̓K�p
		void SetTransform2();//�ό`�̓K�p
		void SetTransform3();//�ό`�̓K�p
		void SetTransformDemo();//�f���p�̃J�����ړ�
		void SetPosition( Math::Vector3D vPos );//�ʒu�̐ݒ�
		void SetAngle( Sint32 Angle );//�p�x�̐ݒ�
		void SetTargetPos( Math::Vector3D vTarget );//�^�[�Q�b�g�̈ʒu�Z�b�g
		void SetStyle( Math::Style style );//�p���f�[�^�ݒ�		
		void SetRotate( Math::Vector3D vRot );//�p�x�̐ݒ�
		
		/*�g�b�v�r���[�t���O�̐ݒ�*/
		void SetTopViewFlag( bool flag)
		{
			m_IsChangeTopView = flag;
		}
	
		
	/*Get�n*/
	public:
	
		//�J�����f�o�C�X�̎擾
		Scene::ICamera *GetCamera()
		{
			return m_pCamera;
		}
		
		//�ʒu�̎擾		
		Math::Vector3D GetPosition()
		{
			return m_vPos;
		}
		//�^�[�Q�b�g�̎擾
		Math::Vector3D GetTarget()
		{
			return m_vTarget;
		}
		
		//�p���f�[�^�̎擾		
		Math::Style GetStyle()
		{
			return m_Style;
		}
		
		//��]�p�x�̐ݒ�
		Math::Vector3D GetRotate()
		{
			return m_vRot;
		}
		
		/*�g�b�v�r���[����t���O�̎擾*/
		bool GetTopViewFlag()
		{
			return m_IsChangeTopView;
		}

		
		
		
		
		
};