//*============================================================================
//EnemyAmeus.h
//*============================================================================
//[history]
//	08/04/15 �쐬
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "enemy.h"

//=============================================================================
//enum
//=============================================================================
/*�q�b�g�^�C�v*/
enum eHitType
{
	HIT_PLAYER,
	HIT_MAP,	
	HIT_NONE,
};

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�A���E�X�p�N���X
//=============================================================================
class CEnemyAmeus : public CEnemy
{
	private:
	
		bool m_IsHit;//�v���C���[�ɓ���������
		eHitType m_eHitType;//�q�b�g�^�C�v
		ICore *m_pCore;//�R�A
		
	
	public:
	
		CEnemyAmeus(){};//�R���X�g���N�^
		CEnemyAmeus( string name, Math::Vector3D vPos, string filename );//�R���X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void MoveExec( );//�ړ�
		
		static int SetAnimKey( lua_State *L );//�A�j���[�V�����L�[�̃Z�b�g
		
	public:
	
		/*�q�b�g�^�C�v�̐ݒ�*/
		void SetHitType( eHitType Type )
		{
			m_eHitType = Type;
		}
		
		/*�v���C���[�ɓ�����������t���O�̐ݒ�*/
		void SetHitFlag( bool flag )
		{
			m_IsHit = flag;
		}
		
		void GetCore( ICore *pCore )
		{
			m_pCore = pCore;
		}
		
	public:
	
		/*����t���O�̎擾*/
		bool GetHitFlag() const
		{
			return m_IsHit;
		}
		
};