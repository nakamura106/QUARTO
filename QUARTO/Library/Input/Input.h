#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#include <dinput.h>
#include<d3dx9.h>
struct KeyCode
{
	// @brife �L�[�̎��
	enum KEY_INFO
	{
		ESC_KEY,
		SPACE_KEY,
		UP_KEY,
		DOWN_KEY,
		RIGHT_KEY,
		LEFT_KEY,
		A_KEY,
		W_KEY,
		S_KEY,
		D_KEY,
		F_KEY,
		E_KEY,
		R_KEY,
		Q_KEY,
		T_KEY,
		Y_KEY,
		RETURN_KEY,
		L_CONTROL,
		L_SHIFT,
		ZERO_KEY,
		ONE_KEY,
		TWO_KEY,
		THREE_KEY,
		FOUR_KEY,
		FIVE_KEY,
		SIX_KEY,
		SEVEN_KEY,
		EIGHT_KEY,
		NINE_KEY,
		MAX_KEY_INFO,
	};

	//�R���g���[���[�̃{�^��
	enum ButtonKind
	{
		A_BUTTON,
		B_BUTTON,
		X_BUTTON,
		Y_BUTTON,
		LEFT_B_BUTTON,
		RIGHT_B_BUTTON,
		LEFT_T_BUTTON,
		RIGHT_T_BUTTON,
		L_UP_STICK,
		L_DOWN_STICK,
		L_LEFT_STICK,
		L_RIGHT_STICK,
		R_UP_STICK,
		R_DOWN_STICK,
		R_LEFT_STICK,
		R_RIGHT_STICK,
		UP_BUTTON,
		DOWN_BUTTON,
		LEFT_BUTTON,
		RIGHT_BUTTON,
		BUTTON_KIND_MAX,
	};

	//�}�E�X�̃{�^��
	enum MouseButton
	{
		LEFT,		//!< ��
		RIGHT,		//!< �E
		CENTER,		//!< �^��
	};

};

struct KeyState
{
	//�{�^���̏��
	enum ButtonState
	{
		BUTTON_STATE_NONE,
		BUTTON_STATE_DOWN,
		BUTTON_STATE_PUSH,
		BUTTON_STATE_UP,
		BUTTON_STATE_MAX,
	};

	//�������
	enum InputState
	{
		NOT_PUSH,		//������Ă��Ȃ�
		PUSH_DOWN,		//�����ꂽ�u��
		PUSH,			//������Ă���
		PUSH_UP,		//�������u��
	};
};

class Input {
public:

	struct DeviceEnumParameter
	{
		LPDIRECTINPUTDEVICE8* gamepad_device_ptr;
		int find_count;
	};
	
public:
/**
	* @brief Input�@�\�̏������֐�@n
	* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s���܂�
	* InitEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂���܂���
	* @return ���������ʁA�����̏ꍇ��true
	* @param[in] hInstance �C���X�^���X�n���h��
	* @param[in] hWindow �E�B���h�E�n���h��
	*/
	bool InitInput();

	/**
	* @brief Input�@�\�̏I���֐�@n
	* Input�@�\���I�������܂�@n
	* EndEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂���܂���
	*/
	void EndInput();


	
	

	/**
	* @brief �L�[��������Ă����Ԃ̔���֐�@n
	* �w�肵���L�[��������Ă��邩�𔻒肵�܂�
	* @return ���茋�ʁA������Ă���Ȃ�true
	* @param[in] key ���肵�����L�[
	*/
	bool GetKey(KeyCode::KEY_INFO key_);

	/**
	* @brief ���͏��̍X�V@n
	* �f�o�C�X�̓��͏��̍X�V���s��@n
	* ���t���[���ɂP�x�K�����s����K�v������
	*/
	void UpdateInput();

	

	/**
	* @brief �L�[�������ꂽ�u�Ԃ̔���֐�@n
	* �w�肵���L�[�������ꂽ�u�ԉ��𔻒肵�܂�
	* @return ���茋�ʁA�����ꂽ�u�ԂȂ�true
	* @param[in] key ���肵�����L�[
	*/
	bool GetKeyDown(KeyCode::KEY_INFO key_);

