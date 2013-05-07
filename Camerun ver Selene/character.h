//*============================================================================
//character.h
//*============================================================================
//[history]
//	08/03/03�@�C���J�n
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "c3dobject.h"

//=============================================================================
//enum
//=============================================================================

enum eAnimType
{
	ANIM_NOW,
	ANIM_NEXT,
	ANIM_MAX,
};

//�A�j���[�V�����̏��
enum eAnimState
{
	ANIM_STANDBY,//�ҋ@��
	ANIM_CHANGESTART,//�؂�ւ��J�n
	ANIM_CHANGE,//�؂�ւ���
	ANIM_CHANGEEND,//�؂�ւ��I��
};

//#define DEBUG_MAP


//=============================================================================
//class
//=============================================================================
//[Desc]
//	�L�����N�^�[�p�N���X
//=============================================================================
class CCharacter :public CDraw3DObject
{
	private:
	
	protected:
	
		Renderer::Object::IModel *m_pModel;//���f���f�[�^	
		Scene::IModelActor		 *m_pActorModel[S_MAX];//���f���A�N�^�[	
		Dynamics::IRigidBody	 *m_pRigidBody;//����
		
	protected:
	
	
		Math::Vector3D m_vDirection;//�L�����̌����Ă������
		
		Math::Vector3D m_vOldPos;//�ʒu�̃o�b�N�A�b�v�p
		Math::Vector3D m_vSetFlagPos;//�t���O�ݒu�ʒu
		Math::Vector3D m_vArrowPos;//�^�[�Q�b�g���ʒu
		
		float m_fGravity;//�d��
		
		float m_fWeight;//�d��
		float m_fSpeed;//�ړ����x
		
		bool m_IsSetFlag;//�t���O�ݒu����t���O
	
	public:
	
		CCharacter(){}; //�R���X�g���N�^
		CCharacter( string name ); //�R���X�g���N�^
		CCharacter( string name, Math::Vector3D vPos );//�R���X�g���N�^
		
		~CCharacter(); //�f�X�g���N�^
	
		void Init();//������
		void Exec();//����
		void Rendering( int index );//�����_�����O
		virtual void MoveExec(){};
		
		virtual void Load( Renderer::IRender *pRender );//�t�@�C���ǂݍ���
		virtual void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		void CreateRigidModel( Dynamics::ISimulationWorld *pWorld );//���̃��f���̐���
		void CreateCollision();//�R���W�����f�[�^�̍쐬
		
		virtual void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
		
		bool HitCheck( CCharacter *pChara );
		bool HitCheck( CDraw3DObject **ppChara );//�����蔻��
		bool HitCheck( Selene::Collision::CLine3D &vRay );//�����蔻��
		bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		
		float CheckDistance( CCharacter *pChara );//�L���������𑪂�
		
		virtual bool GroundCheck( CCharacter *pChara, int index );//�n�ʃ`�F�b�N
		bool GroundCheck( CCharacter *pChara );//�n�ʃ`�F�b�N
		virtual bool GroundCheck( Scene::IMapActor *pActor );//�n�ʃ`�F�b�N
		bool GroundCheck2( Scene::IMapActor *pActor );//�n�ʃ`�F�b�N
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
	/*Set�n*/
	public:
	
		void SetFlag( bool flag );//�t���O�ݒu����t���O�̐ݒu
		void SetGravity( Float fGravity );//�d�͂̐ݒ�	
		void SetOldPosition( Math::Vector3D vPos );//�o�b�N�A�b�v���W�̐ݒ�
		
		/*���̈ʒu�̐ݒ�*/
		void SetArrowPos( Math::Vector3D vPos )
		{
			m_vArrowPos = vPos;	
		}
		
	/*Get�n*/
	public:
	
		/*���f���f�[�^�̎擾*/
		Renderer::Object::IModel *GetModel() const
		{
			return m_pModel;
		}
		
		/*���f���A�N�^�[�̎擾*/
		Scene::IModelActor *GetModelActor( int index ) const
		{
			return m_pActorModel[index];
		}
		
		/*���̂̎擾*/
		Dynamics::IRigidBody *GetRigidBody() const
		{
			return m_pRigidBody;
		}
		
		/*�t���O�ݒu�ʒu�̎擾*/
		Math::Vector3D GetSetFlagPosition()
		{
			return m_vSetFlagPos;
		}
		
		/*�d�͉����x�̎擾*/
		Float GetGravity()
		{
			return m_fGravity;									
		}
		
		/*�ړ����x�̎擾*/
		float GetSpeed()
		{
			return m_fSpeed;
		}
		
		/*�t���O�ݒu����t���O�̎擾*/
		bool GetSetFlag()
		{
			return m_IsSetFlag;
		}
		
		/*�����W�̎擾*/
		Math::Vector3D GetOldPosition()
		{
			return m_vOldPos;
		}
		
		/*�^�[�Q�b�g���ʒu�̎擾*/
		Math::Vector3D GetArrowPosition()
		{
			return m_vArrowPos;
		}
		
		
		
		
};