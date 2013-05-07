//*============================================================================
//player.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "player.h"
#include <math.h>
#include "camera.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//=============================================================================
CPlayer::CPlayer( string name )
{
	m_IsVisible = true;
	
	m_pModel	= NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_vPos.Set(0, 10, -40);
	m_vRot.Set(DEG_TO_ANGLE(90), DEG_TO_ANGLE(90), 0);
	
	m_vScale.Set(2.0f, 2.0f, 2.0f);
	
	
	m_IsCameraMode = false;
	m_IsFlashMode = false;
	m_IsSetFlag	= false;
	
	m_ActorIndex = 0;
	
	m_HoldTime = 0;
	
	m_AnimID[ANIM_NOW] = 0;
	
	m_DataName = name;
	
	m_fSpeed = 0.15f;
	
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	name:�f�[�^��
//	vPos:�ʒu
//=============================================================================
CPlayer::CPlayer( string name, Math::Vector3D vPos ) : m_pCamObj(NULL)
{
	m_IsVisible = true;
	
	m_pModel	= NULL;
	m_pJoy = NULL;
	m_pCtrl = NULL;
	
	for( int numActor = 0;numActor < S_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
	}
	
	m_vPos = vPos;
	m_vOldPos = vPos;
	m_vRot.Set(DEG_TO_ANGLE(90), DEG_TO_ANGLE(90), 0);
	m_vSetFlagPos.Set( 0, 0, 0 );
	m_vRay.vStart = Math::Vector3D(0, 0, 0);
	m_vRay.vEnd = Math::Vector3D(0, 0, 0);
	
	m_vScale.Set(1.0f, 1.0f, 1.0f);
	
	m_IsCameraMode = false;
	m_IsFlashMode = false;
	m_IsSetFlag	= false;
	
	m_ActorIndex = 0;
	
	m_HoldTime = 0;
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 1.0f;
		m_AnimID[Anim] = 0;
	} 
	
	m_eType = OBJ_PLAYER;
	
	m_DataName = name;
	m_fGravity = 0.0f;
	
	//m_fSpeed = 0.15f;
	
	m_fSpeed = 0.2f;
	
	m_fWeight = 0.0f;
	
	m_eAnimState = ANIM_STANDBY;
	
	//m_fSpeed = 1.0f;
	
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
	SAFE_RELEASE( m_pJoy );
	SAFE_RELEASE( m_pCtrl );

	for( int i = 0;i < S_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorModel[i] );
	}
	
	
	SAFE_RELEASE( m_pModel );
	
}

//=============================================================================
//������
//=============================================================================
void CPlayer::Init()
{
	m_vPos = m_vOldPos;
	
	m_vRot.Set(DEG_TO_ANGLE(90), 0, 0);
	//
	//m_vScale.Set(1.0f, 1.0f, 1.0f);
	//
	m_IsCameraMode = false;
	m_IsFlashMode = false;
	m_IsSetFlag	= false;
	m_IsJumpFlag = false;
	m_IsSettingFlag = false;
	m_eAnimState = ANIM_STANDBY;
	
	
	//
	//m_ActorIndex = 0;
	//
	//m_fNowAnimTime = 1.0;
	//m_HoldTime = 0;
	//
	//m_AnimID[ANIM_NOW] = 0;
	//
}
	
//=============================================================================
//����
//=============================================================================
void CPlayer::Exec()
{
	AnimExec();
	
	/*�p���̃��Z�b�g*/		
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	m_pActorModel[m_ActorIndex]->RotationX( toI( m_vRot.y ) );
	
	m_pActorModel[m_ActorIndex]->RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE(90)  );
	
	/*�ړ��̐ݒ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	
	// �L�����ɑ΂��ăA�j���[�V�������X�V
	m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW], m_AnimID[ANIM_NEXT], m_fAnimTime[ANIM_NEXT], m_fWeight );
	
	// �L�����̕ϊ��X�V
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//�A�j���[�V�����p����
//=============================================================================
void CPlayer::AnimExec()
{
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		/*�A�j���[�V�����I������*/
		FLOAT fAnimLastTime = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] );
		
		/*���Ԃ��Ō�܂œ��B*/
		while( m_fAnimTime[Anim] > fAnimLastTime )
		{
			/*�ŏ��ɖ߂�*/
			m_fAnimTime[Anim] -= fAnimLastTime;
		}
	}
	
	if( m_eAnimState == ANIM_STANDBY )
	{
	
	}	
	
	else if( m_eAnimState == ANIM_CHANGESTART )
	{
		m_fAnimTime[ANIM_NEXT] = 0.0f;
		m_fWeight = 0.0f;
		
		m_eAnimState = ANIM_CHANGE;
	}
	
	else if( m_eAnimState == ANIM_CHANGE )
	{
		UpdateAnimation();
	}
	
	
}

//=============================================================================
//�J�������[�h����t���O�̃Z�b�g
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
//=============================================================================
void CPlayer::SetCameraModeFlag( bool flag )
{
	m_IsCameraMode = flag;
}

//=============================================================================
//�t���b�V�����[�h����t���O�̃Z�b�g
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
//=============================================================================
void CPlayer::SetFlashModeFlag( bool flag )
{
	m_IsFlashMode = flag;
}

//=============================================================================
//�R���g���[���[�f�o�C�X�̃Z�b�g
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
//=============================================================================
void CPlayer::SetController(Selene::Peripheral::IInputController *pCtrl, Peripheral::IJoystick *pJoy )
{
	m_pCtrl = pCtrl;
	
	pCtrl->AddRef();
	
	m_pJoy = pJoy;
	
	pJoy->AddRef();
}

//==============================================================================
//�A�j��ID�̐ݒ�
//==============================================================================
//[input]
//	index:�C���f�b�N�X
//	animID:�ݒ肷��A�j��ID
//==============================================================================
void CPlayer::SetAnimationID(eAnimType index, int animID)
{
	m_AnimID[index] = animID;
}

//==============================================================================
//�I�u�W�F�N�g�̐ݒu
//==============================================================================
//[input]
//	vPos:�ݒu����ʒu
//	obj:�ݒu����I�u�W�F�N�g
//==============================================================================
//void CPlayer::SetObject( CVector3 vPos, CDrawObject *obj )
//{
	//if( CWiiRemocon::GetNunAttacked() )
	//{
	//	if( CWiiRemocon::GetNunState(REM_STATE_PUSH, NUNCHUK_BUTTON_Z) )
	//	{
	//		obj->SetVisibleFlag( !obj->GetVisibleFlag() );
	//	
	//	}
	//	
	//}
	//
	//else
	//{
	//
	//	if( CJoyPad::GetState( 0, PAD_STATE_PUSH, PAD_BUTTON_01 ) )
	//	{
	//		obj->SetVisibleFlag( !obj->GetVisibleFlag() );
	//	}
	//}
//}

