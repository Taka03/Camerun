//*============================================================================
//SoundEffect.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SoundEffect.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	name:データ名
//=============================================================================
CSoundEffect::CSoundEffect( std::string name ) :m_pSE(NULL)
{
	m_DataName = name;
}


//=============================================================================
//デストラクタ
//=============================================================================
CSoundEffect::~CSoundEffect(void)
{
	SAFE_RELEASE( m_pSE );
}

//=============================================================================
//サウンドの読み込み
//=============================================================================
//[input]
//	pCore:コアデバイス
//=============================================================================
void CSoundEffect::LoadSound( ICore *pCore )
{
	m_pSE = pCore->CreateSoundFromFile( m_DataName.c_str(), 1, false ); 
}

//=============================================================================
//処理
//=============================================================================
void CSoundEffect::Exec()
{
	m_pSE->Play(0);
}



