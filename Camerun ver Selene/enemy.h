//*============================================================================
//enemy.h
//*============================================================================
//[history]
//	08/03/09�@�C���J�n
//[author]
//	Taka
//=============================================================================

#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "Sprite3D.h"
#include <vector>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�G�p�N���X
//=============================================================================
class CEnemy :public CCharacter
{
	protected:
	
		CCharacter *m_pStunEffect;//�C��G�t�F�N�g
		
		Math::Animation *m_pAnimX;//X���̃A�j���[�V����
		Math::Animation *m_pAnimY;//Y���̃A�j���[�V����
		Math::Animation *m_pAnimZ;//Z���̃A�j���[�V����
		Math::Animation *m_pAnimRotX;//X������]�̃A�j���[�V����
		Math::Animation *m_pAnimSpeed;//�L�[�X�s�[�h
		float m_fKeyTime;//�L�[�A�j���[�V��������
		float m_fKeySpeed;//�L�[�X�s�[�h
		
		float m_fMaxKeyTime;//�ő�L�[����
		
		vector< float > m_vDeltaKey;//�L�[���Ԃ̍���
		vector< float > m_vKeySpeed;//�L�[�X�s�[�h
		vector< float > m_vKeyTime;//�L�[����
		
		int m_AnimID[ANIM_MAX];//�A�j���[�V����ID
		float m_fAnimTime[ANIM_MAX];//���݂̃A�j���[�V��������
		
		bool m_IsChangeKeyTime;//�L�[�^�C�����ύX���ꂽ���ǂ���
		Uint32 m_KeyIndex;//���ݎQ�Ƃ��Ă���L�[�̃C���f�b�N�X
		
		bool m_IsStopKeyTime;//�L�[�^�C�����~�܂��Ă��邩�ǂ���
	
	public:
	
		CEnemy(){};//�R���X�g���N�^
		CEnemy( string name, Math::Vector3D vPos );//�R���X�g���N�^
		~CEnemy();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		virtual void MoveExec(){};//�ړ�����
		
	public:
	
		void FlashedState( );//�t���b�V���𗁂т���Ԃ̏���
		void ChangeAnimation( );//�A�j���[�V�����̕ύX
		
		void ChangeKeyTime( Peripheral::IMouse *pMouse );//�L�[�^�C���̕ύX
		void ChangeKeySpeed( Peripheral::IInputController *pCtrl );//�L�[�X�s�[�h�̕ύX
		
		
	public:

		void SetAnimationID( eAnimType index,  int animID );//�A�j��ID�̐ݒ�
		
		/*�C��G�t�F�N�g�̎擾*/
		void GetStunEffect( CCharacter *pEffect )
		{
			m_pStunEffect = pEffect;
			pEffect->AddRef();
		}
		
	
		
	public:
	
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
		
		/*�L�[�A�j���[�V�������Ԃ̎擾*/
		float GetKeyTime( )
		{
			return m_fKeyTime;
		}
	
	
};