//==============================================================================
//�t���b�V������
//==============================================================================
//[input]
//	obj:����I�u�W�F�N�g
//	CharaMax:�L�����ő吔
//	pRender:�����_���[�p�f�o�C�X
//	pParticle:�p�[�e�B�N���G�t�F�N�g
//==============================================================================
void CPlayer::SetFlash( CCharacter *obj[], Uint32 CharaMax, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] )
{
	
	//if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_02 ) )
	//{
	//	m_HoldTime += 1;
	//	
	//	if( m_HoldTime >= 150 )
	//	{
	//		m_IsFlashMode = true;
	//	}
	//	
	//}
	#if defined( DEBUG_MAP_EDIT )
	
		if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_L1 ) )
		{
			m_vRot.x -= DEG_TO_ANGLE(1.0);
		}
		
		if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_L2 ) )
		{
			m_vRot.x += DEG_TO_ANGLE(1.0);
		}
	
	#else
		if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R1 ) )
		{
			m_IsFlashMode = true;
			/*�t���b�V��*/
			//pRender->FillRect( Math::Rect2DF( 0, 0, 800, 600 ), CColor(255, 255, 255) );
			
			//m_vRay.vStart = m_vPos + Math::Vector3D(0, 0.5, 0);
			//m_vRay.vEnd = m_vRay.vStart + vFront * 10;
			
			//CDraw3DObject *objHit = NULL;
			
			//m_pEmissionObj->SetMatWorld( matWorld );
			
				
			//Math::Vector3D vFront( 0, 0, 0 );
			//
			//this->GetModelActor(S_MAIN)->GetFront( vFront );
			//
			//Collision::CBox Box;
		
			//Math::Matrix matWorld;
			//
			//Math::Matrix matTemp;
			//
			//matTemp.Identity();
			//
			//matWorld.Identity();
			//
			//matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
			//
			//matWorld *= matTemp;
			//
			//matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
			//
			//matWorld *= matTemp;
			//
			//Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld );
			//	
			//static float PosZ = 0.0f;
			//
			//static int count = 0;
			//
			//count++;
			//
			//m_pEmissionObj->SetPosition( m_vPos + Math::Vector3D( 0, 2, 1 ) );
			//
			//if( obj->GetModelActor(S_MAIN)->Collision_Check( Box ) )
			//{
			//	obj->SetStopFlag( true );
			//}
			//
			//if( count >= 60 )
			//{
			//	count = 0;
			//	m_IsFlashMode = false;
			//} 
			
		}
		
		for( int i = 0;i < FLASH_EFFECT_NUM;++i )
		{
			if( m_IsFlashMode )
			{
				static int count = 0;
				
				const int DISTANCE = 30;
				
				count +=5;
				
				if( count >= DISTANCE*i )
				{
					pParticle[i]->SetVisibleFlag( true );
				}
				
				if( count >=  DISTANCE*FLASH_EFFECT_NUM )
				{
					count = 0;
					m_IsFlashMode = false;
				}
			
			}
			
			if( pParticle[i]->GetVisibleFlag() )
			{
				Math::Vector3D vFront( 0, 0, 0 );
				
				this->GetModelActor(S_MAIN)->GetFront( vFront );
				
				Collision::CBox Box;
			
				Math::Matrix matWorld;
				
				Math::Matrix matTemp;
				
				matTemp.Identity();
				
				matWorld.Identity();
				
				matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
				
				matWorld *= matTemp;
				
				matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
				
				matWorld *= matTemp;
				
				const float FlashRange = 5.0f;
				
				Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, FlashRange, FlashRange), matWorld );
					
				static Math::Vector3D vPos[FLASH_EFFECT_NUM];
				
				static int count = 0;
				
				count +=5;
				
				vPos[i] = m_vPos + vFront + Math::Vector3D( 0, 1.2f, 0 );
				
	/*			vPos[0].x = Interpolation::Flat( m_vPos.x , m_vPos.x + vFront.x*FlashRange, 60, count );
				vPos[0].z = Interpolation::Flat( m_vPos.z , m_vPos.z + vFront.z*FlashRange, 60, count );*/
				
				for( int flashnum = 1;flashnum < FLASH_EFFECT_NUM;++flashnum )
				{
					vPos[flashnum].x = Interpolation::Flat( vPos[flashnum-1].x , vPos[flashnum-1].x + vFront.x * flashnum, 60*flashnum, count );
					vPos[flashnum].z = Interpolation::Flat( vPos[flashnum-1].z , vPos[flashnum-1].z + vFront.z * flashnum, 60*flashnum, count );
				}
				
				
				vPos[0] = m_vPos + Math::Vector3D( 0, 1.2f, 0 );
				
				pParticle[i]->SetPosition( vPos[i] );
				
				float Scale = 2.0f - 0.2f * toF( i );
				
				pParticle[i]->SetScale( Math::Vector3D( Scale, Scale, Scale ) );
				
				static Math::Point3D<Uint8> Alpha( 180, 255, 0 );
				
				//Alpha.x = Interpolation::Sub2( Alpha.y, Alpha.z, 90, count ); 
				
				Math::Vector3D fScale( 2.0, 2.0, 0.0 );
				
				fScale.x = Interpolation::Flat( 3.0f, 3.3f, 30, count );
				fScale.y = Interpolation::Flat( 3.0f, 3.3f, 30, count );
				
				
				pParticle[0]->SetAlpha( Alpha );
				pParticle[0]->SetScale( fScale );
				
				const int DISTANCE = 60;
				
				for( int flashnum = 1;flashnum < FLASH_EFFECT_NUM;++flashnum )
				{
					if( count >= DISTANCE * flashnum )	
					{
						pParticle[flashnum]->SetVisibleFlag( false );
					}
					
				}
				
				if( count >= 180 )
				{
					pParticle[0]->SetVisibleFlag( false );
				
				}
				
				if( count >=  DISTANCE * FLASH_EFFECT_NUM )
				{
					count = 0;
					
				}
				
				for( Uint32 Chara = 0;Chara < CharaMax;++Chara )
				{
					if( obj[Chara]->GetModelActor(S_MAIN)->Collision_Check( Box ) )
					{
						obj[Chara]->SetStopFlag( true );
					}
					
				}
				
				
			}
			
		}
		
	#endif
	
	
}

//==============================================================================
//�t���b�V������
//==============================================================================
//[input]
//	obj:����I�u�W�F�N�g
//	CharaMax:�L�����ő吔
//	pRender:�����_���[�p�f�o�C�X
//	pParticle:�p�[�e�B�N���G�t�F�N�g
//==============================================================================
void CPlayer::SetFlash( CCharacter *obj, Renderer::IRender *pRender, CFlash *pParticle[FLASH_EFFECT_NUM] )
{
	Math::Vector3D vFront( 0, 0, 0 );
	
	this->GetModelActor(S_MAIN)->GetFront( vFront );
	
	Math::Vector3D vOldFront( 0, 0, 0 );

	
	//if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_02 ) )
	//{
	//	m_HoldTime += 1;
	//	
	//	if( m_HoldTime >= 150 )
	//	{
	//		m_IsFlashMode = true;
	//	}
	//	
	//}
	#if defined( DEBUG_MAP_EDIT )
	
		if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_L1 ) )
		{
			m_vRot.x -= DEG_TO_ANGLE(1.0);
		}
		
		if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_L2 ) )
		{
			m_vRot.x += DEG_TO_ANGLE(1.0);
		}
	
	#else
		if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R1 ) )
		{
			m_IsFlashMode = true;
			vOldFront = vFront;
			
		}
		
		for( int i = 0;i < FLASH_EFFECT_NUM;++i )
		{
			if( m_IsFlashMode )
			{
				static int count = 0;
				
				const int DISTANCE = 20;
				
				count ++;
				
				if( count >= DISTANCE*i )
				{
					pParticle[i]->SetVisibleFlag( true );
				}
				
				if( count >=  DISTANCE*FLASH_EFFECT_NUM )
				{
					count = 0;
					m_IsFlashMode = false;
				}
			
			}
			
			if( pParticle[i]->GetVisibleFlag() )
			{
				
				Collision::CBox Box;
			
				Math::Matrix matWorld;
				
				Math::Matrix matTemp;
				
				matTemp.Identity();
				
				matWorld.Identity();
				
				matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
				
				matWorld *= matTemp;
				
				matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
				
				matWorld *= matTemp;
				
				const float FlashRange = 3.0f;
				
				Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, FlashRange, FlashRange), matWorld );
					
				static Math::Vector3D vPos[FLASH_EFFECT_NUM];
				
				static int count = 0;
				
				count++;
				
				vPos[i] = m_vPos + vFront + Math::Vector3D( 0, 1.2f, 0 );
				
	/*			vPos[0].x = Interpolation::Flat( m_vPos.x , m_vPos.x + vFront.x*FlashRange, 60, count );
				vPos[0].z = Interpolation::Flat( m_vPos.z , m_vPos.z + vFront.z*FlashRange, 60, count );*/
				
				for( int flashnum = 1;flashnum < FLASH_EFFECT_NUM;++flashnum )
				{
					vPos[flashnum].x = Interpolation::Flat( vPos[flashnum-1].x , vPos[flashnum-1].x + vOldFront.x * flashnum, 60*flashnum, count );
					vPos[flashnum].z = Interpolation::Flat( vPos[flashnum-1].z , vPos[flashnum-1].z + vOldFront.z * flashnum, 60*flashnum, count );
				}
				
				
				vPos[0] = m_vPos + Math::Vector3D( 0, 1.2f, 0 );
				
				pParticle[i]->SetPosition( vPos[i] );
				
				float Scale = 2.0f - 0.2f * toF( i );
				
				pParticle[i]->SetScale( Math::Vector3D( Scale, Scale, Scale ) );
				
				static Math::Point3D<Uint8> Alpha( 180, 255, 0 );
				
				//Alpha.x = Interpolation::Sub2( Alpha.y, Alpha.z, 90, count ); 
				
				Math::Vector3D fScale( 2.0, 2.0, 0.0 );
				
				fScale.x = Interpolation::Flat( 3.0f, 3.3f, 30, count );
				fScale.y = Interpolation::Flat( 3.0f, 3.3f, 30, count );
				
				
				pParticle[0]->SetAlpha( Alpha );
				pParticle[0]->SetScale( fScale );
				
				const int DISTANCE = 30;
				
				for( int flashnum = 1;flashnum < FLASH_EFFECT_NUM;++flashnum )
				{
					if( count >= DISTANCE * flashnum )	
					{
						pParticle[flashnum]->SetVisibleFlag( false );
					}
					
				}
				
				if( count >= 180 )
				{
					pParticle[0]->SetVisibleFlag( false );
				
				}
				
				if( count >=  DISTANCE * FLASH_EFFECT_NUM )
				{
					count = 0;
					
				}
				
				if( obj->GetModelActor(S_MAIN)->Collision_Check( Box ) )
				{
					obj->SetStopFlag( true );
				}
					
				
				
			}
			
		}
		
	#endif
	
	
	
}


