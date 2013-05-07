//*============================================================================
//Menu.h
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Menu.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFontSpr:�t�H���g�X�v���C�g
//	pSpr:�X�v���C�g
//=============================================================================
CMenu::CMenu( CFontSprite *pFontSpr, CSprite *pSpr ) :m_pFontSpr( pFontSpr ), m_pSpr( pSpr )
{
	m_IsPopUp = false;
	m_CaptionName.clear();
	m_IsYesNoOrder = true;
	m_Cursor = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMenu::~CMenu()
{
	SAFE_DELETE( m_pRender );
}

//=============================================================================
//������
//=============================================================================
void CMenu::Init()
{

}

//=============================================================================
//�����_�����O
//=============================================================================
void CMenu::Rendering()
{
	if( m_IsPopUp )
	{
		m_pFontSpr->Rendering();
		
		m_pSpr->SetVisibleFlag( true );
		
	}
	
	else
	{
		m_pSpr->SetVisibleFlag( false );
	}
	
}

//=============================================================================
//����
//=============================================================================
void CMenu::Exec( )
{
		const int ITEM_MAX = 2;
		
		const char *pItemName[] =
		{
			"�͂�",
			"������"
		};

		m_pFontSpr->GetFontSprite()->Begin();
		
		m_pFontSpr->GetFontSprite()->DrawString( m_CaptionName.c_str(), Math::Point2DF( m_pSpr->GetPosition().x + 10, m_pSpr->GetPosition().y + 10 ), CColor( 255, 255, 255 ) );
		

		if( m_IsYesNoOrder )
		{
			
			for( int i = 0;i < ITEM_MAX;++i )
			{
				if( m_Cursor == i )
				{	
					m_pRender->SetDrawType( DRAW_TYPE_BLEND );
					
					if( m_IsPopUp )
					{	
						m_pRender->FillRect( Math::Rect2DF( m_pSpr->GetPosition().x + 20.0f, m_pSpr->GetPosition().y + toF( i ) * 20.0f + 50.0f , toF( m_pSpr->GetWidth() ) - 30.0f , 20.0f ), CColor( 128, 128, 128, 128 ) );
					}
					
					m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
					
					m_pFontSpr->GetFontSprite()->DrawString( pItemName[i], Math::Point2DF( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 20 + 50 ), CColor( 128, 0, 0 ) );
					
					
					//m_pRender->DrawTextA( Math::Point2DI( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 30 + 40 ), CColor( 128, 0, 0 ), pItemName[i] ); 
		//			m_pRender->SetDrawType( DRAW_TYPE_MULTIPLE );
					
				}
				
				else
				{
					//m_pRender->DrawTextA( Math::Point2DI( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 30 + 40 ), CColor( 0, 0, 0 ), pItemName[i] ); 
				
					m_pFontSpr->GetFontSprite()->DrawString( pItemName[i], Math::Point2DF( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 20 + 50 ), CColor( 128, 0, 0 ) );
				}
			}
			
			//m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
			
		}
		
		//else
		//{
		//	for( int i = 0;i < ITEM_MAX;++i )
		//	{
		//		if( m_Cursor == i )
		//		{	
		//			//m_pRender->DrawTextA( Math::Point2DI( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 20 + 50 ), CColor( 255, 255, 255 ), pItemName[i] ); 
		//		
		//		//	m_pFontSpr->GetFontSprite()->DrawString( pItemName[(i+1)%ITEM_MAX], Math::Point2DF( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 20 + 50 ), CColor( 0, 0, 0 ) );
		//			
		//		}
		//		
		//		else
		//		{
		//		//	m_pFontSpr->GetFontSprite()->DrawString( pItemName[(i+1)%ITEM_MAX], Math::Point2DF( m_pSpr->GetPosition().x + 20, m_pSpr->GetPosition().y + i * 20 + 50 ), CColor( 128, 0, 0 ) );
		//		}
		//	}
		//	
		//	//m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		//	
		//}

		m_pFontSpr->GetFontSprite()->End();
		
		m_pSpr->Exec();
		
}

//=============================================================================
//�I�����̑I��
//=============================================================================
//[input]
//	pCtrl:�R���g���[���[�f�o�C�X
//[return]
//	Yes���I�����ꂽ��
//=============================================================================
eSelectType CMenu::SelectYesNo( Selene::Peripheral::IInputController *pCtrl )
{
	const int ITEM_MAX = 2;
	
	if( m_IsPopUp )
	{
		eInputButtonType eButtonUpDown = pCtrl->CursorClampUpDown( 0, m_Cursor, ITEM_MAX );
		
		if( pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
		{
			if( m_IsYesNoOrder )
			{
				if( m_Cursor == 0 )
				{
					m_IsPopUp = false;
					return SELECT_YES;	
				}
				
				else
				{
					m_IsPopUp = false;
					return SELECT_NO;
				}
			}
			
			else
			{
				if( m_Cursor == 0 )
				{
					m_IsPopUp = false;
					return SELECT_NO;
				}
				
				else
				{
					m_IsPopUp = false;
					return SELECT_YES;	
				}
			}
		}
		
		if( pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R1 ) )
		{
			m_IsPopUp = false;
			return SELECT_NO;
		}
	}
	
	return SELECT_NONE;
}



