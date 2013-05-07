//*============================================================================
//C3DObject.h
//*============================================================================
//[history]
//	08/03/03�@�C���J�n
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "drawobject.h"

//=============================================================================
//enum
//=============================================================================
//�X�N���[���^�C�v
enum eScreenType
{
	S_MAIN,//���C�����
	S_SUB,//�T�u���
	S_MAX,
};


//�L�����N�^�[�^�C�v
enum eDraw3DType
{
	OBJ_PLAYER,//�v���C���[
	OBJ_ENEMY,//�G
	OBJ_MAP,//�}�b�v
	OBJ_OTHER,//���̑�
	
};


//=============================================================================
//class
//=============================================================================
//[desc]
//	3D�I�u�W�F�N�g�`��p�N���X
//=============================================================================
class CDraw3DObject :public CDrawObject
{
	private:
	
	protected:
	
		int m_ActorIndex;//�A�N�^�[�C���f�b�N�X
		Dynamics::IRigidModel *m_pRigidModel;//���̗p���f��
		eDraw3DType m_eType;//�I�u�W�F�N�g�^�C�v
		Selene::Renderer::Shader::IShader *m_pShader;//�V�F�[�_�[
		
	public:
	
		CDraw3DObject(void){};//�R���X�g���N�^
		CDraw3DObject( string name );//�R���X�g���N�^
		virtual ~CDraw3DObject(void);//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		virtual void MoveExec();//�ړ�����
		void Rendering(int index);//�����_�����O
		
		virtual void Load( Renderer::IRender *pRender );//�t�@�C���ǂݍ���
		void LoadShader( Renderer::IRender *pRender, string name );//�V�F�[�_�[�̓ǂݍ���
		
		virtual void CreateActor( int index,  Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		
		virtual void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//���̃��f���̐���
		virtual void CreateCollision();//�R���W�����f�[�^�̍쐬
		
		virtual bool HitCheck( CDraw3DObject **ppChara );//�����蔻��
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay );//�����蔻��
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj );//�����蔻��
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj );
		//virtual bool HitCheck( Selene::Collision::CBox &Box, CDraw3DObject **ppHitObj)
		
		virtual void FlashedState( );//�t���b�V���𗁂т���Ԃ̏���
	//	virtual void RecallFlag( Peripheral::IInputController *m_pCtrl );
		
		//virtual void CreateActor( int index,  Scene::ICustomizedSceneManager *pSceneMgr );//�A�N�^�[�̐���
		
		//virtual void SetActor( Math::Style *pStyle );//�A�N�^�[�̃Z�b�g
		
	/*Set�n*/
	public:
	
		virtual void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
	
	
	/*Get�n*/
	public:
	
		/*�A�N�^�[�C���f�b�N�X�̎擾*/
		int GetActorIndex()
		{
			return m_ActorIndex;
		}
		
		Dynamics::IRigidModel *GetRigidModel() const
		{
			return m_pRigidModel;
		}
		
		//�I�u�W�F�N�g�^�C�v�̎擾	
		eDraw3DType GetObjectType()
		{
			return m_eType;
		}
		
		

		
		
};