//==============================================================================
//�I�u�W�F�N�g�ւ̃t���O�ݒu
//==============================================================================
//[input]
//	pChara:�t���O��ݒu����L����
//	pSound:�t���O�ݒu��
//	pMapActor:�}�b�v�A�N�^�[
//[return]
//	�I�u�W�F�N�g�Ƀt���O��ݒu������
//==============================================================================
//bool CPlayer::SetFlagToObject( CCharacter *pChara[FLASH_CHARA_NUM], Sound::ISound *pSound, Scene::IMapActor *pMapActor )
//{
//	Math::Vector3D vCharaFront( 0, 0, 0 );
//	Math::Vector3D vCharaRight( 0, 0, 0 );
//	
//	this->GetModelActor(S_MAIN)->GetFront( vCharaFront );
//	m_pActorModel[S_MAIN]->GetRight( vCharaRight );
//
//	Collision::CBox Box;
//	
//	Math::Matrix matWorld;
//	
//	Math::Matrix matTemp;
//	
//	matTemp.Identity();
//	
//	matWorld.Identity();
//	
//	matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
//	
//	matWorld *= matTemp;
//	
//	matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
//	
//	matWorld *= matTemp;
//	
//	/*����p�{�b�N�X�̍쐬*/
//	Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
//	
//	static int count = 0;
//	
//	count++;
//	
//	//if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
//	//{
//	//	if( /*FlagCheck( pMapActor )*/  objPlayer->GetAnimationID(ANIM_NOW) == ANIM_STAND )
//	//	{
//	//		if( !objPlayer->GetSettingFlag() )
//	//		{
//	//			objPlayer->SetSettingFlag( true );
//	//		
//	//			objPlayer->SetAnimationTime( ANIM_NOW, 0.0f );
//	//		}
//	//	}
//	//	
//	//}
//	
//	if( m_IsSettingFlag )
//	{
//		for( int Anim = 0;Anim < ANIM_MAX;++Anim )
//		{
//			m_fAnimTime[Anim] += 0.5f;
//		}
//	}
//	
//	if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
//	{
//		if( /*FlagCheck( pMapActor )*/  m_AnimID[ANIM_NOW] == ANIM_STAND )
//		{
//			if( !m_IsSettingFlag )
//			{
//				m_IsSettingFlag = true;
//			
//				m_fAnimTime[ANIM_NOW] = 0.0f;
//			}
//		}
//	}
//	
//	for( int i = 0;i < FLASH_CHARA_NUM;++i )
//	{	
//		if( m_IsSettingFlag )
//		{	
//			if( pChara[i]->GetModelActor(S_MAIN)->Collision_Check( Box )  )
//			{
//				/*�Î~��Ԃ̎�*/
//				if( pChara[i]->GetStopFlag() )
//				{
//						
//					m_AnimID[ANIM_NOW] = ANIM_SET_MOVE;
//					//ChangeAnimation( ANIM_SET_MOVE );
//					
//					if( m_fAnimTime[ANIM_NOW] >= m_pActorModel[m_ActorIndex]->GetAnimationLastTime(ANIM_SET_MOVE) )
//					{
//						m_fAnimTime[ANIM_NOW] = 0.0f;
//						
//						pChara[i]->SetFlag( true );
//						/*�t���O�Z�b�g*/
//						m_IsSetFlag = true ;
//						
//						m_IsSettingFlag = false;
//						
//						pSound->Play( 0 );
//						
//						m_AnimID[ANIM_NOW] = ANIM_STAND;
//						
//						return true;
//						
//					}
//					
//					//if( count > 180 )
//					//{
//					//	count = 0;
//					//	
//						
//					//}
//
//				}	
//				
//			}
//			
//			else
//			{
//				Math::Vector3D vCharaFront;
//				
//				m_pActorModel[S_MAIN]->GetFront( vCharaFront );
//				
//				m_pFlag->SetPosition( m_vPos + vCharaFront );
//				
//				m_AnimID[ANIM_NOW] = ANIM_SET_GROUND;
//				
//				/*�t���O�Z�b�g*/
//				if( m_fAnimTime[ANIM_NOW] >= m_pActorModel[m_ActorIndex]->GetAnimationLastTime(ANIM_SET_GROUND) )
//				{
//					m_IsSetFlag = true;
//					m_AnimID[ANIM_NOW] = ANIM_STAND;
//					m_IsSettingFlag = false;
//					
//					pSound->Play( 0 );
//					
//					
//				}
//			
//			}
//			
//		}
//	}
//	
//	return false;	
//
//}

//==============================================================================
//�I�u�W�F�N�g�ւ̃t���O�ݒu
//==============================================================================
//[input]
//	pChara:�t���O��ݒu����L����
//	pSound:�t���O�ݒu��
//	pMapActor:�}�b�v�A�N�^�[
//[return]
//	�I�u�W�F�N�g�Ƀt���O��ݒu������
//==============================================================================
void CPlayer::SettingFlag()
{
	if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
	{
		if( /*FlagCheck( pMapActor )*/  m_AnimID[ANIM_NOW] == ANIM_STAND )
		{
			if( !m_IsSettingFlag )
			{
				m_IsSettingFlag = true;
			
				m_fAnimTime[ANIM_NOW] = 0.0f;
			}
		}
	}
	
	if( m_IsSettingFlag )
	{
		m_fAnimTime[ANIM_NOW] += 1.0f;
	}

}

//==============================================================================
//�I�u�W�F�N�g�ւ̃t���O�ݒu
//==============================================================================
//[input]
//	pChara:�t���O��ݒu����L����
//	pSound:�t���O�ݒu��
//	pMapActor:�}�b�v�A�N�^�[
//[return]
//	�I�u�W�F�N�g�Ƀt���O��ݒu������
//==============================================================================
bool CPlayer::SetFlagToObject( CCharacter *pChara, Sound::ISound *pSound )
{
	//Math::Vector3D vCharaFront( 0, 0, 0 );
	//Math::Vector3D vCharaRight( 0, 0, 0 );
	//
	//this->GetModelActor(S_MAIN)->GetFront( vCharaFront );
	//m_pActorModel[S_MAIN]->GetRight( vCharaRight );

	//Collision::CBox Box;
	//
	//Math::Matrix matWorld;
	//
	//Math::Matrix matTemp;
	//
	//matTemp.Identity();
	//
	//matWorld.Identity();
	//
	//matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
	//
	//matWorld *= matTemp;
	//
	//matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
	//
	//matWorld *= matTemp;
	//
	///*����p�{�b�N�X�̍쐬*/
	//Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
	//
	//static int count = 0;
	//
	//count++;
	
	//if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
	//{
	//	if( /*FlagCheck( pMapActor )*/  objPlayer->GetAnimationID(ANIM_NOW) == ANIM_STAND )
	//	{
	//		if( !objPlayer->GetSettingFlag() )
	//		{
	//			objPlayer->SetSettingFlag( true );
	//		
	//			objPlayer->SetAnimationTime( ANIM_NOW, 0.0f );
	//		}
	//	}
	//	
	//}
	
	//if( m_IsSettingFlag )
	//{
	//	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	//	{
	//		m_fAnimTime[Anim] += 0.5f;
	//	}
	//}
	
	//if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
	//{
	//	if( /*FlagCheck( pMapActor )*/  m_AnimID[ANIM_NOW] == ANIM_STAND )
	//	{
	//		if( !m_IsSettingFlag )
	//		{
	//			m_IsSettingFlag = true;
	//		
	//			m_fAnimTime[ANIM_NOW] = 0.0f;
	//		}
	//	}
	//}
	
	if( m_IsSettingFlag )
	{	
		//if( pChara->GetModelActor(S_MAIN)->Collision_Check( Box )  )
		//{
			m_AnimID[ANIM_NOW] = ANIM_SET_MOVE;
			//ChangeAnimation( ANIM_SET_MOVE );
			
			if( m_fAnimTime[ANIM_NOW] >= m_pActorModel[m_ActorIndex]->GetAnimationLastTime(ANIM_SET_MOVE) )
			{
				m_fAnimTime[ANIM_NOW] = 0.0f;
				
				pChara->SetFlag( true );
				/*�t���O�Z�b�g*/
				m_IsSetFlag = true ;
				
				m_IsSettingFlag = false;
				
				pSound->Play( 0 );
				
				m_AnimID[ANIM_NOW] = ANIM_STAND;
				
				return true;
				
			}
			
	//		/*�Î~��Ԃ̎�*/
	//		if( pChara->GetStopFlag() )
	//		{
	//				
	//			//m_AnimID[ANIM_NOW] = ANIM_SET_MOVE;
	//			////ChangeAnimation( ANIM_SET_MOVE );
	//			//
	//			//if( m_fAnimTime[ANIM_NOW] >= m_pActorModel[m_ActorIndex]->GetAnimationLastTime(ANIM_SET_MOVE) )
	//			//{
	//			//	m_fAnimTime[ANIM_NOW] = 0.0f;
	//			//	
	//			//	pChara->SetFlag( true );
	//			//	/*�t���O�Z�b�g*/
	//			//	m_IsSetFlag = true ;
	//			//	
	//			//	m_IsSettingFlag = false;
	//			//	
	//			//	pSound->Play( 0 );
	//			//	
	//			//	m_AnimID[ANIM_NOW] = ANIM_STAND;
	//			//	
	//			//	return true;
	//			//	
	//			//}
	//			
	//			//if( count > 180 )
	//			//{
	//			//	count = 0;
	//			//	
	//				
	//			//}

	//		}	
	//		
		//}
	//	
	//	else
	//	{
	//		SetFlagToGround( pSound, pMapActor );	
	//		return false;
	//	}
	//	
	}
	
	return false;	

}

//==============================================================================
//�I�u�W�F�N�g�ւ̃t���O�ݒu
//==============================================================================
//[input]
//	pSound:�t���O�ݒu��
//	pMapActor:�}�b�v�A�N�^�[
//[return]
//	�I�u�W�F�N�g�Ƀt���O��ݒu������
//==============================================================================
bool CPlayer::SetFlagToGround( Sound::ISound *pSound, CCharacter *pFlag )
{
	if( m_IsSettingFlag )
	{
		Math::Vector3D vCharaFront;
		
		m_pActorModel[m_ActorIndex]->GetFront( vCharaFront );
		
		pFlag->SetPosition( m_vPos + vCharaFront );
		
		m_AnimID[ANIM_NOW] = ANIM_SET_GROUND;
		
		/*�t���O�Z�b�g*/
		if( m_fAnimTime[ANIM_NOW] >= m_pActorModel[m_ActorIndex]->GetAnimationLastTime(ANIM_SET_GROUND) )
		{
			m_IsSetFlag = true;
			m_AnimID[ANIM_NOW] = ANIM_STAND;
			m_IsSettingFlag = false;
			
			pSound->Play( 0 );
			
		}
	}
	
	return true;
	
}