	/**
	* @brief �L�[�������ꂽ�u�Ԃ̔���֐�@n
	* �w�肵���L�[�������ꂽ�u�ԉ��𔻒肵�܂�
	* @return ���茋�ʁA�����ꂽ�Ȃ�true
	* @param[in] key ���肵�����L�[
	*/
	bool GetKeyUp(KeyCode::KEY_INFO key_);

	/**
	* @brief �N���b�N�����u�Ԕ���֐�@n
	* �w�肵���}�E�X�̃{�^�����N���b�N���ꂽ�u�Ԃ��ǂ����𔻒肷��
	* @return ���茋��(�����ꂽ�u�ԂȂ�true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool OnMouseDown(KeyCode::MouseButton button_type_);

	/**
	* @brief �N���b�N������֐�@n
	* �w�肵���}�E�X�̃{�^�����N���b�N�����ǂ����𔻒肷��
	* @return ���茋��(�N���b�N���u�ԂȂ�true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool OnMousePush(KeyCode::MouseButton button_type_);

	/**
	* @brief �N���b�N�I������֐�@n
	* �w�肵���}�E�X�̃{�^�����N���b�N���I�������u�Ԃ��ǂ����𔻒肷��
	* @return ���茋��(�N���b�N����߂��u�ԂȂ�true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool OnMouseUp(KeyCode::MouseButton button_type_);

	/** @brief �}�E�X�̍��W�擾�֐� */
	D3DXVECTOR2 GetMousePos();

	/**
	* @brief �R���g���[���[�̃{�^������֐�@n
	* �w�肵���R���g���[���[�̃{�^���������Ă��邩���Ă��邩�ǂ����𔻒肷��
	* @return ���茋��(�����Ă����true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool IsButtonPush(KeyCode::ButtonKind button_);

	/**
	* @brief �R���g���[���[�̃{�^������֐�@n
	* �w�肵���R���g���[���[�̃{�^���𗣂����u�Ԃ𔻒肷��
	* @return ���茋��(�{�^���𗣂����u�ԂȂ�true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool IsButtonUp(KeyCode::ButtonKind button_);

	/**
	* @brief �R���g���[���[�̃{�^������֐�@n
	* �w�肵���R���g���[���[�̃{�^�����������u�Ԃ𔻒肷��
	* @return ���茋��(�{�^�����������u�ԂȂ�true)
	* @param[in] button_type ���肵�����{�^���̎��
	*/
	bool IsButtonDown(KeyCode::ButtonKind button_);

	private:
		BOOL StartGamePadControl();
		BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device_);
		static BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi_, LPVOID pvRef_);		
		/**
	* @brief �L�[�{�[�h�̓��͏��̍X�V@n
	* �f�o�C�X�̓��͏��̍X�V���s���܂�@n
	* ���t���[����1�x�K�����s����K�v������܂�
	*/
		void KeyStateUpdate();
		void UpdateMouse();
		void UpdateGamePad();
		bool CreateInputInterface();
		bool CreateMouseDevice();
		bool CreateGamePadDevice();
		bool CreateKeyboardDevice();

	private:
		LPDIRECTINPUT8 input_interface_;

		LPDIRECTINPUTDEVICE8 key_device_;
		LPDIRECTINPUTDEVICE8 mouse_device_;		//!< DIRECTINPUTDEVICE8�̃|�C���^
		LPDIRECTINPUTDEVICE8 gamepad_device_;

		DIMOUSESTATE prev_mouse_state_;			//!< �}�E�X�̂P�t���[���O�̓��͏��
		DIMOUSESTATE curr_mouse_state_;		//!< �}�E�X�̌��݂̓��͏��

		D3DXVECTOR2 mouse_pos_;
		D3DXVECTOR2 mouse_move_vec_;


		KeyState::ButtonState ButtonStates[KeyCode::ButtonKind::BUTTON_KIND_MAX];

		KeyState::InputState InputState[KeyCode::KEY_INFO::MAX_KEY_INFO];

		int KeyInfo[KeyCode::KEY_INFO::MAX_KEY_INFO] = {
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
			DIK_R,
			DIK_Q,
			DIK_T,
			DIK_Y,
			DIK_RETURN,
			DIK_LCONTROL,
			DIK_LSHIFT,
			DIK_0,
			DIK_1,
			DIK_2,
			DIK_3,
			DIK_4,
			DIK_5,
			DIK_6,
			DIK_7,
			DIK_8,
			DIK_9,
		};
};



#endif