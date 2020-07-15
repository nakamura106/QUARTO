#define DIRECTINPUT_VERSION 0x0800
#include<d3dx9math.h>
#include<math.h>
#include "Input.h"
#include"../Engine/Engine.h"
#include"../../Manager/LibraryManager.h"
#include"../../Definition/Definition.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define MOUSE_ON_VALUE (0x80)		// �I����Ԃ̒l

// @brief ���͏�Ԃ̎��
enum INPUT_STATE
{
	NOT_PUSH,		//������Ă��Ȃ�
	PUSH_DOWN,		//�����ꂽ�u��
	PUSH,			//������Ă���
	PUSH_UP,		//�������u��
};

//�L�[�̏�Ԃ�ێ�����O���[�o���ϐ�


BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	//�������[�h�̐ݒ�
	if (FAILED(device->SetCooperativeLevel(
		FindWindow(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		return false;
	}
	return true;
}

//���C�u�������̃L�[���z��
int g_KeyInfo[] = {
	DIK_ESCAPE,
	DIK_SPACE,
	DIK_UP,
	DIK_DOWN,
	DIK_RIGHT,
	DIK_LEFT,
	DIK_A,
	DIK_W,
	DIK_S,
	DIK_D,
	DIK_F,
	DIK_E,
	DIK_Q,
	DIK_T,
	DIK_Y,
	DIK_RETURN,
	DIK_LCONTROL,
	DIK_LSHIFT,
};

BOOL Input::StartGamePadControl()
{
	if (GamePadDevice == nullptr)
	{
		return false;
	}

	if (FAILED(GamePadDevice->Acquire()))
	{
		return false;
	}

	return true;
}

BOOL Input::SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	// ��������DIPROP�̃w�b�_�[�ɃX�e�[�^�X�ݒ�
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	return true;
}

BOOL CALLBACK Input::DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	HRESULT hr = THE_INPUT->InputInterface->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	if (THE_INPUT->SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	//if (FAILED(device->Poll()))
	//{
	//	return DIENUM_STOP;
	//}

	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

bool Input::InitInput()
{
	if (CreateInputInterface() == false)
	{
		return false;
	}

	if (CreateMouseDevice() == false)
	{
		EndInput();
		return false;
	}

	if (CreateKeyboardDevice() == false) {
		EndInput();
		return false;
	}

	if (CreateGamePadDevice() == false)
	{
		EndInput();
		return false;
	}

	for (int i = 0; i < Input::ButtonKind::ButtonKindMax; i++)
	{
		ButtonStates[i] = Input::ButtonState::ButtonStateNone;
	}

	ZeroMemory(&CurrentMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&PrevMouseState, sizeof(DIMOUSESTATE));

	return true;
}

void Input::EndInput()
{
	if (MouseDevice != nullptr)
	{
		MouseDevice->Release();
		MouseDevice = nullptr;
	}

	if (InputInterface != nullptr)
	{
		InputInterface->Release();
		InputInterface = nullptr;
	}

	if (GamePadDevice != nullptr)
	{
		GamePadDevice->Release();
		GamePadDevice = nullptr;
	}

	if (KeyDevice != nullptr)
	{
		KeyDevice->Release();
		KeyDevice = nullptr;
	}
}

bool Input::CreateInputInterface()
{
	// IDirectInput8�C���^�[�t�F�C�X�̎擾
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)& InputInterface,
		NULL);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool Input::CreateGamePadDevice()
{
	Input::DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &GamePadDevice;

	// �w�肵���f�o�C�X��񋓂���i����ł���΃Q�[���p�b�h�j
	if (FAILED(InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,
		DeviceFindCallBack,		// ��2�����F�R�[���o�b�N�֐�
		&parameter,				// ��3�����F�R�[���o�b�N�֐��ɓn�����Ƃ��ł���f�[�^
		DIEDFL_ATTACHEDONLY		// ��4�����F����ł������Ă���f�o�C�X�݂̂��g�p����ݒ�
	)))
	{
		return false;
	}

	/*if (parameter.FindCount == 0)
	{
		return false;
	}*/

	int count = 0;
	while (StartGamePadControl() == false)
	{
		Sleep(1000);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	return true;
}

bool Input::CreateMouseDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(InputInterface->CreateDevice(GUID_SysMouse, &MouseDevice, NULL)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(MouseDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	MouseDevice->Acquire();

	return true;
}

bool Input::CreateKeyboardDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(InputInterface->CreateDevice(GUID_SysKeyboard, &KeyDevice, NULL)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(KeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(KeyDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(KeyDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	KeyDevice->Acquire();

	return true;
}

void Input::KeyStateUpdate()
{
	BYTE Key[256];
	HRESULT hr = KeyDevice->GetDeviceState(256, Key);

	if (FAILED(hr))
	{
		return;
	}

	for (int i = 0; i < MAX_KEY_INFO; i++)
	{
		if (Key[KeyInfo[i]] & 0x80)
		{
			if (InputState[i] == INPUT_STATE::NOT_PUSH || InputState[i] == INPUT_STATE::PUSH_UP)
			{
				InputState[i] = INPUT_STATE::PUSH_DOWN;
			}
			else
			{
				InputState[i] = INPUT_STATE::PUSH;
			}
		}
		else
		{
			if (InputState[i] == INPUT_STATE::PUSH || InputState[i] == INPUT_STATE::PUSH_DOWN)
			{
				InputState[i] = INPUT_STATE::PUSH_UP;
			}
			else
			{
				InputState[i] = INPUT_STATE::NOT_PUSH;
			}
		}
	}
}

bool Input::GetKey(KEY_INFO key)
{
	return (InputState[key] == INPUT_STATE::PUSH);
}

bool Input::GetKeyDown(KEY_INFO key)
{
	return (InputState[key] == INPUT_STATE::PUSH_DOWN);
}

bool Input::GetKeyUp(KEY_INFO key)
{
	return (InputState[key] == INPUT_STATE::PUSH_UP);
}

void Input::UpdateInput()
{
	UpdateMouse();
	UpdateGamePad();

	PrevMouseState = CurrentMouseState;
	// �}�E�X�̏�Ԃ��擾���܂�
	HRESULT	hr = MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
	if (FAILED(hr))
	{
		MouseDevice->Acquire();
		hr = MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
	}
}

bool Input::OnMouseDown(MouseButton button_type)
{
	if (!(PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool Input::OnMousePush(MouseButton button_type)
{
	if (PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool Input::OnMouseUp(MouseButton button_type)
{
	if (PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}

	return false;
}

void Input::UpdateMouse()
{
	D3DXVECTOR2 prev = MousePos;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(TEXT("XFileDraw"), nullptr), &p);

	MousePos.x = (float)p.x;
	MousePos.y = (float)p.y;

	MouseMoveVec.x = MousePos.x - prev.x;
	MouseMoveVec.y = MousePos.y - prev.y;
}

D3DXVECTOR2 Input::GetMousePos()
{
	return MousePos;
}

void Input::UpdateGamePad()
{

	if (GamePadDevice == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;
	HRESULT hr = GamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		if (FAILED(GamePadDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
			{
				ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}

	bool is_push[ButtonKind::ButtonKindMax] = { false };

	//���A�i���O�X�e�B�b�N��500�̂Ƃ��Ńf�b�h�]�[������
	if (pad_data.lX < -500)
	{
		is_push[ButtonKind::L_LeftStick] = true;
	}
	else if (pad_data.lX > 500)
	{
		is_push[ButtonKind::L_RightStick] = true;
	}

	if (pad_data.lY < -500)
	{
		is_push[ButtonKind::L_UpStick] = true;
	}
	else if (pad_data.lY > 500)
	{
		is_push[ButtonKind::L_DownStick] = true;
	}
	if (pad_data.lZ > 50000)
	{
		is_push[ButtonKind::LeftTButton] = true;
	}
	else if (pad_data.lZ < 500)
	{
		is_push[ButtonKind::RightTButton] = true;
	}

	if (pad_data.lRx < 10000)
	{
		is_push[ButtonKind::R_LeftStick] = true;
	}
	else if (pad_data.lRx > 40000)
	{
		is_push[ButtonKind::R_RightStick] = true;
	}

	if (pad_data.lRy < 10000)
	{
		is_push[ButtonKind::R_UpStick] = true;
	}
	else if (pad_data.lRy > 40000)
	{
		is_push[ButtonKind::R_DownStick] = true;
	}
	// �\���L�[
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((pad_data.rgdwPOV[0] / 100.0f));
		// �{����x��cos�Ay��sin�����ǁArgdwPOV��0���ォ��n�܂�̂ŁA
		// cos��sin���t�ɂ��������s��������
		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[ButtonKind::LeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[ButtonKind::RightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[ButtonKind::UpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[ButtonKind::DownButton] = true;
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		if (pad_data.rgbButtons[i] == 0x80)
		{
			is_push[i] = true;
		}
		else {
			is_push[i] = false;
		}
	}


	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (ButtonStates[i] == ButtonState::ButtonStateNone)
			{
				ButtonStates[i] = ButtonState::ButtonStateDown;
			}
			else
			{
				ButtonStates[i] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (ButtonStates[i] == ButtonState::ButtonStatePush)
			{
				ButtonStates[i] = ButtonState::ButtonStateUp;
			}
			else
			{
				ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}
}

bool Input::IsButtonPush(ButtonKind button)
{
	if (ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

bool Input::IsButtonUp(ButtonKind button)
{
	if (ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

bool Input::IsButtonDown(ButtonKind button)
{
	if (ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}