//==============================================================================
//�J�������[�h�̐؂�ւ�
//==============================================================================
//[input]
//	pSnd:�Đ�����T�E���h
//==============================================================================
void CPlayer::ChangeCameraMode( Sound::ISound *pSnd )
{
	if( m_IsSetFlag )
	{
		pSnd->Play( 0 );
		
		m_IsCameraMode = !m_IsCameraMode;
	}

}

//=============================================================================
//�A�j���[�V�����̍X�V
//=============================================================================
void CPlayer::UpdateAnimation()
{
	if( m_AnimID[ANIM_NOW] != m_AnimID[ANIM_NEXT] )
	{
		/*��b�Ő؂�ւ���*/
		m_fWeight += 1.0f / 120.0f;
		
		if( m_fWeight >= 1.0f )
		{
			m_fWeight = 0.0f;
			m_fAnimTime[ANIM_NOW] = m_fAnimTime[ANIM_NEXT];
			m_AnimID[ANIM_NOW] = m_AnimID[ANIM_NEXT];
			m_eAnimState = ANIM_STANDBY;
		}
	}
}

//=============================================================================
//�A�j���[�V�����̐ݒ�
//=============================================================================
//[input]
//	animID:�ݒ肷��A�j���[�V����ID
//=============================================================================
void CPlayer::ChangeAnimation( int animID )
{
	m_AnimID[ANIM_NEXT] = animID;
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pCam:�J����
//	pParticle:�p�[�e�B�N��
//==============================================================================
void CPlayer::Move( CCamera *pCam, CParticle *pParticle[RUN_EFFECT_NUM] )
{
	//------------------------------------------------
	// �J������̕������擾
	//------------------------------------------------
	Math::Vector3D vCameraFront, vCameraRight;
	// �O
	pCam->GetStyle().GetFront( vCameraFront );
	// �����͍l�����Ȃ�
	vCameraFront.y = 0.0f;
	vCameraFront.Normalize();
	// �E
	pCam->GetStyle().GetRight( vCameraRight );
	// �����͍l�����Ȃ�
	vCameraRight.y = 0.0f;
	vCameraRight.Normalize();
	
	Math::Vector3D vCharaFront( 0, 0, 0 );
	Math::Vector3D vCharaRight( 0, 0, 0 );
	
	m_pActorModel[S_MAIN]->GetFront( vCharaFront );
	m_pActorModel[S_MAIN]->GetRight( vCharaRight );
	
	static const Float Sqrt2 = sqrtf( 2.0f );
	
	m_vDirection.Set( 0.0, 0.0f, 0.0f );
	
	const float AXIS_MAX = 4096;
	const float AXIS_MIN = -4096;
	
	Math::Vector2D AxisPos( toF( m_pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_X ) / AXIS_MAX ), toF( m_pJoy->GetAxis( PAD_AXIS_POSITION, PAD_AXIS_Y ) / AXIS_MAX ) );
	
	Math::Vector3D vOldDir = m_vRot;
	Math::Vector3D vDesiredDir( 0.0f, 0.0f, 0.0f );
	
	#if defined(DEBUG_MAP_EDIT) 
	
		if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_CIRCLE ) )
		{
			m_vPos.y += 0.5f;	
		}
		
		else if( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_CROSS ) )
		{
			m_vPos.y -= 0.5f;
		}
		
	#elif defined( DEBUG_MAP_EDIT )
	
	#endif
	
	/*�ړ��␳*/
	MoveAdjust();
	
	for( int i = 0;i < RUN_EFFECT_NUM;++i )
	{	
		pParticle[i]->Rendering( m_ActorIndex );
	}
	
	
		#if defined ( DEBUG_MAP_SEE )
		
		#elif defined( DEBUG_MAP_EDIT )
		
		if( !m_IsCameraMode )
		{
		
		
			m_pActorModel[m_ActorIndex]->GetFront( vCameraFront );
			m_pActorModel[m_ActorIndex]->GetRight( vCameraRight );
			
			vCameraFront.Normalize();
			
			vCameraRight.Normalize();
			
			
			/*�O(�󂭓|�����Ƃ�)*/
			if(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -0.7 && AxisPos.y < -0.3) )
			{
				//m_vDirection.x =  ( ( -AxisPos.y ) * vCameraFront.x );
				//
				//m_vDirection.z =  ( ( -AxisPos.y ) * vCameraFront.z );
				//m_vDirection.Normalize();
				
				//m_vDirection = -vCameraFront;
				m_vDirection = Math::Vector3D( 0, 0, 1 );
				
				static int count = 0;
				
				m_fSpeed = 0.2f;
				
				count++;
				
				//m_fNowAnimTime ++; //= Interpolation::Flat( 1.0f, m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[ANIM_NOW] ), 50, count );
				//m_fNextAnimTime ++;
				
				if( count >= 50 )
				{
					count = 0;
				}
				
				//if( count > 0 && count <= 30 )
				//{
				//	m_fNowAnimTime += 1.0f;	
				//		m_fNowAnimTime = 6.0f;
				//}
				//
				//ef( count > 30 && count <= 60 )			
				//{
				//	m_fNowAnimTime = 21.0f;
				//}
				//
				//ef( count > 60)
				//{
				//	count = 0;
				//}
				m_AnimID[ANIM_NOW] = ANIM_WALK;
				
				//SetAnimState( ANIM_CHANGESTART );
				
				for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				{
					m_fAnimTime[Anim] += 0.5f;
				}
				
				
			}
			
			//�O(�[���|�����Ƃ�)
			ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
			{
				//m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
				//
				//m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
				//m_vDirection.Normalize();
				
				static int count = 0;
				
				m_fSpeed = 0.3f;
				
				count++;
				
				//m_vDirection = -vCameraFront;
				m_vDirection = Math::Vector3D( 0, 0, 1 );
				
				
			 //= Interpolation::Flat( 1.0f, m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[ANIM_NOW] ), 50, count );
				
				
				//m_fNowAnimTime = Interpolation::Flat( 1.0f, m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[ANIM_NOW] ), 100, count );
				
				if( count >= 100 )
				{
					count = 0;
				}
				
				//if( count > 0 && count <= 30 )
				//{
				//	m_fNowAnimTime += 1.0f;	
				//		m_fNowAnimTime = 6.0f;
				//}
				//
				//ef( count > 30 && count <= 60 )			
				//{
				//	m_fNowAnimTime = 21.0f;
				//}
				//
				//ef( count > 60)
				//{
				//	count = 0;
				//}
				
				m_AnimID[ANIM_NOW] = ANIM_RUN;
				
				for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				{
					m_fAnimTime[Anim] += 0.7f;
				}
				
				
				
				//SetAnimState( ANIM_CHANGESTART );
				
			}
			
			
			/*��*/
			ef( ( AxisPos.x >= -0.2 && AxisPos.x <= 0.2 ) && ( AxisPos.y <= 1.0 && AxisPos.y > 0.7) )
			{
				Math::Vector3D Vec(0, 0, 0);
				
				this->GetModelActor(S_MAIN)->GetFront( Vec );
				
				m_fSpeed = 0.2f;
				
				
				//m_vRot.x -= DEG_TO_ANGLE(180);				
				
				//m_vDirection = +vCameraFront;
				m_vDirection = Math::Vector3D( 0, 0, -1 );
				
				//m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x * 0.01);
				//
				//m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z * 0.01 );
				//
				////m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
				//
				//m_vDirection.Normalize();
				
				for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				{
					m_fAnimTime[Anim] += 0.5f;
				}
				
				
				m_AnimID[ANIM_NOW] = ANIM_RUN;
				
				//SetAnimState( ANIM_CHANGESTART );
			
			}
			
			/*��*/
			ef( ( AxisPos.x <= -0.4 && AxisPos.x >= -1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
			{
				//m_vDirection.x = -vCameraRight.x;
				//m_vDirection.z = 
				//
				//m_vRot.x += DEG_TO_ANGLE(1.5);
				
				//m_vDirection = +vCameraRight;
				m_vDirection = Math::Vector3D( -1, 0, 0 );
				
				for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				{
					m_fAnimTime[Anim] += 0.5f;
				}
				
				
					m_AnimID[ANIM_NOW] = ANIM_RUN;
					
					//SetAnimState( ANIM_CHANGESTART );
				
				//m_fNowAnimTime += 1.0f;
				//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1 ) + ( -AxisPos.y ) * vCameraFront.x );
				//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1 ) + ( -AxisPos.y ) * vCameraFront.z );
				//m_vDirection.y = 0;
				//
				//m_vDirection.Normalize();
				
				//m_vDirection.x =  ( ( -vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
				//m_vDirection.z =  ( ( -vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
				
			}
			
			/*�E*/
			ef( ( AxisPos.x >= 0.4 && AxisPos.x <= 1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
			{
				//m_vDirection = -vCameraRight;
				m_vDirection = Math::Vector3D( 1, 0, 0 );
				
				
				//m_vRot.x -= DEG_TO_ANGLE(1.5);
				
				for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				{
					m_fAnimTime[Anim] += 0.5f;
				}
				
				
					m_AnimID[ANIM_NOW] = ANIM_RUN;
					
				//	SetAnimState( ANIM_CHANGESTART );
				
							
				
				//m_fNowAnimTime += 1.0f;
				
				//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.x*/ );
				//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.01 ) /*+ ( -AxisPos.y ) * vCameraFront.z*/ );
				
			}
			
			
			/*���̑�*/
			ef( ( AxisPos.y <= -0.3 ) && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
			{
				//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
				//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
				//m_vDirection.y = 0;
				//
				//m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
				//
				//m_AnimID[ANIM_NOW] = ANIM_RUN;
				//
				//	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
				//{
				//	m_fAnimTime[Anim] += 0.5f;
				//}
			
				//
				////SetAnimState( ANIM_CHANGESTART );
				//
				//
				//if( AxisPos.x < 0.0 )
				//{
				//	//m_fNowAnimTime = 21.0f;
				//}
				//
				//else
				//{
				//	//m_fNowAnimTime = 6.0f;
				//}
				//
				//
				//m_vDirection.Normalize();
			}
			
			ef( AxisPos.y >= 0.3 && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
			{
				//m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
				//m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
				//m_vDirection.y = 0;

				//m_vDirection.Normalize();
				
				
			}
			
			else
			{
				if( m_AnimID[ANIM_NOW] == ANIM_SET_MOVE || m_AnimID[ANIM_NOW] == ANIM_SET_GROUND )
				{
				
				}
				
				else
				{
					m_AnimID[ANIM_NOW] = ANIM_STAND;
					
					//SetAnimState( ANIM_CHANGESTART );
						
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
				}
					

			}
			
		}
			
		#else
			
			//�p�b�h�p
			/*�O(�󂭓|�����Ƃ�)*/
			if(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -0.7 && AxisPos.y < -0.3) )
			{
				if( !m_IsCameraMode)
				{
					m_vDirection.x =  ( ( -AxisPos.y ) * vCameraFront.x );
					
					m_vDirection.z =  ( ( -AxisPos.y ) * vCameraFront.z );
					m_vDirection.Normalize();
					
					static int count = 0;
					
					m_fSpeed = 0.2f;
					
					count++;
					
					if( count >= 50 )
					{
						count = 0;
					}
					
					m_AnimID[ANIM_NOW] = ANIM_WALK;
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
				}
				
			}
			
			//�O(�[���|�����Ƃ�)
			ef(  ( AxisPos.x >= -0.5 && AxisPos.x <= 0.5 ) && ( AxisPos.y >= -1.0 && AxisPos.y < -0.7) )
			{
				if( !m_IsCameraMode )
				{

					m_vDirection.x =  ( /*( AxisPos.x * vCameraRight.x )*/ + ( -AxisPos.y ) * vCameraFront.x );
					
					m_vDirection.z =  ( /*( AxisPos.x * vCameraRight.z )*/ + ( -AxisPos.y ) * vCameraFront.z );
					
					m_fSpeed = 0.3f;
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.7f;
					}
				}
				
			}
			
			
			/*��*/
			ef( ( AxisPos.x >= -0.3 && AxisPos.x <= 0.3 ) && ( AxisPos.y <= 1.0 && AxisPos.y > 0.7) )
			{
				if( !m_IsCameraMode )
				{
					Math::Vector3D Vec(0, 0, 0);
					
					this->GetModelActor(S_MAIN)->GetFront( Vec );
					
					m_fSpeed = 0.2f;
					
					m_vDirection = -Vec;
					m_vDirection = -vCameraFront;
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}

			}
			
			/*��*/
			ef( ( AxisPos.x <= -0.4 && AxisPos.x >= -1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
			{
				if( !m_IsCameraMode )
				{
					m_vRot.x += DEG_TO_ANGLE(1.5);
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}
					
			}
			
			/*�E*/
			ef( ( AxisPos.x >= 0.4 && AxisPos.x <= 1.0 ) && ( AxisPos.y <= 0.4 && AxisPos.y > -0.4 )  )
			{
				if( !m_IsCameraMode )
				{
				
					m_vRot.x -= DEG_TO_ANGLE(1.5);
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}
					
			}
			
			
			/*���̑�*/
			//ef( ( AxisPos.y <= -0.3 ) && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
			//{
			//	if( !m_IsCameraMode )
			//	{
			//		m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
			//		m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
			//		m_vDirection.y = 0;
			//		
			//		m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
			//		
			//		m_AnimID[ANIM_NOW] = ANIM_RUN;
			//		
			//		for( int Anim = 0;Anim < ANIM_MAX;++Anim )
			//		{
			//			m_fAnimTime[Anim] += 0.5f;
			//		}
			//	
			//		m_vDirection.Normalize();
			//	}
			//}
			//
			//ef( AxisPos.y >= 0.3 && ( AxisPos.x <= -0.3 || AxisPos.x >= 0.3 ) )
			//{
			//	if( !m_IsCameraMode )
			//	{
			//		m_vDirection.x =  ( ( AxisPos.x * vCameraRight.x * 0.1f ) + ( -AxisPos.y ) * vCameraFront.x );
			//		m_vDirection.z =  ( ( AxisPos.x * vCameraRight.z * 0.1f ) + ( -AxisPos.y ) * vCameraFront.z );
			//		m_vDirection.y = 0;
			//		
			//		//m_vRot.x = toF( Math::ATan2( -m_vDirection.x, -m_vDirection.z ) );
			//		
			//		m_AnimID[ANIM_NOW] = ANIM_RUN;
			//		
			//		for( int Anim = 0;Anim < ANIM_MAX;++Anim )
			//		{
			//			m_fAnimTime[Anim] += 0.5f;
			//		}
			//		
			//		m_vDirection.Normalize();
			//	}
			//	
			//}
			
			//else
			//{
			//	if( m_AnimID[ANIM_NOW] == ANIM_SET_MOVE || m_AnimID[ANIM_NOW] == ANIM_SET_GROUND )
			//	{
			//	
			//	}
			//	
			//	else
			//	{
			//		if( !m_IsJumpFlag )
			//		{	
			//			m_AnimID[ANIM_NOW] = ANIM_STAND;
			//		}
			//		
			//		for( int Anim = 0;Anim < ANIM_MAX;++Anim )
			//		{
			//			m_fAnimTime[Anim] += 0.5f;
			//		}
			//	}
			//		

			//}
			
			//�L�[�{�[�h�p
			
			//�O
			if(  m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP ) )
			{
				if( !m_IsCameraMode )
				{

					m_vDirection = vCameraFront;
										
					m_fSpeed = 0.3f;
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.7f;
					}
				}
				
			}
			
			
			/*��*/
			ef( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) )
			{
				if( !m_IsCameraMode )
				{
					Math::Vector3D Vec(0, 0, 0);
					
					this->GetModelActor(S_MAIN)->GetFront( Vec );
					
					m_fSpeed = 0.2f;
					
					m_vDirection = -vCameraFront;
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}

			}
			
			/*��*/
			ef( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT )  )
			{
				if( !m_IsCameraMode )
				{
					m_vRot.x += DEG_TO_ANGLE(1.5);
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}
					
			}
			
			/*�E*/
			ef( m_pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT )  )
			{
				if( !m_IsCameraMode )
				{
				
					m_vRot.x -= DEG_TO_ANGLE(1.5);
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
					
					
					m_AnimID[ANIM_NOW] = ANIM_RUN;
				}
					
			}
			
			
			else
			{
				if( m_AnimID[ANIM_NOW] == ANIM_SET_MOVE || m_AnimID[ANIM_NOW] == ANIM_SET_GROUND )
				{
				
				}
				
				else
				{
					if( !m_IsJumpFlag )
					{	
						m_AnimID[ANIM_NOW] = ANIM_STAND;
					}
					
					for( int Anim = 0;Anim < ANIM_MAX;++Anim )
					{
						m_fAnimTime[Anim] += 0.5f;
					}
				}
					

			}
			

			
		#endif
		
		if( m_AnimID[ANIM_NOW] == ANIM_RUN )
		{
			float fLastTime = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( ANIM_RUN );
			
			//if( m_fAnimTime[ANIM_NOW] >= fLastTime % 3 && m_fAnimTime[ANIM_NOW] <= fLastTime % 2 )
			//{
			//	pParticle[0]->SetPosition( m_vPos + vCharaRight * 0.2 );
			//	pParticle[0]->SetVisibleFlag( true );
			//	//pParticle[1]->SetPosition( m_vPos + vCharaRight * 0.2 );
			//	//pParticle[1]->SetVisibleFlag( true );
			//	
			//}
			//
			//if( m_fAnimTime[ANIM_NOW] >= fLastTime % 4  && m_fAnimTime[ANIM_NOW] <= 17.0f )
			//{
			//
			//}
			
			
			
			
		}
		
		
		for( int i = 0;i < RUN_EFFECT_NUM;++i )
		{
			if( pParticle[i]->GetVisibleFlag() )
			{
				static int count = 0;
				
				static Math::Vector3D vPos[RUN_EFFECT_NUM];
				
				count++;
				
				Math::Point3D<Uint8> Alpha[RUN_EFFECT_NUM];
				
				Alpha[i].x = 255;
				Alpha[i].y = 255;
				Alpha[i].z = 0;
				
				const int COUNT_MAX = 180;
				
				Alpha[i].x = Interpolation::Flat( Alpha[i].y, Alpha[i].z, COUNT_MAX, count );
				vPos[i].x = Interpolation::Flat( 0.0f, -vCharaFront.x * 2.0f, COUNT_MAX, count );
				vPos[i].z = Interpolation::Flat( 0.0f, -vCharaFront.z * 2.0f, COUNT_MAX, count );
				
				Math::Vector3D Scale;
				
				Scale.x = ::Interpolation::Flat( 0.5f, 1.0f, 30, count);
				Scale.y = ::Interpolation::Flat( 0.5f, 1.0f, 30, count);
				
				
				pParticle[i]->SetAlpha( Alpha[i] );
				
				pParticle[0]->SetPosition( m_vPos );
				pParticle[2]->SetPosition( m_vPos );
				
				pParticle[0]->SetScale( Scale );
				pParticle[2]->SetScale( Scale );
				
				pParticle[1]->SetPosition( Math::Vector3D( pParticle[0]->GetPosition().x + vPos[0].x, pParticle[0]->GetPosition().y, pParticle[0]->GetPosition().z + vPos[0].z ) );
				pParticle[3]->SetPosition( Math::Vector3D( pParticle[2]->GetPosition().x + vPos[2].x, pParticle[2]->GetPosition().y, pParticle[2]->GetPosition().z + vPos[2].z ) );
				
				
				if( count >= COUNT_MAX )
				{
					count = 0;
					pParticle[i]->SetVisibleFlag( false );
				}
				
			}
			
			
			pParticle[i]->Exec();
		
		}
		
		
		//if( IsTurn )
		//{
		//	static int count = 0;
		//	
		//	
		//	if(++count > 30 )
		//	{
		//		count = 0;
		//		IsTurn = false;
		//	}
		//	
		//	
		//}
		
	
	

}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pCtrl:�R���g���[���[�p�f�o�C�X
//	vDir:����
//==============================================================================
//void CPlayer::Move( CScene *pScene )
//{
//	CCamera *objCamMain	= dynamic_cast<CCamera *>( pScene->GetGameObject()->FindObjectFromName("CamMain") );
//	
//	
//	Math::Vector3D vCameraFront, vCameraRight;
//	// �O
//	objCamMain->GetStyle().GetFront( vCameraFront );
//	// �����͍l�����Ȃ�
//	vCameraFront.y = 0.0f;
//	vCameraFront.Normalize();
//	// �E
//	objCamMain->GetStyle().GetRight( vCameraRight );
//	// �����͍l�����Ȃ�
//	vCameraRight.y = 0.0f;
//	vCameraRight.Normalize();
//		
//	static const Float Sqrt2 = sqrtf( 2.0f );
//	
//	m_vDirection.Set( 0.0, 0.0f, 0.0f );
//	
//	Math::Vector3D vAxisX( m_vRot.x, 0, 0 );
//	
//	if( !m_IsCameraMode )
//	{
//		////���O
//		//if( pScene->GetJoyPad() ( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP ) && pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT ) )
//		//{
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	
//		//	m_vDirection = (+vDir + -vAxisX) / Sqrt2;
//		//	
//		//}
//		//
//		////�E�O
//		//ef( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP ) && pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
//		//{
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	
//		//	m_vDirection = (+vDir + vAxisX) / Sqrt2;
//		//	
//		//}
//
//		////����
//		//ef( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) && pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
//		//{
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	
//		//	m_vDirection = (-vDir + -vAxisX) / Sqrt2;
//		//	
//		//}
//
//		////���O
//		//if( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP ) && pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
//		//{
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	
//		//	m_vDirection = (-vDir + vAxisX) / Sqrt2;
//		//	
//		//}
//		//
//		////�O
//		//if ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP )  )
//		//{
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	// �ړ��̓J�����ɑ΂��čs��
//		//	m_vDirection = +vDir;
//		//	m_fNowAnimTime += 1.0f;
//		//	
//		//}
//		//// ��
//		//ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) )
//		//{
//		//	// �ړ��̓J�����ɑ΂��čs��
//		//	m_AnimID[ANIM_NOW] = 0;
//		//	m_vDirection = -vDir;
//		//	m_fNowAnimTime += 1.0f;
//		//	
//		//}
//		//// �E
//		//ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
//		//{
//		//	// �ړ��̓J�����ɑ΂��čs��
//		//	//vCharaDirection = +vCameraRight;
//		//	m_vRot.x -= DEG_TO_ANGLE(1);
//		//	m_AnimID[ANIM_NOW] = 2;
//		//	//CharaData[1].AngleY += DEG_TO_ANGLE(1);
//		//	m_fNowAnimTime += 1.0f;
//		//	
//		//}
//		//// ��
//		//ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT ) )
//		//{
//		//	// �ړ��̓J�����ɑ΂��čs��
//		//	//CharaData[1].AngleY -= DEG_TO_ANGLE(1);
//		//	m_vRot.x += DEG_TO_ANGLE(1);
//		//	m_AnimID[ANIM_NOW] = 2;
//		//	//vCharaDirection = -vCameraRight;
//		//	m_fNowAnimTime += 1.0f;
//		//	
//		//}
//		//
//	}
//
//}
//

//==============================================================================
//�n�ʕ␳(�v���C���[��Y���W�����ȉ��ɂȂ����Ƃ��������W�ɖ߂��Ă��)
//==============================================================================
void CPlayer::GroundAdjust()
{
	if( m_vPos.y <= -200.0f )
	{
		m_vPos = m_vOldPos;
	}
}


//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	pCtrl:�R���g���[���[�p�f�o�C�X
//==============================================================================
void CPlayer::Move(  )
{
	//if( m_IsFlashMode )
	//{
	//	if ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_UP )  )
	//	{
	//		m_vRot.y -= DEG_TO_ANGLE(1);	
	//	}
	//	// ��
	//	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_DOWN ) )
	//	{
	//		m_vRot.y += DEG_TO_ANGLE(1);	
	//	}
	//	
	//	// �E
	//	if ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_RIGHT ) )
	//	{
	//		m_vRot.x -= DEG_TO_ANGLE(1);
	//	}
	//	// ��
	//	ef ( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_AXIS1_LEFT ) )
	//	{
	//		m_vRot.x += DEG_TO_ANGLE(1);
	//	}
	//}
	//
	//else
	//{
	//	m_vRot.y = 0;
	//}

}

//==============================================================================
//�ړ��`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N����}�b�v�A�N�^�[
//[return]
//	�ړ���ɏ�Q�������邩
//==============================================================================
bool CPlayer::MoveCheck( Scene::IMapActor *pActor )
{
	Renderer::SCollisionResultExtend RetEx;
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay[6];
	
	Collision::CBox Box;
	
	Math::Vector3D vCharaFront(0, 0, 0);
	Math::Vector3D vCharaRight;
	
	this->GetModelActor(S_MAIN)->GetFront( vCharaFront );
	m_pActorModel[S_MAIN]->GetRight( vCharaRight );
	
	//if ( m_vDirection.Length() > 0.0f )
	//{
		// �i�s�����֌�����
		//CharaData[0].TargetAngle = Math::ATan2( vCharaDirection.x, vCharaDirection.z );
		
		
		//m_vRot *= 0.1f;
		
		//m_vRot.Normalize();
		

		// �ړ���
		m_vDirection *= m_fSpeed;
		//------------------------------------------------
		// �ړ��Ɋւ��Ẵ}�b�v�ƃR���W���������
		//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
		//------------------------------------------------

		Math::Vector3D vMove = m_vDirection;
		Math::Vector3D vPos = m_vPos;
		Sint32 Limit = 200;
		
		vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.2f;
		vRay[0].vEnd   = vRay[0].vStart + vMove;
		
		vRay[1].vStart = vRay[0].vStart ;
		vRay[1].vEnd   = vRay[0].vStart + vMove + vCharaRight * 0.2f;
		
		vRay[2].vStart = vRay[0].vStart ;
		vRay[2].vEnd   = vRay[2].vStart + vMove - vCharaRight * 0.2f;
		
		vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.1f;
		vRay[3].vEnd   = vRay[3].vStart + vMove;
		
		vRay[4].vStart = vRay[3].vStart;
		vRay[4].vEnd   = vRay[4].vStart + vMove + vCharaRight * 0.1f;
		
		vRay[5].vStart = vRay[3].vStart;
		vRay[5].vEnd   = vRay[5].vStart + vMove - vCharaRight * 0.1f;
		
		
		//vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos - vCharaFront.Normalize();
		//vRay[3].vEnd   = vRay[0].vStart + vMove;
		
		m_vRay.vStart = vRay[0].vStart;
		m_vRay.vEnd = vRay[0].vEnd;
		
		
		//for ( ; ; )
		//{
			#if defined(DEBUG_MAP)
			
			#elif defined(DEBUG_MAP_EDIT)
			
					m_vPos += vMove;
					
					//break;
				
			
			#else
			
				
					//if( pActor->HitCheckByRay()
					
					if ( pActor->HitCheckByRay( vRay[0], RetEx ) || 
						 pActor->HitCheckByRay( vRay[1], RetEx ) || 
						 pActor->HitCheckByRay( vRay[2], RetEx ) ||
						 pActor->HitCheckByRay( vRay[3], RetEx ) ||
						 pActor->HitCheckByRay( vRay[4], RetEx ) ||
						 pActor->HitCheckByRay( vRay[5], RetEx )  )
					{
							// �Փˈʒu�Ɉړ�
							Math::Vector3D RetPos = RetEx.vSlidePosition + (RetEx.vNormal * 0.03f);
							vMove = RetPos - vPos;
							vMove.y = 0.0f;
							//vMove.Set( 0.0, 0.0, 0.0 );
							m_fSpeed = 0.0f;
						
						return true;				
					}
					
					else
					{
						// �ړ�
						m_vPos += vMove;
							//IsHit = false;
						
					}
			#endif
			
			//// ���E���˔j
			//if ( --Limit ==  0 )
			//{
			//	// �ǂ�����Ă����܂�̂ňړ������ɒE�o
			//	break;
			//}
		//}
			
		
	//}
	
	return false;
}

//==============================================================================
//�ړ��`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N���郂�f���A�N�^�[
//[return]
//	�ړ���ɏ�Q�������邩
//==============================================================================
bool CPlayer::MoveCheck( Scene::IModelActor *pActor )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	Math::Vector3D vCharaFront;//�L�����̑O��
	
	m_pActorModel[m_ActorIndex]->GetFront( vCharaFront );
	
	
	//if ( m_vDirection.LengthSq() > 0.0f )
	//{
		// �ړ���
		m_vDirection *= m_fSpeed;
		
		//------------------------------------------------
		// �ړ��Ɋւ��Ẵ}�b�v�ƃR���W���������
		//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
		//------------------------------------------------
		// �R���W���������΍�Ń��[�v
		Math::Vector3D vMove = m_vDirection;
		Math::Vector3D vPos = m_vPos;
		Sint32 Limit = 10;
		
		
		for ( ; ; )
		{
			vRay.vStart = Math::Vector3D(0.0f,0.8f,0.0f) + m_vPos;
			vRay.vEnd   = vRay.vStart + vCharaFront * 0.5;
			
			if ( pActor->HitCheckByRay( vRay, RetEx ) )
			{
				// �Փˈʒu�Ɉړ�
				if( RetEx.Attribute == 1 )
				{	
					m_vPos = RetEx.vHitPosition - Math::Vector3D( 0, 0, -1 );
					//Math::Vector3D RetPos = RetEx.vSlidePosition + (RetEx.vNormal * 0.01f);
					//RetEx.
					//vMove = RetPos - vPos;
					//vMove.y = 0.0f;
				}
				
				return true;				
			}
			
			else
			{
				// �ړ�
				if( !m_IsFlashMode )	
				{
					m_vPos += vMove;
					//IsHit = false;
					
				}
				
				break;
				
			}
			
			// ���E���˔j
			if ( --Limit ==  0 )
			{
				// �ǂ�����Ă����܂�̂ňړ������ɒE�o
				break;
			}
		}
//	}
	
	
	return false;
}

//==============================================================================
//�ړ��`�F�b�N
//==============================================================================
//[input]
//	pChara:�`�F�b�N����L����
//[return]
//	�ړ���ɏ�Q�������邩
//==============================================================================
bool CPlayer::MoveCheck( CCharacter *pChara )
{
	Renderer::SCollisionResultExtend RetEx;
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay[6];
	
	Collision::CBox Box;
	
	Math::Vector3D vCharaFront(0, 0, 0);
	Math::Vector3D vCharaRight;
	
	this->GetModelActor(S_MAIN)->GetFront( vCharaFront );
	m_pActorModel[S_MAIN]->GetRight( vCharaRight );
	
	
	//if ( m_vDirection.LengthSq() > 0.0f )
	//{
		// �ړ���
		m_vDirection *= m_fSpeed;
		
		//------------------------------------------------
		// �ړ��Ɋւ��Ẵ}�b�v�ƃR���W���������
		//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
		//------------------------------------------------
		// �R���W���������΍�Ń��[�v
		Math::Vector3D vMove = m_vDirection;
		Math::Vector3D vPos = m_vPos;
		Sint32 Limit = 10;
		
		vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.2f;
		vRay[0].vEnd   = vRay[0].vStart + vMove;
		
		vRay[1].vStart = vRay[0].vStart ;
		vRay[1].vEnd   = vRay[0].vStart + vMove + vCharaRight * 0.2f;
		
		vRay[2].vStart = vRay[0].vStart ;
		vRay[2].vEnd   = vRay[2].vStart + vMove - vCharaRight * 0.2f;
		
		vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.1f;
		vRay[3].vEnd   = vRay[3].vStart + vMove;
		
		vRay[4].vStart = vRay[3].vStart;
		vRay[4].vEnd   = vRay[4].vStart + vMove + vCharaRight * 0.1f;
		
		vRay[5].vStart = vRay[3].vStart;
		vRay[5].vEnd   = vRay[5].vStart + vMove - vCharaRight * 0.1f;
		
		
		
		//for ( ; ; )
		//{
				
			if( pChara->GetVisibleFlag() )
			{
			
				if ( pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[0], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[1], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[2], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[3], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[4], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[5], RetEx )  )
				{
					// �Փˈʒu�Ɉړ�
					Math::Vector3D RetPos = RetEx.vSlidePosition + (RetEx.vNormal * 0.03f);
					vMove = RetPos - vPos;
					vMove.y = 0.0f;
					//vMove.Set( 0.0, 0.0, 0.0 );
					m_fSpeed = 0.0f;
					
					return true;				
				}
				
				else
				{
					// �ړ�
					m_vPos += vMove;
						//IsHit = false;
					
				}
			
				
				//if ( this->GetModelActor(S_MAIN)->Collision_Check( pChara->GetModelActor(S_MAIN) )  )
				//{
				//	//m_fSpeed = 0.0f;
				//	//
				//	//m_vDirection.Set( 0, 0, 0 );
				//	//
				//	m_vPos = (pChara->GetPosition() - m_vPos);
				//	
				//	
				//	vMove.Set( 0.0, 0.0, 0.0 );
				//	
				//	return true;				
				//}
				//
				//else
				//{
				//	m_vPos += vMove;
				//		
				//	break;
				//	
				//}
			}
			
			//// ���E���˔j
			//if ( --Limit ==  0 )
			//{
			//	// �ǂ�����Ă����܂�̂ňړ������ɒE�o
			//	break;
			//}
		
	//}
	
	
	return false;
}


