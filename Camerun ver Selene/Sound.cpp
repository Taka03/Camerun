//*============================================================================
//Sound.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sound.h"

CSound::~CSound()
{
	list<ListData>::iterator i;
	
	for(i = m_ObjectList.begin();i != m_ObjectList.end();i++)
	{
		CSound *obj = dynamic_cast<CSound *>( i->gameobj );
		
		SAFE_DELETE(obj);
	}

}

//=============================================================================
//�T�E���h�̓ǂݍ���
//=============================================================================
//[input]
//	pCore:�R�A�f�o�C�X
//=============================================================================
void CSound::LoadSound( ICore *pCore )
{
	list<ListData>::iterator i;
	
	for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	{
		CSound *obj = dynamic_cast<CSound *>( i->gameobj );
		
		obj->LoadSound( pCore );
	}
	
}
