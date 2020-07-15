#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#include <dinput.h>
#include<d3dx9.h>

class Input {
public:
	/** @brief マウスボタンの種類 */
	enum MouseButton
	{
		Left,		//!< 左
		Right,		//!< 右
		Center,		//!< 真ん中
	};

	// @brife キーの種類
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
		Q_KEY,
		T_KEY,
		Y_KEY,
		RETURN_KEY,
		L_CONTROL,
		L_SHIFT,
		MAX_KEY_INFO,
	};

	enum ButtonKind
	{
		AButton,
		BButton,
		XButton,
		YButton,
		LeftBButton,
		RightBButton,
		LeftTButton,
		RightTButton,
		L_UpStick,
		L_DownStick,
		L_LeftStick,
		L_RightStick,
		R_UpStick,
		R_DownStick,
		R_LeftStick,
		R_RightStick,
		UpButton,
		DownButton,
		LeftButton,
		RightButton,
		ButtonKindMax,
	};

	enum ButtonState
	{
		ButtonStateNone,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	};

	enum INPUT_STATE
	{
		NOT_PUSH,		//押されていない
		PUSH_DOWN,		//押された瞬間
		PUSH,			//押されている
		PUSH_UP,		//離した瞬間
	};

	struct DeviceEnumParameter
	{
		LPDIRECTINPUTDEVICE8* GamePadDevice;
		int FindCount;
	};
	
public:
/**
	* @brief Input機能の初期化関数@n
	* デバイスの入力取得に必要な初期化を行います
	* InitEngineで実行されるので開発側が実行する必要はありません
	* @return 初期化結果、成功の場合はtrue
	* @param[in] hInstance インスタンスハンドル
	* @param[in] hWindow ウィンドウハンドル
	*/
	bool InitInput();

	/**
	* @brief Input機能の終了関数@n
	* Input機能を終了させます@n
	* EndEngineで実行されるので開発側が実行する必要はありません
	*/
	void EndInput();


	
	

	/**
	* @brief キーが押されている状態の判定関数@n
	* 指定したキーが押されているかを判定します
	* @return 判定結果、押されているならtrue
	* @param[in] key 判定したいキー
	*/
	bool GetKey(KEY_INFO key);

	/**
	* @brief 入力情報の更新@n
	* デバイスの入力情報の更新を行う@n
	* 毎フレームに１度必ず実行する必要がある
	*/
	void UpdateInput();

	

	/**
	* @brief キーが押された瞬間の判定関数@n
	* 指定したキーが押された瞬間化を判定します
	* @return 判定結果、押された瞬間ならtrue
	* @param[in] key 判定したいキー
	*/
	bool GetKeyDown(KEY_INFO key);

	/**
	* @brief キーが離された瞬間の判定関数@n
	* 指定したキーが離された瞬間化を判定します
	* @return 判定結果、離されたならtrue
	* @param[in] key 判定したいキー
	*/
	bool GetKeyUp(KEY_INFO key);

	/**
	* @brief クリックした瞬間判定関数@n
	* 指定したマウスのボタンがクリックされた瞬間かどうかを判定する
	* @return 判定結果(押された瞬間ならtrue)
	* @param[in] button_type 判定したいボタンの種類
	*/
	bool OnMouseDown(MouseButton button_type);

	/**
	* @brief クリック中判定関数@n
	* 指定したマウスのボタンがクリック中かどうかを判定する
	* @return 判定結果(クリック中瞬間ならtrue)
	* @param[in] button_type 判定したいボタンの種類
	*/
	bool OnMousePush(MouseButton button_type);

	/**
	* @brief クリック終了判定関数@n
	* 指定したマウスのボタンがクリックを終了した瞬間かどうかを判定する
	* @return 判定結果(クリックをやめた瞬間ならtrue)
	* @param[in] button_type 判定したいボタンの種類
	*/
	bool OnMouseUp(MouseButton button_type);

	/** @brief マウスの座標取得関数 */
	D3DXVECTOR2 GetMousePos();

	bool IsButtonPush(ButtonKind button);
	bool IsButtonUp(ButtonKind button);
	bool IsButtonDown(ButtonKind button);

	private:
		BOOL StartGamePadControl();
		BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device);
		static BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);		
		/**
	* @brief キーボードの入力情報の更新@n
	* デバイスの入力情報の更新を行います@n
	* 毎フレームに1度必ず実行する必要があります
	*/
		void KeyStateUpdate();
		void UpdateMouse();
		void UpdateGamePad();
		bool CreateInputInterface();
		bool CreateMouseDevice();
		bool CreateGamePadDevice();
		bool CreateKeyboardDevice();

	private:
		LPDIRECTINPUT8 InputInterface;

		LPDIRECTINPUTDEVICE8 KeyDevice;
		LPDIRECTINPUTDEVICE8 MouseDevice;		//!< DIRECTINPUTDEVICE8のポインタ
		LPDIRECTINPUTDEVICE8 GamePadDevice;

		DIMOUSESTATE PrevMouseState;			//!< マウスの１フレーム前の入力情報
		DIMOUSESTATE CurrentMouseState;		//!< マウスの現在の入力情報

		D3DXVECTOR2 MousePos;
		D3DXVECTOR2 MouseMoveVec;


		ButtonState ButtonStates[ButtonKind::ButtonKindMax];

		INPUT_STATE InputState[KEY_INFO::MAX_KEY_INFO];

		int KeyInfo[KEY_INFO::MAX_KEY_INFO] = {
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
};



#endif