/**
* @file GetEngine.h
* @brief �G���W������(�`��A����)�Ɋւ���֐��A�萔�̐錾
*/
#ifndef ENGINE_H_
#define ENGINE_H_
#define WINDOW_CLASS_NAME "Window"	//!< �E�B���h�E�N���X��
#include<Windows.h>

class Engine
{
public:
	/**
* @brief �G���W���������֐�@n
* �Q�[���Ŏg���G���W������(�`��A����)�̏������ƃE�B���h�E�̍쐬���s��@n
* �����̊֐��̓Q�[�����[�v�J�n�O�ɂP�x�������s����
* @return ���������� (true������)
* @param[in] width �E�B���h�E�̉���
* @param[in] height �E�B���h�E�̏c��
* @param[in] title_name �^�C�g���o�[�ɕ\�����镶����
*/
	bool InitEngine(int width_, int height_, const char* title_name_);

	/**
	* @brief �G���W���I���֐�@n
	* �Q�[���I����ɃG���W�������̏I�����s��@n
	* �����̊֐��̓Q�[�����[�v�I����ɂP�x�������s����
	*/
	void EndEngine();

	HWND GetWindowHandle() { return hWnd_; };

private:
	bool MakeWindow(int width_, int height_, const char* title_);
private:
	HWND hWnd_;
};

#endif