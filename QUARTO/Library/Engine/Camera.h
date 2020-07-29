#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

class Camera
{
private:
	/* �J�����̈ړ����x Walk */
	const float walk_speed_;

	/* �J�����̈ړ����x Sprint */
	const float sprint_speed_;

	struct CAMERA_DATA {

		/* �J�����̈ʒu */
		D3DXVECTOR3 camera_pos;

		/* �����_ */
		D3DXVECTOR3 eye_pos;

		/* �J�����̏�����̃x�N�g�� */
		D3DXVECTOR3 camera_up;

		D3DXVECTOR3 forward;

		/* �J�����̃r���[����ۑ�����ϐ� */
		D3DXMATRIX mat_view;

		/* �p�x */
		float rad;

		/* ��]���x */
		float rotate_speed;

		/* X����] */
		float yaw;

		/* Y����] */
		float pitch;

		/* Z����] */
		float roll;

		/* �X�s�[�h */
		float speed;

		/* �ړ����x */
		//D3DXVECTOR3 m_Velocity;

	}camera_data_;

public:
	Camera(D3DXVECTOR3 pos_) :
		walk_speed_(0.5f),
		sprint_speed_(6.0f)
	{
		camera_data_.camera_pos.x = pos_.x;
		camera_data_.camera_pos.y = pos_.y;//+ 0.5;	// ������(FirstPerson�p)
		camera_data_.camera_pos.z = pos_.z;

		camera_data_.eye_pos.x = 0.0f;
		camera_data_.eye_pos.y = 0.0f;
		camera_data_.eye_pos.z = 0.0f;

		camera_data_.camera_up.x = 0.0f;
		camera_data_.camera_up.y = 1.0f;
		camera_data_.camera_up.z = 0.0f;

		camera_data_.rotate_speed = 0.05f;

		camera_data_.yaw = 0.0f;
		camera_data_.pitch = 0.0f;
		camera_data_.roll = 0.0f;

		camera_data_.speed = walk_speed_;

		D3DXMatrixIdentity(&camera_data_.mat_view);
	}

	// �J�������W�̍X�V
	void Update();

	// �J�����̈ړ�
	void Move();

	void MouseRotate();

	void StickRotate();

	CAMERA_DATA* GetCameraData() { return &camera_data_; }


};

#endif