//*============================================================================
//Game.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Game.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGame::CGame(void) :m_pCore(NULL), m_pGraphicCard(NULL), m_pFileMgr(NULL), 
					m_ScreenWidth(800), m_ScreenHeight(600)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame(void)
{
	SAFE_RELEASE( m_pRender );
	SAFE_RELEASE( m_pFileMgr );
	SAFE_RELEASE( m_pGraphicCard );
	SAFE_RELEASE( m_pCore );
	
}

//=============================================================================
//�R�A�̐���
//=============================================================================
void CGame::CreateCore()
{
	
	#if defined(DEBUG) | defined(_DEBUG)
		/*�V�X�e���̏�����*/
		System::Initialize();
		
	#else
	
		//System::Initialize( true, false );
		System::Initialize();
		
	#endif
	
	/*�R�A�̐���*/
	m_pCore = System::CreateCore();
	
}

//=============================================================================
//������
//=============================================================================
bool CGame::Initialize()
{
	/*������*/
	m_pCore->Initialize( "�L����RUN", FRAME_RATE_60 );
	
	//-----------------------------------------------------------------
	// �^�C�g���o�[�ɏ���\��
	//-----------------------------------------------------------------
	#if defined(DEBUG) | (_DEBUG)	
		m_pCore->EnableDrawTitleInformation( true );
	#endif

	//-----------------------------------------------------------------
	// �t�@�C���o�^
	//-----------------------------------------------------------------
	// �t�@�C���}�l�[�W���[�𐶐�
	m_pFileMgr = m_pCore->CreateFileManager();
	// �R�A�ɐݒ�
	m_pCore->SetFileManager( m_pFileMgr );
	// ���[�g�f�B���N�g����ݒ�
	#if defined(DEBUG) | (_DEBUG)
		
		m_pFileMgr->SetRootPath( 0, "../data" );
		
	#else
	
		m_pFileMgr->SetRootPath( 0, "./data", "LXfj6MhP" );
	
	#endif

	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h���擾
	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���܂��B
	// IGraphicCard�C���^�[�t�F�C�X����͐ڑ����ꂽ
	// �O���t�B�b�N�J�[�h�̔\�͂��擾���鎖���\�ł��B
	// IGraphicCard�C���^�[�t�F�C�X��1��ICore�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	m_pGraphicCard = m_pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
	
	if( m_pGraphicCard == NULL )
	{
		return false;
	}

	//-----------------------------------------------------------------
	// �E�B���h�E�쐬
	//-----------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
	// �E�B���h�E�𐶐����܂��B
	// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
	// ICore::Start()���Ăяo���O�ɍs���Ă��������B
	m_pCore->Start( m_ScreenWidth, m_ScreenHeight, true );

	//-----------------------------------------------------------------
	// �����_���[���擾
	//-----------------------------------------------------------------
	// �쐬�����O���t�B�b�N�J�[�h�����ʕ`��p�̃����_���[���擾���܂��B
	// Renderer::IRender�C���^�[�t�F�C�X��1��IGraphicCard�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	m_pRender = m_pGraphicCard->CreateRender();
	
	if ( m_pRender == NULL ) 
	{
		return false;
	}
	
	Renderer::CTextureConfig Config;
	
	// �e�N�X�`���t�H�[�}�b�g
	Config.SetColorKey( CColor(0,0,0,0) );
	Config.SetFormat( FORMAT_TEXTURE_32BIT );
	Config.SetMipmapEnable( true );
	m_pRender->SetTextureConfig( Config );
	
	return true;
}

//=============================================================================
//�e�N�X�`���t�B���^�̐ݒ�
//=============================================================================
void CGame::SetTextureFilter()
{
	// �t�B���^�����O   
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_LIGHT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_ENVIRONMENT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_SPECULAR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_NORMAL, TEXTURE_FILTER_3D_LOW );
}

//=============================================================================
//�Q�ƃJ�E���^����
//=============================================================================
void CGame::AddRef()
{
	m_pRender->AddRef();
	m_pGraphicCard->AddRef();
	m_pFileMgr->AddRef();
	m_pCore->AddRef();
}
	



