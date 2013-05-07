//*============================================================================
//Scene.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"
#include "joypad.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "Train.h"
#include "CamObject.h"
#include "FlagObject.h"
#include "SoundEffect.h"
#include "Field.h"
#include "Sprite.h"
#include "FontSprite.h"
#include "BGM.h"
#include "SceneManager.h"
#include "Game.h"
#include "Application.h"
#include "Photo.h"
#include "DebugLine.h"
#include "MissionManager.h"
#include "Menu.h"
#include "Sprite3D.h"
#include "Particle.h"
#include "Flash.h"
#include "MiniMap.h"

//=============================================================================
//enum
//=============================================================================
//�V�[���^�C�v
enum eSceneType
{
	SCENE_INIT,
	SCENE_TITLE,
	SCENE_MISSIONSELECT,
	SCENE_CHAT,
	SCENE_DRAWMISSION,
	SCENE_DEMO,
	SCENE_GAMEMAIN,
	SCENE_STARTMENU,
	SCENE_PHOTOSCREEN,
	SCENE_RESULT,
	SCENE_CALCSCORE,
	SCENE_ENDING,
};

enum eSceneState
{
	STATE_STANDBY,//�J�ڒ�
	STATE_FADEIN,//�t�F�[�h�C��
	STATE_FADEOUT,//�t�F�[�h�A�E�g
	STATE_FINISH,//�J�ڏI��
};

