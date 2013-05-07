//*============================================================================
//DebugLine.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "DebugLine.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CDebugLine::CDebugLine(void) :m_pLine(NULL), m_pActorLine(NULL)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDebugLine::~CDebugLine(void)
{
	SAFE_RELEASE( m_pActorLine );
	SAFE_RELEASE( m_pLine );
}

//=============================================================================
//���C���̐���
//=============================================================================
//[input]
//	pRender:�����_�����O�p�f�o�C�X
//=============================================================================
void CDebugLine::CreateLine( Renderer::IRender *pRender )
{
	m_pLine = pRender->CreateLine3D( 500000, false );
}

//=============================================================================
//�A�N�^�[�̐���
//=============================================================================
//[input]
//	pSceneMgr:�V�[���f�o�C�X
//=============================================================================
void CDebugLine::CreateActor( Selene::Scene::ISceneManager *pSceneMgr )
{
	m_pActorLine = pSceneMgr->CreateActor( m_pLine );
}

//=============================================================================
//�����_�����O
//=============================================================================
void CDebugLine::Rendering()
{
	m_pActorLine->RenderingRequest();
}

//=============================================================================
//���C���̒ǉ�
//=============================================================================
//[input]
//	pLine:�ǉ����郉�C��
//	LineNum:���C����
//=============================================================================
void CDebugLine::AddLine( Renderer::SLineVertex3D *pLine, int LineNum )
{
	m_pLine->Push( pLine, LineNum );
	
}

//=============================================================================
//�{�b�N�X�̒ǉ�
//=============================================================================
//[input]
//	Box:�ǉ�����{�b�N�X
//	Color:���C���̐F
//=============================================================================
void CDebugLine::AddBox( Collision::CBox &Box, CColor Color )
{
	m_pLine->PushBox( Box, Color );
	
}




