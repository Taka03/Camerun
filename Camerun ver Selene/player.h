//*============================================================================
//player.h
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
#include "CamObject.h"
#include "SoundEffect.h"
#include "camera.h"
#include "Particle.h"
#include "Menu.h"
#include "Flash.h"
#include "field.h"
#include "Sprite3D.h"

//=============================================================================
//enum
//=============================================================================
enum ePlayerAnim
{
	ANIM_STAND,
	ANIM_WALK,
	ANIM_RUN,
	ANIM_DASH,
	ANIM_FALL_START,
	ANIM_FALL,
	ANIM_FALL_END,
	ANIM_SET_GROUND,
	ANIM_SET_MOVE,
};

//enum eSetType
//{
//	SET_GROUND,
//	
//}

const int RUN_EFFECT_NUM = 4;
const int FLASH_EFFECT_NUM = 6;
const int FLASH_CHARA_NUM = 4;//�t���b�V���łƂ߂邱�Ƃ��ł���G�̐�

//#define POP_UP 


//=============================================================================
//class
//=============================================================================
//[Desc]
//	�v���C���[�p�N���X
//=============================================================================
class CPlayer :public CCharacter
{
	private:

		Peripheral::IInputController *m_pCtrl;//�R���g���[���[�p�f�o�C�X	
		Peripheral::IJoystick *m_pJoy;//�W���C�p�b�h�p�f�o�C�X		
		
	private:
	
		CCamObject *m_pCamObj;//�J�����I�u�W�F�N�g
		
	
	private:
	
		bool	m_IsCameraMode;//�J�������[�h�ɂȂ��Ă��邩�ǂ���
		bool	m_IsFlashMode;//�t���b�V�����[�h�ɂȂ��Ă��邩�ǂ���
		bool	m_IsJumpFlag;//�W�����v�����ǂ���
		bool	m_IsSettingFlag;//�t���O�ݒu�����ǂ���
		
		Sint32 m_HoldTime;//�{�^���������Ă��鎞��
		
		Collision::CLine3D m_vRay;//�����蔻��p���C
		
		int m_AnimID[ANIM_MAX];//�A�j���[�V����ID
		float m_fAnimTime[ANIM_MAX];//���݂̃A�j���[�V��������
		eAnimState m_eAnimState;//�A�j���[�V�������
		
	public:
	
		CPlayer(){};//�R���X�g���N�^
		CPlayer( string name );//�R���X�g���N�^
		CPlayer( string name, Math::Vector3D vPos );//�R���X�g���N�^
		
		~CPlayer();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void AnimExec();//�A�j���[�V�����p����
		void MoveExec(){};//�ړ�����
		
	public:
	
		//void SetObject(  vPos, CDrawObject *obj );//�I�u�W�F�N�g�̐ݒu
		void SetFlash( CCharacter *obj[], Uint32 CharaMax, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] );//�t���b�V������
		void SetFlash( CCharacter *obj, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] );//�t���b�V������
		
		void SettingFlag( );//�t���O�ݒu
		bool SetFlagToGround( Sound::ISound *pSound, CCharacter *pFlag );
		//bool SetFlagToObject( CCharacter *pChara[FLASH_CHARA_NUM], Sound::ISound *pSound, Scene::IMapActor *pMapActor );//�I�u�W�F�N�g�ւ̃t���O�ݒu
		bool SetFlagToObject( CCharacter *pChara, Sound::ISound *pSound );//�I�u�W�F�N�g�ւ̃t���O�ݒu
		
		void AdjustDirection();//�����␳
		void Jump(  );//�W�����v����
		void Move( CCamera *pCam, CParticle *pParticle[RUN_EFFECT_NUM] );//�ړ�����
		void Move( );//�ړ�����
		void Move( Peripheral::IInputController *pCtrl );//�ړ�����
		bool MoveCheck( Scene::IMapActor *pActor );//�ړ��`�F�b�N
		bool MoveCheck( Scene::IModelActor *pActor );//�ړ��`�F�b�N
		bool MoveCheck( CCharacter *pChara );//�ړ��`�F�b�N
		bool GroundCheck( CField *pField );	//�n�ʃ`�F�b�N
		bool GroundCheck( CCharacter *pChara, int index );//�n�ʃ`�F�b�N
		bool FlagCheck( Scene::IMapActor *pMapActor );//�t���O���ݒu�ł��邩�ǂ���
		bool FlagObjectCheck( CCharacter *pChara[], Uint32 CharaMax, Sound::ISound *pSnd, CCharacter  **ppFlashedChara );//�t���O���ݒu�ł��邩����
		bool SettableFlagCheck( CCharacter *pChara, CSprite3D *pSpr );//�t���O�ݒu�\�`�F�b�N
		
		void MoveAdjust();//�ړ��␳
		void GroundAdjust();//�n�ʕ␳
		
		void RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CMenu *pMenu );//�t���O�̉��
		void RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CSprite3D *pSpr, CCharacter *pFlag );//�t���O�̉��
		
		
		void ChangeCameraMode( Sound::ISound *pSnd );//�J�������[�h�̐؂�ւ�
		void UpdateAnimation( );//�A�j���[�V�����̕ύX
		void ChangeAnimation( int animID );//�A�j���[�V�����̐؂�ւ�
		
		//�J�����I�u�W�F�N�g�̐ݒ�		
		void GetCamObject( CCamObject *pCamObj )
		{
			m_pCamObj = pCamObj;
		}
		
		
		
	/*Set�n*/
	public:
	
		void SetCameraModeFlag( bool flag );//�J�������[�h����t���O�̃Z�b�g
		void SetFlashModeFlag( bool flag );//�t���b�V�����[�h����t���O�̃Z�b�g
		void SetDirection();//�ʒu�̐ݒ�
		void SetController( Peripheral::IInputController *pCtrl, Peripheral::IJoystick *pJoy );//�R���g���[���[�p�f�o�C�X�̐ݒ�
		void SetAnimationID( eAnimType index,  int animID );//�A�j��ID�̐ݒ�
		
		/*�A�j���[�V������Ԃ̐ݒ�*/
		void SetAnimState( eAnimState state )
		{
			m_eAnimState = state;
		}
		
		/*�t���O�ݒu�A�j���[�V�������t���O�̐ݒ�*/
		void SetSettingFlag( bool flag )
		{
			m_IsSettingFlag = flag;
		}
		
		/*�A�j���[�V�������Ԃ̐ݒ�*/
		void SetAnimationTime( int index, float Time )
		{
			m_fAnimTime[index] = Time;	
		}
		
		

	/*Get�n*/
	public:
	
		//�J�������[�h�ɂȂ��Ă��邩�ǂ����̎擾	
		bool	IsCameraMode()
		{
			return m_IsCameraMode;
		}
		
		//�t���b�V�����[�h�ɂȂ��Ă��邩�ǂ����̎擾	
		bool	IsFlashMode()
		{
			return m_IsFlashMode;
		}
		
		//�����蔻��p���C�̎擾
		Collision::CLine3D GetRay() const
		{
			return m_vRay;
		}
		
		/*�A�j���[�V����ID�̎擾*/
		int GetAnimationID( int index )
		{
			return m_AnimID[index];
		}
		
		/*���݂̃A�j���[�V�������Ԃ̎擾*/	
		float GetAnimationTime( int index )
		{
			return m_fAnimTime[index];
		}
		
		/*�t���O�ݒu�A�j���[�V�������t���O�̐ݒ�*/
		bool GetSettingFlag()
		{
			return m_IsSettingFlag;
		}
		
};