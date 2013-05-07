//*============================================================================
//DrawObject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "DrawObject.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	name:�f�[�^��
//===========================================================================
CDrawObject::CDrawObject( string name )
{
	m_IsVisible = true;
	
	m_DataName = name;
	
	m_vPos.Set( 0.0f, 0.0f, 0.0f );
	m_vRot.Set( 0.0f, 0.0f, 0.0f );
	m_vScale.Set( 0.0f, 0.0f, 0.0f );
	
}


//=============================================================================
//�ʒu���W�̐ݒ�
//=============================================================================
//[input]
//	vPos:�ݒ肷��ʒu���W
//=============================================================================
void CDrawObject::SetPosition( Math::Vector3D vPos )
{
	m_vPos = vPos;
}

//=============================================================================
//��]�p�x�̐ݒ�
//=============================================================================
//[input]
//	vRot:�ݒ肷���]�p�x
//=============================================================================
void CDrawObject::SetRotate(Math::Vector3D vRot)
{
	m_vRot = vRot;
}

//=============================================================================
//�g�k�̐ݒ�
//=============================================================================
void CDrawObject::SetScale(Math::Vector3D vScale)
{
	m_vScale = vScale;
}

//=============================================================================
//�ʒu���W�̎擾
//=============================================================================
//[return]
//	�ʒu���W
//=============================================================================
Math::Vector3D CDrawObject::GetPosition()
{
	return m_vPos;
}

//=============================================================================
//��]�p�x�̎擾
//=============================================================================
//[return]
//	��]�p�x
//=============================================================================
Math::Vector3D CDrawObject::GetRotate()
{
	return m_vRot;
}

//=============================================================================
//�g�k�̎擾
//=============================================================================
//[return]
//	�ʒu���W
//=============================================================================
Math::Vector3D CDrawObject::GetScale()
{
	return m_vScale;
}

