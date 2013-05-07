//*============================================================================
//DebugLine.h
//*============================================================================
//[history]
//	08/4/04�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "C3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�f�o�b�O���C���p�N���X
//=============================================================================
class CDebugLine :	public CDraw3DObject
{
	private:
	
		Renderer::Object::ILine3D *m_pLine;//���C��
		Scene::IPrimitiveActor *m_pActorLine;//���C���p�A�N�^�[
	
	public:
	
		CDebugLine(void);//�R���X�g���N�^
		virtual ~CDebugLine(void);//�f�X�g���N�^
		
		void CreateLine( Renderer::IRender *pRender );//���C���̐���
		void CreateActor( Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		
		void AddLine( Renderer::SLineVertex3D *pLine, int LineNum );//���C���̒ǉ�
		void AddBox( Collision::CBox &Box, CColor Color );//�{�b�N�X�̒ǉ�
		void Rendering();//�����_�����O
		
	/*Get�n*/
	public:
	
		//���C���̎擾
		Renderer::Object::ILine3D *GetLine() const
		{
			return m_pLine;
		}
		
		//���C���p�A�N�^�[�̎擾
		Scene::IPrimitiveActor *GetLineActor() const
		{
			return m_pActorLine;
		}
		
		
		
		
		
	
		
};
