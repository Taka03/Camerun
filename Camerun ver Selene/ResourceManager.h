//*============================================================================
//ResourceManager.h
//*============================================================================
//[history]
//	08/07/04�@�쐬
//[author]
//	Taka
//=============================================================================

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//enum
//=============================================================================
//���\�[�X�^�C�v
enum eResourceType
{
	TEXTURE,
	MODEL,
	MAP,
	SOUND,
	BGM,
	OTHER,
};


//=============================================================================
//class
//=============================================================================
//[desc]
//	���\�[�X�Ǘ��p�N���X
//=============================================================================
class CResourceManager
{
	private:
	
		ICore *m_pCore;//�R�A�f�o�C�X
		Selene::File::IFileManager *m_pFileMgr;//�t�@�C���Ǘ��f�o�C�X
		Renderer::IRender *m_pRender;//�����_���[�p�f�o�C�X
		
	private:
	
		CGameObject *m_pGameObj;//�Q�[���I�u�W�F�N�g
		
	private:
	
		Thread::CThread	m_Thread;//�X���b�h�p�n���h��
		Thread::CCriticalSection m_CS;//�N���e�B�J���Z�N�V����
		Thread::CEvent m_Event;//�C�x���g
	
		
	protected:
	
	private:
	
		static void LoadedProc( void *pData ) ;//���[�h�p�X���b�h
		virtual void Run();//�ǂݍ���
		
	public:
	
		CResourceManager( ICore *pCore, File::IFileManager *pFileMgr, Renderer::IRender *pRender );//�R���X�g���N�^
		~CResourceManager();//�f�X�g���N�^
		
		void AppendObject( eResourceType type );//�I�u�W�F�N�g�̒ǉ�
		
		//virtual Bool IsLoading(){};//���[�h�����ǂ���
		
	/*Set�n*/
	public:
	
	/*Get�n*/
	public:
	
		/*�Q�[���p�I�u�W�F�N�g�̎擾*/
		CGameObject *GetGameObject()
		{
			return m_pGameObj;
		}
};