//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CPlayer::GroundCheck( CCharacter *pChara, int index )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	
	//if ( m_fGravity > 1.0f )
	//{
	//	// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.8f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(index)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// �Փˈʒu�Ɉړ�
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
			
			//m_vDirection += pChara->GetSpeed();
			// �d�͉���������
			m_fGravity = 0.0f;
		}
		
		return true;
	}
	
	return false;

}


//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N����}�b�v�A�N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CPlayer::GroundCheck( CField *pField )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
		m_fGravity = 1.0f;
		
	}
	
	//m_AnimID[ANIM_NOW] = ANIM_FALL_START;
	//m_IsJumpFlag = true;
	//m_AnimID[ANIM_NOW] = ANIM_FALL;


	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	#if defined(DEBUG_MAP_EDIT)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.8f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pField->GetMapActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( m_IsJumpFlag )
		{
			m_AnimID[ANIM_NOW] = ANIM_FALL_END;
			
			static float fCount = 1.0f;
			
			m_fAnimTime[ANIM_NOW] = fCount;
			
			fCount++;
			
			if( m_fAnimTime[ANIM_NOW] > m_pActorModel[S_MAIN]->GetAnimationLastTime( ANIM_FALL_END ) )
			{
				fCount = 1.0f;
				m_IsJumpFlag = false;
			}
			
		}
		
		// �Փˈʒu�Ɉړ�
		m_vPos = RetEx.vHitPosition;
		// �d�͉���������
		m_fGravity = 0.0f;

		return true;
	}
	
	else
	{
		if( m_vPos.y >= RetEx.vHitPosition.y + 0.5 )
		{
			m_IsJumpFlag = true;
		}
		
		if( m_IsJumpFlag )
		{
			m_AnimID[ANIM_NOW] = ANIM_FALL;
		}
	}
	
	return false;

}