const int BIRD_MAX = 6;
const int MOUSE_MAX = 3;
const int MINI_CHARA_MAX = BIRD_MAX + MOUSE_MAX;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[���p�N���X
//=============================================================================
class CScene
{
	private:
	
		CApplication	*m_pApp;//�Q�[���p�f�o�C�X
		CGameObject *m_pGameObj;//�Q�[���I�u�W�F�N�g
		CDraw3DObject *m_p3DObj;//3D���f���I�u�W�F�N�g
		Draw2DObject  *m_p2DObj;//2D�摜�I�u�W�F�N�g
		CSound		*m_pSoundObj;//�T�E���h�I�u�W�F�N�g
		CSceneManager *m_pSceneMgr[S_MAX];//�V�[���Ǘ�
		MissionManager *m_pMissionMgr;//�~�b�V�����Ǘ�
		CJoyPad *m_pJoyPad;//�W���C�p�b�h�p�f�o�C�X
		Selene::Peripheral::IMouse *m_pMouse;//�}�E�X�p�f�o�C�X
		eSceneType m_eNowScene;//���݂̃V�[��
		eSceneType m_eNextScene;//���̃V�[��
		bool m_IsFirstBoot;//�����N������t���O
		bool m_IsLoadEnd;//���[�h�I���t���O
		
		Sint32 m_PhotoIndex;//�\������ʐ^�p
		Sint32 m_FilmCount;//�t�B�����J�E���^		
		eSceneState m_eSceneState;//�V�[�����
		
		tagTime m_ClearTime;//�N���A����
		tagTime m_CurrentTime;//�o�ߎ���
		float m_fFadeTime;//�t�F�[�h����
		
		Sint32 m_VisibleCount;//�\���J�E���^
		
		Sint32 m_FontSize;//�t�H���g�T�C�Y
		
		//Selene::Thread::CThread CThread;//�X���b�h
		
	private:
	
		void FadeIn();//�t�F�[�h�C��
		void FadeOut();//�t�F�[�h�A�E�g
		
	public:
	
		CScene(){};
		CScene( CApplication *pApp, CJoyPad *pJoy );//�R���X�g���N�^
		~CScene(void);//�f�X�g���N�^
		
		virtual bool Init( CScene *pScene );//������
		virtual void Exec( CScene *pScene );//����
		
		void SceneStateExec();//�V�[����Ԃɂ��ω�
		void TimeCount();//���Ԍv��
		
		/*�t�B�����J�E���^�̑���*/
		void AddFilmCounter( )
		{
			m_FilmCount ++;
		}
		
		/*�\���J�E���^�̉��Z*/
		void AddVisibleCounter()
		{
			m_VisibleCount++;
			return;
		}
		
		
	/*Set�n*/
	public:
	
		void ChangeScene( eSceneType scene );//�V�[���̈ڍs
		void SetNextScene( eSceneType scene );//���̃V�[���̐ݒ�
		
		/*�ʐ^�C���f�b�N�X�̐ݒ�*/
		void SetPhotoIndex( Sint32 index )
		{
			m_PhotoIndex = index;
		}
		
		/*�N���A���Ԃ̐ݒ�*/
		void SetClearTime( tagTime Time )
		{
			m_ClearTime = Time;			
		}
		
		/*�o�ߎ��Ԃ̐ݒ�*/
		void SetCurrentTime( tagTime Time )
		{
			m_CurrentTime = Time;
		}
		
		/*���[�h�I���t���O�̐ݒ�*/
		void SetLoadEndFlag( bool flag )
		{
			m_IsLoadEnd = flag;
		}
		
		/*�V�[����Ԃ̐ݒ�*/
		void SetSceneState( eSceneState state )
		{
			m_eSceneState = state;
		}
		
		/*�t�F�[�h���Ԃ̐ݒ�*/
		void SetFadeTime( float fTime )
		{
			m_fFadeTime = fTime;
		}
		
		/*�t�B�����J�E���g�̃Z�b�g*/
		void SetFilmCount( Sint32 count )
		{
			m_FilmCount = count;
		}
		
		/*�t�H���g�T�C�Y�̐ݒ�*/
		void SetFontSize( Sint32 Size )
		{
			m_FontSize = Size;
		}
		
		void SetVisibleCount( Sint32 count )
		{
			m_VisibleCount = count;
		}
		
		
	/*Get�n*/
	public:
		
		//�A�v���P�[�V�����p�f�o�C�X�̎擾		
		CApplication *GetAppDevice() const
		{
			return m_pApp;
		}

		//�Q�[���I�u�W�F�N�g�̎擾		
		CGameObject *GetGameObject() const
		{
			return m_pGameObj;
		}

		//3D���f���I�u�W�F�N�g�̎擾		
		CDraw3DObject *Get3DObject() const 
		{
			return m_p3DObj;
		}

		//2D�摜�I�u�W�F�N�g�̎擾		
		Draw2DObject  *Get2DObject() const
		{
			return m_p2DObj;
		}
		
		//�T�E���h�I�u�W�F�N�g�̎擾
		CSound		*GetSoundObj() const
		{
			return m_pSoundObj;
		}
		
		//�V�[���Ǘ��̎擾
		CSceneManager *GetSceneMgr( int index ) const
		{
			return m_pSceneMgr[index];
		}
		
		/*�W���C�p�b�h�̎擾*/
		CJoyPad *GetJoyPad() const
		{
			return m_pJoyPad;
		}
		
		/*�~�b�V�����}�l�[�W���̎擾*/
		MissionManager *GetMissionMgr()
		{
			return m_pMissionMgr;
		}
		
		//�}�E�X�p�f�o�C�X�̎擾
		Selene::Peripheral::IMouse *GetMouse() const
		{
			return m_pMouse;
		}
		
		/*�V�[����Ԃ̎擾*/
		eSceneState GetSceneState() const
		{
			return m_eSceneState;
		}
		
		/*���̃V�[���̎擾*/
		eSceneType GetNowScene() const
		{
			return m_eNowScene;
		}
		
		/*���̃V�[���̎擾*/
		eSceneType GetNextScene() const
		{
			return m_eNextScene;
		}
		
		/*�ʐ^�\���p�̃C���f�b�N�X*/
		Sint32 GetPhotoIndex() const
		{
			return m_PhotoIndex;
		}
		
		/*�t�B�����J�E���^�̎擾*/
		Sint32 GetFilmCount() const
		{
			return m_FilmCount;
		}
		
		/*�o�ߎ��Ԃ̎擾*/
		tagTime GetCountTime() const
		{
			return m_CurrentTime;
		}
		
		/*�N���A���Ԃ̎擾*/
		tagTime GetClearTime() const
		{
			return m_ClearTime;
		}
		
		/*���݂̎��Ԃ̎擾*/
		tagTime GetCurrentTime() const
		{
			return m_CurrentTime;
		}
		
		/*�����u�[�g�t���O�̎擾*/
		bool GetFirstBootFlag() const
		{
			return m_IsFirstBoot;
		}
		
		/*���[�h�I���t���O�̎擾*/
		bool GetLoadEndFlag()
		{
			return m_IsLoadEnd;
		}
		
		/*�\���J�E���^�̎擾*/
		Sint32 GetVisibleCount()
		{
			return m_VisibleCount;
		}
		
		
		
		
};
