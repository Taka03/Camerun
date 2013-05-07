//*============================================================================
//Game.h
//*============================================================================
//[history]
//	08/03/05�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Selene.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//class
//=============================================================================
//[desc]
//	�Q�[���p�N���X
//=============================================================================
class CGame
{
	private:
	
		ICore	*m_pCore;//�R�A�f�o�C�X
		IGraphicCard	*m_pGraphicCard;//�O���t�B�b�N�J�[�h�f�o�C�X
		File::IFileManager	*m_pFileMgr;//�t�@�C���Ǘ��f�o�C�X
		Renderer::IRender	*m_pRender;//�����_���[�p�f�o�C�X
		
	private:
	
		const Sint32 m_ScreenWidth;//��ʕ�
		const Sint32 m_ScreenHeight;//��ʍ���
		
	public:
		CGame(void);//�R���X�g���N�^
		~CGame(void);//�f�X�g���N�^
		
	public:
	
		void CreateCore();//�R�A�̐���
		bool Initialize();//������
		void SetTextureFilter();//�e�N�X�`���t�B���^�̐ݒ�
		
		virtual void AddRef();
		
	/*Get�n*/
	public:
	
		/*�R�A�f�o�C�X�̎擾*/
		ICore	*GetCore() const
		{
			return m_pCore;
		}
		
		/*�O���t�B�b�N�J�[�h�f�o�C�X�̎擾*/
		IGraphicCard	*GetGraphicCard() const
		{
			return m_pGraphicCard;
		}
		
		/*�t�@�C���Ǘ��f�o�C�X�̎擾*/
		File::IFileManager	*GetFileMgr() const
		{
			return m_pFileMgr;
		}
		
		/*�����_���[�p�f�o�C�X�̎擾*/
		Renderer::IRender	*GetRenderer() const
		{
			return m_pRender;
		}
		
		//��ʕ��̎擾		
		Sint32 GetScreenWidth()
		{
			return m_ScreenWidth;
		}
		
		//��ʍ����̎擾
		Sint32 GetScreenHeight()
		{
			return m_ScreenHeight;
		}
		
};