//==============================================================================
//�t���O�ݒu�`�F�b�N
//==============================================================================
//[input]
//	pMapActor:�}�b�v�A�N�^�[
//[return]
//	�ړ���ɏ�Q�������邩
//==============================================================================
bool CPlayer::FlagCheck( Scene::IMapActor *pMapActor )
{
	const int RAY_NUM = 9;
	
	Renderer::SCollisionResultExtend RetEx;
	
	Math::Vector3D vCharaFront(0, 0, 0);
	Math::Vector3D vCharaRight;
	
	this->GetModelActor(S_MAIN)->GetFront( vCharaFront );
	m_pActorModel[S_MAIN]->GetRight( vCharaRight );
	
	
	Math::Vector3D vMove = m_vDirection;
	Math::Vector3D vPos = m_vPos;
	
	Collision::CLine3D vRay[RAY_NUM];
	
	vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos ;
	vRay[0].vEnd   = m_vPos + vCharaFront * 0.2f;
	
	vRay[1].vStart = vRay[0].vStart ;
	vRay[1].vEnd   = vRay[0].vEnd + vCharaRight * 0.2f;
	
	vRay[2].vStart = vRay[0].vStart ;
	vRay[2].vEnd   = vRay[0].vEnd  - vCharaRight * 0.2f;
	
	vRay[3].vStart = m_vPos + Math::Vector3D( 0.0f,0.8f, 0.0f ) ;
	vRay[3].vEnd   = vRay[3].vStart + vCharaFront * 0.1f;
	
	vRay[4].vStart = vRay[3].vStart;
	vRay[4].vEnd   = vRay[3].vEnd + vCharaRight * 0.1f;
	
	vRay[5].vStart = vRay[3].vStart;
	vRay[5].vEnd   = vRay[3].vEnd - vCharaRight * 0.1f;
	
	vRay[6].vStart = m_vPos + Math::Vector3D(0.0f,0.8f,0.0f) + vCharaFront * 0.3f;
	vRay[6].vEnd   = m_vPos + vCharaFront * 0.3f;
	
	vRay[7].vStart = m_vPos + Math::Vector3D(0.0f,0.8f,0.0f) + vCharaFront * 0.2f;
	vRay[7].vEnd   = m_vPos + vCharaFront * 0.2f;

	vRay[8].vStart = m_vPos + Math::Vector3D(0.0f,0.8f,0.0f) + vCharaFront * 0.1f;
	vRay[8].vEnd   = m_vPos + vCharaFront * 0.1f;
	
	
	
	/*�O�����ǂłȂ����`�F�b�N*/
	if ( pMapActor->HitCheckByRay( vRay[0], RetEx ) || 
		 pMapActor->HitCheckByRay( vRay[1], RetEx ) || 
		 pMapActor->HitCheckByRay( vRay[2], RetEx ) ||
		 pMapActor->HitCheckByRay( vRay[3], RetEx ) ||
		 pMapActor->HitCheckByRay( vRay[4], RetEx ) ||
		 pMapActor->HitCheckByRay( vRay[5], RetEx ) || 
		 pMapActor->HitCheckByRay( vRay[6], RetEx ) ||
 		 pMapActor->HitCheckByRay( vRay[7], RetEx ) || 
		 pMapActor->HitCheckByRay( vRay[8], RetEx )  )
	{
		return true;
	}
	
	
	return false;

}

