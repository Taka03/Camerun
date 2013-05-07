//*============================================================================
//BGM.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "BGM.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//=============================================================================
CBGM::CBGM( std::string name ) :m_pBGM(NULL)
{
	m_DataName = name;
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBGM::~CBGM(void)
{
	SAFE_RELEASE( m_pBGM );
}

//=============================================================================
//�T�E���h�̓ǂݍ���
//=============================================================================
//[input]
//	pCore:�R�A�f�o�C�X
//=============================================================================
void CBGM::LoadSound( ICore *pCore )
{
	if( !m_DataName.empty() )
	{	
		m_pBGM = pCore->CreateStreamSoundFromFile( m_DataName.c_str(), false, "OggVorbis" );
	}
	
}

//=============================================================================
//����
//=============================================================================
void CBGM::Exec()
{
	m_pBGM->Play(-1);
}

//=============================================================================
//�t�F�[�h�A�E�g
//=============================================================================
void CBGM::FadeOut()
{
	static int count = 0;
	
	while( count <= 60 )
	{
	
		float fVolume = Interpolation::Flat( 100.0f, 0.0f, 60, count );
		
		m_pBGM->SetVolume( fVolume );
		
		count++;
		
	
	}
	
	if( count >= 60 )
	{
		count = 0;
	}

	
}




