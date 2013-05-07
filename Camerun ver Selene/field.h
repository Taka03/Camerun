//*============================================================================
//field.h
//*============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "C3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t�B�[���h�p�N���X
//=============================================================================
class CField :public CDraw3DObject
{
	private:
	
		Renderer::Object::IMapModel *m_pMapModel;//�}�b�v�̃��f���f�[�^
		Scene::IMapActor			*m_pActorMap[S_MAX];//�}�b�v�A�N�^�[
		Renderer::Object::ILine3D   *m_pLine;//�f�o�b�O���C��
		
	public:
	
		CField(){};//�R���X�g���N�^
		CField( string name );//�R���X�g���N�^
		~CField();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void Rendering(int index);//�����_�����O
		
		virtual void Load( Renderer::IRender *pRender );//�t�@�C���ǂݍ���
		
		//virtual void SetActor( Math::Style *pStyle );//�A�N�^�[�̃Z�b�g	
		virtual void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
		
		void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//���̃��f���̐���
	public:
		
		void	CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		//void	CreateActor( int index, Scene::ICustomizedSceneManager *pSceneMgr );//�A�N�^�[�̐���
		
		
		/*�Փ˔���p���C��*/
		void SetCollisionLine( Renderer::Object::ILine3D *pLine )
		{
			m_pLine = pLine;
		}
	
	/*Get�n*/
	public:
	
		/*�}�b�v���f���f�[�^�̎擾*/
		Renderer::Object::IMapModel *GetMapModel() const
		{
			return m_pMapModel;
		}
		
		/*�}�b�v�A�N�^�[�̎擾*/
		Scene::IMapActor *GetMapActor( int index ) const
		{
			return m_pActorMap[index];
		}

		
	
		
		
};