#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

class CAMERA
{
private:
	/* カメラの移動速度 Walk */
	const float m_WalkSpeed;

	/* カメラの移動速度 Sprint */
	const float m_SprintSpeed;

	struct CAMERA_DATA {

		/* カメラの位置 */
		D3DXVECTOR3 m_CameraPos;

		/* 注視点 */
		D3DXVECTOR3 m_EyePos;

		/* カメラの上向きのベクトル */
		D3DXVECTOR3 m_CameraUp;

		D3DXVECTOR3 m_Forward;

		/* カメラのビュー情報を保存する変数 */
		D3DXMATRIX m_MatView;

		/* 角度 */
		float m_Rad;

		/* 回転速度 */
		float m_RotateSpeed;

		/* X軸回転 */
		float m_Yaw;

		/* Y軸回転 */
		float m_Pitch;

		/* Z軸回転 */
		float m_Roll;

		/* スピード */
		float m_Speed;

		/* 移動速度 */
		//D3DXVECTOR3 m_Velocity;

		bool m_startflag;
	}m_cameradata;

public:
	CAMERA(D3DXVECTOR3 pos_) :
		m_WalkSpeed(0.5f),
		m_SprintSpeed(6.0f)
	{
		m_cameradata.m_CameraPos.x = pos_.x;
		m_cameradata.m_CameraPos.y = pos_.y;//+ 0.5;	// 今だけ(FirstPerson用)
		m_cameradata.m_CameraPos.z = pos_.z;

		m_cameradata.m_EyePos.x = 0.0f;
		m_cameradata.m_EyePos.y = 0.0f;
		m_cameradata.m_EyePos.z = 0.0f;

		m_cameradata.m_CameraUp.x = 0.0f;
		m_cameradata.m_CameraUp.y = 1.0f;
		m_cameradata.m_CameraUp.z = 0.0f;

		m_cameradata.m_RotateSpeed = 0.05f;

		m_cameradata.m_Yaw = 0.0f;
		m_cameradata.m_Pitch = 0.0f;
		m_cameradata.m_Roll = 0.0f;

		m_cameradata.m_Speed = m_WalkSpeed;

		m_cameradata.m_startflag = false;

		D3DXMatrixIdentity(&m_cameradata.m_MatView);
	}

	// カメラ座標の更新
	void Update();

	// カメラの移動
	void Move();

	void MouseRotate();

	void StickRotate();

	CAMERA_DATA* GetCameraData() { return &m_cameradata; }


};

#endif