//*============================================================================
//joypad.cpp
//*============================================================================

//============================================================================
//include
//============================================================================
#include "joypad.h"
#include <fstream>
#include <vector>

Peripheral::IInputController *CJoyPad::m_pController = NULL;

////============================================================================
////�{�^���̐ݒ�
////============================================================================
////[input]
////	luaState:Lua�̃X�^�b�N�|�C���^
////============================================================================
//int SetButtonType( lua_State *L )
//{
//	int x = lua_tonumber( L, 1 );
//	
//	int y = lua_tonumber( L, 2 );
//	
//	return 1;	
//}




//============================================================================
//�R���X�g���N�^
//============================================================================
CJoyPad::CJoyPad() :m_pJoystick(NULL)
{

}

//============================================================================
//�f�X�g���N�^
//============================================================================
CJoyPad::~CJoyPad()
{
	SAFE_RELEASE( m_pJoystick );
	SAFE_RELEASE( m_pController );
	
}

//============================================================================
//�f�o�C�X�̍쐬
//============================================================================
//[input]
//	pCore:�R�A�f�o�C�X
//============================================================================
void CJoyPad::CreateDevice( ICore *pCore )
{
	if( pCore != NULL )
	{	
		m_pController = pCore->GetInputController( 0, 30, 5 );
		m_pJoystick = pCore->GetJoystick( 0 );
	}
	
	Initialize();
	
}

//============================================================================
//������
//============================================================================
void CJoyPad::Initialize( )
{
	if( m_pController != NULL )
	{
		//---------------------------------------------
		//�{�^���̐ݒ�
		//---------------------------------------------
		//m_pController->SetButton(BUTTON_01, PAD_BUTTON_01);
		//m_pController->SetButton(BUTTON_02, PAD_BUTTON_02);
		//m_pController->SetButton(BUTTON_03, PAD_BUTTON_03);
		//lua_State *L = lua_open();
		//
		//luaL_openlibs( L );

		//lua_register( L, "SetButtonType", SetButtonType ); 
		//
		//
		//luaL_dofile( L, "test.lua" );
		//
		//
		//int x = g_x;
		//int y = g_y;
		
		
		
		
	//	m_pController->SetButton( deb.x, deb.y );
		std::ifstream ifs("keydata.csv");
		
		const int MAX_BUTTON = 9;
		
		for( int i = 0;i < MAX_BUTTON;++i )
		{
			int Key = 0;
			
			ifs >> Key;
			
			m_pController->SetButton( (eInputButtonType)(i+16), (ePadButtonType)(Key) );
		}
		
		
		//---------------------------------------------
		//���̐ݒ�
		//---------------------------------------------
		m_pController->SetAxisX( AXIS_TYPE_01, PAD_AXIS_POSITION, PAD_AXIS_X );
		m_pController->SetAxisY( AXIS_TYPE_01, PAD_AXIS_POSITION, PAD_AXIS_Y );
		
		
		//m_pController->SetAxisX( AXIS_TYPE_02, PAD_AXIS_POSITION_ROTATE, PAD_AXIS_Z );
	//	m_pController->SetAxisY( AXIS_TYPE_02, PAD_AXIS_POSITION_ROTATE, PAD_AXIS_Y );
		
		
		//---------------------------------------------
		//��փ{�^���̐ݒ�
		//---------------------------------------------
		m_pController->SetAlias(BUTTON_01, SELENE_VK_Z);
		m_pController->SetAlias(BUTTON_02, SELENE_VK_X);
		m_pController->SetAlias(BUTTON_03, SELENE_VK_C);
		m_pController->SetAlias(BUTTON_04, SELENE_VK_V);
		m_pController->SetAlias(BUTTON_05, SELENE_VK_S);
		m_pController->SetAlias(BUTTON_06, SELENE_VK_A);
		
		
		m_pController->SetAlias(BUTTON_AXIS1_UP, SELENE_VK_UP);
		m_pController->SetAlias(BUTTON_AXIS1_DOWN, SELENE_VK_DOWN);
		m_pController->SetAlias(BUTTON_AXIS1_LEFT, SELENE_VK_LEFT);
		m_pController->SetAlias(BUTTON_AXIS1_RIGHT, SELENE_VK_RIGHT);
		
		
		
		//m_pController->SetAlias(BUTTON_AXIS2_UP, SELENE_VK_UP );
		//m_pController->SetAlias(BUTTON_AXIS2_DOWN, SELENE_VK_DOWN);
		//m_pController->SetAlias(BUTTON_AXIS2_LEFT, SELENE_VK_LEFT);
		//m_pController->SetAlias(BUTTON_AXIS2_RIGHT, SELENE_VK_RIGHT);
		
		
	}
	
}

//============================================================================
//�p�b�h�̍X�V
//============================================================================
void CJoyPad::Update()
{
	m_pController->Refresh();
	
}

//============================================================================
//�Q�ƃJ�E���^�̑���
//============================================================================
void CJoyPad::AddRef()
{
	m_pController->AddRef();
	m_pJoystick->AddRef();
}



