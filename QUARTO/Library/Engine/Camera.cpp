#include"Camera.h"
#include"../Input/Input.h"
#include"../Graphics/Graphics.h"
#include"../../Definition/Definition.h"
#include"../../Manager/LibraryManager.h"

void CAMERA::Update()
{
	//�r���[���W�ϊ��p�̍s��Z�o start
	D3DXVECTOR3 camera_pos(m_cameradata.m_CameraPos.x, m_cameradata.m_CameraPos.y, m_cameradata.m_CameraPos.z);	// �J�����ʒu
	D3DXVECTOR3 eye_pos(m_cameradata.m_EyePos.x, m_cameradata.m_EyePos.y, m_cameradata.m_EyePos.z);				// �����_
	D3DXVECTOR3 up_vector(m_cameradata.m_CameraUp.x, m_cameradata.m_CameraUp.y, m_cameradata.m_CameraUp.z);		// �J�����̌���;
	D3DXMatrixLookAtLH(&m_cameradata.m_MatView,
		&camera_pos,				// �J�������W
		&eye_pos,					// �����_���W
		&up_vector);				// �J�����̏�̌����̃x�N�g��

	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_VIEW, &m_cameradata.m_MatView);
	//�r���[���W�ϊ��p�̍s��Z�o end

	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	//�ˉe���W�ϊ��p�̍s��Z�o start
	D3DVIEWPORT9 vp;
	THE_GRAPHICS->GetD3DDevice()->GetViewport(&vp);
	float aspect = (float)vp.Width / (float)vp.Height;

	// ������̍쐬
	D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DXToRadian(60),	// ��p
		aspect,				// �A�X�y�N�g��
		1.1f,				// near
		1000.0f);			// far
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	//�ˉe���W�ϊ��p�̍s��Z�o endMove();
	
	

	m_cameradata.m_Forward = m_cameradata.m_EyePos - m_cameradata.m_CameraPos;
	D3DXVec3Normalize(&m_cameradata.m_Forward, &m_cameradata.m_Forward);
}

void CAMERA::Move()
{
}



void CAMERA::MouseRotate()
{
	SetCursorPos(960, 540);
	m_cameradata.m_Yaw += (THE_INPUT->GetMousePos().x - 960) / 1920 * 50;//�����ŃJ�������x�ύX�\
	m_cameradata.m_Pitch -= (THE_INPUT->GetMousePos().y - 540) / 1080 * 20;
	if (m_cameradata.m_Pitch > 90.0f) { m_cameradata.m_Pitch = 180.0f - m_cameradata.m_Pitch; }
	if (m_cameradata.m_Pitch < -90.0f) { m_cameradata.m_Pitch = -180.0f - m_cameradata.m_Pitch; }

	
	m_cameradata.m_EyePos.x = m_cameradata.m_CameraPos.x + sinf(D3DXToRadian(m_cameradata.m_Yaw)) * cosf(D3DXToRadian(m_cameradata.m_Pitch));
	m_cameradata.m_EyePos.y = m_cameradata.m_CameraPos.y + sinf(D3DXToRadian(m_cameradata.m_Pitch));
	m_cameradata.m_EyePos.z = m_cameradata.m_CameraPos.z + cosf(D3DXToRadian(m_cameradata.m_Yaw)) * cosf(D3DXToRadian(m_cameradata.m_Pitch));
}

void CAMERA::StickRotate()
{
	if (THE_INPUT->IsButtonPush(THE_INPUT->R_LeftStick))
	{
		m_cameradata.m_Yaw -= 2.0f;
	}
	if (THE_INPUT->IsButtonPush(THE_INPUT->R_RightStick))
	{
		m_cameradata.m_Yaw += 2.0f;
	}
	if (THE_INPUT->IsButtonPush(THE_INPUT->R_UpStick))
	{
		m_cameradata.m_Pitch += 2.0f;
	}
	if (THE_INPUT->IsButtonPush(THE_INPUT->R_DownStick))
	{
		m_cameradata.m_Pitch -= 2.0f;
	}
	m_cameradata.m_EyePos.x = m_cameradata.m_CameraPos.x + sinf(D3DXToRadian(m_cameradata.m_Yaw)) * cosf(D3DXToRadian(m_cameradata.m_Pitch));
	m_cameradata.m_EyePos.y = m_cameradata.m_CameraPos.y + sinf(D3DXToRadian(m_cameradata.m_Pitch));
	m_cameradata.m_EyePos.z = m_cameradata.m_CameraPos.z + cosf(D3DXToRadian(m_cameradata.m_Yaw)) * cosf(D3DXToRadian(m_cameradata.m_Pitch));
}