//==============================================================================
//�t���O�ݒu�\�I�u�W�F�N�g�`�F�b�N
//==============================================================================
//[input]
//	pChara:�ݒu����L����
//	CharaMax:�L�����ő吔
//	pSnd:�t���O�ݒu��
//[out]
//	ppFlashedChara:�t���b�V����Ԃ̃L����
//[return]
//	�t���O���ݒu�ł��邩
//==============================================================================
bool CPlayer::FlagObjectCheck( CCharacter *pChara[], Uint32 CharaMax, 
								Sound::ISound *pSnd, CCharacter **ppFlashedChara )
{
	Math::Matrix matWorld;
	Math::Matrix matTemp;
	
	Collision::CBox FlagRangeBox;
	
	matTemp.Identity();
	
	matWorld.Identity();
	
	matTemp.RotationY( toI( -m_vRot.x ) - DEG_TO_ANGLE( 90 ));
	
	matWorld *= matTemp;
	
	matTemp.Translation( m_vPos.x,
						 m_vPos.y, 
						 m_vPos.z );
	
	matWorld *= matTemp;
	
	/*����p�{�b�N�X�̍쐬*/
	FlagRangeBox.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
	
				
	for( Uint32 i = 0;i < CharaMax;++i )
	{
		if( m_IsSettingFlag )
		{
			if( pChara[i]->GetModelActor(m_ActorIndex)->Collision_Check( FlagRangeBox ) )
			{
				*ppFlashedChara = pChara[i];
				return true;
			}
			
			else
			{
				ppFlashedChara = NULL;
				return false;
			}
		}	
	}
	
	return false;
}

