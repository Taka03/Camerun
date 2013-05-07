#include "Draw2DObject.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
Draw2DObject::Draw2DObject( string name ) 
{
	m_DataName = name;
	
	m_vPos.Set(0, 0, 0);
	m_vRot.Set(0, 0, 0);
}

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
Draw2DObject::Draw2DObject( string name, Math::Vector2D vPos )
{
	m_DataName = name;
	
	m_vPos.Set( vPos.x, vPos.y, 0 );
	m_vRot.Set(0, 0, 0);
}

//============================================================================
//�f�X�g���N�^
//============================================================================
Draw2DObject::~Draw2DObject( ) 
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		SAFE_DELETE( i->gameobj );
	}
	
}



//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
void Draw2DObject::Load( Renderer::IRender *pRender )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		Draw2DObject *obj = dynamic_cast<Draw2DObject *>( i->gameobj );
		
		obj->Load( pRender );
			
	}
}

//============================================================================
//����
//============================================================================
void Draw2DObject::Exec()
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		if( !(i->gameobj->GetStopFlag() ) )
		{	
			i->gameobj->Exec();
		}
	}

}

//============================================================================
//�A�N�^�[�̐���
//============================================================================
//[input]
//	pSceneMgr:�V�[���Ǘ��p�f�o�C�X
//===========================================================================
//void Draw2DObject::CreateActor( Scene::ISceneManager *pSceneMgr )
//{
//	if( m_pSprite != NULL )
//	{
//		m_pActorSpr = pSceneMgr->CreateActor(
//	}
//}

//============================================================================
//�����_�����O
//============================================================================
void Draw2DObject::Rendering( )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		Draw2DObject *obj = dynamic_cast<Draw2DObject *>( i->gameobj );
		
		if( obj->GetVisibleFlag() )
		{	
			obj->Rendering( );
		}
	}
}





