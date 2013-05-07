//*============================================================================
//SceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneManager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneManager::CSceneManager(void) :m_pSceneMgr(NULL), m_pRenderTex(NULL)
{
	m_vPos.Set(0, 0);
	
	m_RenderTargetWidth = 800;
	m_RenderTargetHeight = 600;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	SAFE_RELEASE( m_pSceneMgr );
}

//=============================================================================
//�f�o�C�X�̐ݒ�
//=============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//=============================================================================
void CSceneManager::CreateDevice( Renderer::IRender *pRender )
{
	m_pSceneMgr = pRender->CreateSceneManager( 512, false );
	
	m_pRenderTex = pRender->CreateTextureRenderTarget( m_RenderTargetWidth, m_RenderTargetHeight, FORMAT_TARGET_32BIT );
	
}

//=============================================================================
//�����p�����[�^�[�̐ݒ�
//=============================================================================
//[input]
//	IsUseTex:�����_�����O�^�[�Q�b�g�p�e�N�X�`�����g����
//=============================================================================
void CSceneManager::SetInitParameter( bool IsUseTex )
{
	if( m_pSceneMgr != NULL )
	{
		if( IsUseTex )
		{

			m_pSceneMgr->InitParameter_RenderTargetData(
				m_pRenderTex,												// �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ځj
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// �`���̃����_�����O�^�[�Q�b�g�T�C�Y�i�����w�肳��Ă��鎞�́��̃e�N�X�`���T�C�Y�Ɏ����ϊ��j
				false );											// �`���̃e�N�X�`���T�C�Y���Q�̗ݏ�ɂ��邩�ǂ���
		}
		
		else
		{
			m_pSceneMgr->InitParameter_RenderTargetData(
				NULL,												// �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ځj
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// �`���̃����_�����O�^�[�Q�b�g�T�C�Y�i�����w�肳��Ă��鎞�́��̃e�N�X�`���T�C�Y�Ɏ����ϊ��j
				false );											// �`���̃e�N�X�`���T�C�Y���Q�̗ݏ�ɂ��邩�ǂ���
		
		}

		// �V�[���ɑ΂���G�t�F�N�g�̏�����
		//   �V�[���ɑ΂��čs���e�탌���_�����O�G�t�F�N�g�͂����ōs���܂��B
		m_pSceneMgr->InitParameter_Shading( SHADING_TYPE_NORMAL );							// �V�F�[�f�B���O
		//m_pSceneMgr->InitParameter_Fog( FOG_TYPE_DISABLE, FOG_EFFECT_LINEAR );				// �t�H�O
		//m_pSceneMgr->InitParameter_HighDynamicRange( HDR_TYPE_ENABLE, HDR_EFFECT_CROSS );		// HDR�����_�����O
	//		m_pSceneMgr->InitParameter_MotionBlur( MOTION_BLUR_TYPE_DISABLE );					// ���[�V�����u���[
	//		m_pSceneMgr->InitParameter_DepthOfField( DOF_TYPE_DISABLE );							// ��ʊE�[�x
		m_pSceneMgr->InitParameter_Shadow( SHADOW_TYPE_SHADOWMAP, SHADOW_QUARITY_MIDDLE );	// �e����
	//		m_pSceneMgr->InitParameter_AntiAliasType( AA_TYPE_DISABLE, 0.0f );					// �A���`�G�C���A�X

		// �V�[���̏������n�p�����[�^�[�̍X�V
		m_pSceneMgr->InitParameter_Update();
		
		
	}
}

//=============================================================================
//�X�J�C�h�[���̐���
//=============================================================================
//[input]
//	pTex:�e�N�X�`���n���h��
//	pRender:�����_���[�p�f�o�C�X
//=============================================================================
void CSceneManager::CreateSkyDoom( Renderer::ITexture *pTex, Renderer::IRender *pRender )
{

	// �X�J�C�h�[������
	//  ���\�����邽�߂̃X�J�C�h�[���𐶐����܂��B
	m_pSceneMgr->SceneSkydoom_Create(
		100.0f,						// ���a
		CColor(121,154,255),		// �n�\�F
		CColor(121,154,255),		// �V���F
		pTex );					// ��e�N�X�`��
		
}

//=============================================================================
//�p�����[�^�[�̐ݒ�
//=============================================================================
void CSceneManager::SetParameter()
{
	if( m_pSceneMgr != NULL )
	{
		m_pSceneMgr->Reset();

		// �V�[���̔w�i�̐F
		//m_pSceneMgr->SetParameter_BGColor( Math::Vector4D(0.0f,0.0f,0.0f,1.0f) );
		
		/*�`���̈�*/
		m_pSceneMgr->SetParameter_RenderRect( Math::Rect2DF( m_vPos.x, m_vPos.y, toF(m_vPos.x + m_RenderTargetWidth), toF(m_vPos.y + m_RenderTargetHeight) ) );
		
		//m_pSceneMgr->SetParameter_Fog(
		//	Math::Vector3D( 0.8f, 0.8f, 0.8f ),		// �t�H�O�F
		//	50.0f,									// �t�H�O�J�n�ʒu
		//	300.0f );								// �t�H�O�I���ʒu
		//	
		
	}
}



//=============================================================================
//�`��̈�T�C�Y�̐ݒ�
//=============================================================================
//[input]
//	width:�ݒ肷�镝
//	height:�ݒ肷�鍂��
//=============================================================================
void CSceneManager::SetRenderSize( Sint32 width, Sint32 height )
{
	m_RenderTargetWidth = width;
	m_RenderTargetHeight = height;
}

//=============================================================================
//�`��ʒu�̐ݒ�
//=============================================================================
//[input]
//	vPos:�ݒ肷��ʒu
//=============================================================================
void CSceneManager::SetRenderPos( Selene::Math::Vector2D vPos )
{
	m_vPos = vPos;
}