//==============================================================================
//�t���O�ݒu�\�`�F�b�N
//==============================================================================
//[input]
//	pChara:�ݒu����L����
//	pSpr:
//[return]
//	�t���O�ݒu�\���ǂ���
//==============================================================================
bool CPlayer::SettableFlagCheck( CCharacter *pChara, CSprite3D *pSpr )
{
//	Box.CreateBox( Math::Vector3D( -1, 0, 0 ), Math::Vector3D(1, 2, 2), matWorld ); 
//	
//	if( pChara->GetModelActor(m_ActorIndex)->Collision_Check( Box ) )
//	{
//		if( pChara->GetStopFlag() )
//		{
//			pSpr->SetVisibleFlag( true );
//		}
//				
//		pSpr->SetAnimID( Math::Point2DI( 0, 0 ) );
//		
//		
//		pSpr->SetPosition( pChara->GetPosition() + Math::Vector3D(0, 1, 0) );
//			
//		return true;
//	}
//	
	return false;
}


//==============================================================================
//�t���O�̉��
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//==============================================================================
void CPlayer::MoveAdjust()
{
	if( m_vPos.x <= -359 )
	{
		m_vPos.x = -359;
	}
	
	if( m_vPos.x >= 359 )
	{
		m_vPos.x = 359;
	}
	
	if( m_vPos.z >= 0 )
	{
		m_vPos.z = 0;
	}
	
	if( m_vPos.z <= -528 )
	{
		m_vPos.z = -528;
	}
}


//==============================================================================
//�t���O�̉��
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//	pSound:�t���O�����
//	pMenu:���j���[
//==============================================================================
void CPlayer::RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CMenu *pMenu )
{
	
	
	//if( this->GetSetFlag() )
	//{
	//	static int count = 0;//�ꎞ�I�ȃA�j���[�V�����p
	//	
	//	if( this->HitCheck( m_pFlag ) )
	//	//if( m_pActorModel[m_ActorIndex]->Collision_Check( )
	//	{
	//		
	//		Math::Vector3D vPos = m_vPos;
	//		
	//		pMenu->SetCaptionName("�t���O��������܂���?");
	//		
	//		pMenu->SetPopUp( true );
	//		
	//		pMenu->SetYesNoOrderFlag( false );
	//		
	//		eSelectType Select = pMenu->SelectYesNo( m_pCtrl );
	//		
	//		if( Select == SELECT_YES )
	//		{
	//			this->SetFlag( false );
	//			this->SetCameraModeFlag( false );
	//				
	//			if( pChara != NULL )
	//			{	
	//				pChara->SetFlag( false );
	//				pChara = NULL;
	//			}
	//			
	//			pSound->Play( 0 );
	//			
	//		}
	//		
	//		else if( Select == SELECT_NO )
	//		{
	//			Math::Vector3D vCharaFront;
	//			
	//			m_pActorModel[m_ActorIndex]->GetFront( vCharaFront );
	//			
	//			
	//			m_vPos.z = Interpolation::Flat( vPos.z, vPos.z - vCharaFront.z, 60, count );
	//		}
	//		
	//		count++;
	//		
	//	}
	//	
	//	
	//}
	
}

//==============================================================================
//�t���O�̉��
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//	pSound:�t���O�����
//	pSpr:���j���[
//==============================================================================
void CPlayer::RecallFlag( CCharacter *pChara, Sound::ISound *pSound, CSprite3D *pSpr, CCharacter *pFlag )
{
	
	if( this->GetSetFlag() )
	{
		static int count = 0;//�ꎞ�I�ȃA�j���[�V�����p
		
		Collision::CBox Box;
		
		Math::Matrix matWorld;
		
		Math::Matrix matTemp;
		
		matTemp.Identity();
		
		//if( m_pActorModel[m_ActorIndex]->Collision_Check( Box ) )
		if( this->HitCheck( pFlag ) )
		{
			pSpr->SetAnimID( Math::Point2DI( 1, 0 ) );
			pSpr->SetPosition( m_pCamObj->GetPosition() + Math::Vector3D( 0, 1, 0 ) );
			pSpr->SetVisibleFlag( true );
			
			if( m_pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_SQUARE ) )
			{
				this->SetFlag( false );
				this->SetCameraModeFlag( false );
					
				if( pChara != NULL )
				{	
					pChara->SetFlag( false );
					pChara = NULL;
				}
				
				pSound->Play( 0 );
			}
		}
		
		else
		{
			pSpr->SetVisibleFlag( false );
		}
		
		
	}
	
	/*�t���O�Ƃ̓���*/
	if( pChara != NULL )
	{
		if( pChara->GetSetFlag() )
		{
			pFlag->SetPosition( pChara->GetSetFlagPosition() );
		}
	}
	
}


//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
//bool CPlayer::GroundCheck( CCharacter *pChara, int index )
//{
//	Renderer::SCollisionResult Ret;
//	Collision::CLine3D vRay;
//	
//	const float GRAVITY = 0.01f;
//	
//	//------------------------------------------------
//	// �d�͉����x
//	//------------------------------------------------
//	m_fGravity += GRAVITY;
//	
//	if ( m_fGravity > 1.0f )
//	{
//		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
//		m_fGravity = 1.0f;
//	}
//
//	//------------------------------------------------
//	// �L�����̎��R����
//	//------------------------------------------------
//	m_vPos.y -= m_fGravity;
//
//	//------------------------------------------------
//	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
//	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
//	//------------------------------------------------
//	vRay.vStart = m_vPos + Math::Vector3D(0.0f,0.5f,0.0f);
//	vRay.vEnd   = m_vPos;
//	
//	if ( pChara->GetModelActor(index)->HitCheckByRay( vRay, Ret ) )
//	{
//		// �Փˈʒu�Ɉړ�
//		m_vPos = Ret.vHitPosition;
//		
//		m_vPos.z -= pChara->GetSpeed()*2;
//		
//		m_vDirection += pChara->GetSpeed();
//		// �d�͉���������
//		m_fGravity = 0.0f;
//		
//		return true;
//	}
//	
//	return false;
//
//}


	
	//if( CWiiRemocon::GetNunAttacked() )
	//{
	//	if( CWiiRemocon::GetNunState(REM_STATE_PUSH, NUNCHUK_BUTTON_C) )
	//	{
	//		obj->SetStopFlag( !obj->GetStopFlag() );
	//	}
	//}
	//
	//else
	//{
	//	if( CJoyPad::GetState(0, PAD_STATE_PUSH, PAD_BUTTON_02) )
	//	{
	//		obj->SetStopFlag( !obj->GetStopFlag() );
	//	}
	//	
	//	else if( CJoyPad::GetState(0, PAD_STATE_HOLD, PAD_BUTTON_02) )
	//	{			
	//		m_IsHold = true;
	//		
	//		if(CJoyPad::GetState( 0, PAD_STATE_PULL, PAD_BUTTON_02 ) )
	//		{
	//			m_IsHold = false;
	//		}			
	//		
	//	}
	//	
	//	
	//	
	//}

