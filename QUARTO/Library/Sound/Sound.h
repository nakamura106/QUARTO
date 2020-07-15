#ifndef DIRECTSOUND_H_
#define DIRECTSOUND_H_


#include <string>
#include <unordered_map>
#include <string>
#include <dsound.h>

class DirectSound {

public:


	DirectSound(HWND hwnd_ = nullptr);

	/*
	�@
	 wav�t�@�C���̏����o�����s���A�f�[�^��Ԃ�

	�g�p���@�F
		DirectSound("hoge.wave");
	*/
	IDirectSoundBuffer8* LoadWaveFile(std::string file_name_);

	~DirectSound();

private:

	IDirectSound8* d_sound8_;			//�T�E���h�C���^�[�t�F�[�X
	IDirectSoundBuffer* primary_buffer_;//�v���C�}���[�o�b�t�@�\
	IDirectSoundBuffer8* sec_buffer_;
};





//============================
// �I�[�f�B�I�v���C���[�N���X
//============================

class AudioPlayer {

public:

	static AudioPlayer* GetInstance(HWND hwnd_ = nullptr) {
		static AudioPlayer instance(hwnd_);
		return &instance;
	}

	/*
		�E�F�u�t�@�C���ǂݍ���
	�����F
		alias �T�E���h���g�p����ۂ̕ʖ�
		file_name �T�E���h�t�@�C����
	�T�v�F
		�w�肳�ꂽ�T�E���h�t�@�C����ǂݍ���
	*/
	bool Load(std::string alias_, std::string file_name_);

	/*
		�Đ�����
	�����F
		volumr  ���ʁi�O�ōő�@-10000�Ŗ����j
		is_loop �Đ����@�itrue=���[�v�Đ��j

	�T�v�F
	�@�@�w�肳�ꂽ���ʂŁA��Q�����ł��Ă����ꂽ
	  �@�Đ����@�ɂ��Đ�����
	*/
	void Play(
		std::string alias_,
		int volume_ = -1000,
		bool is_loop_ = false);

	// ��~
	void Stop(std::string alias_);

	/*
		�{�����[���ݒ�
	�����F
		volume ���ʁi0�ōő� -10000�Ŗ����j
	*/
	void SetVolume(std::string alias_, int volume_);

	//�������
	void Release(std::string alias_);

private:

	//�R���X�g���N�^
	AudioPlayer(HWND hwnd_) {
		//�Đ���̃E�B���h�E�n���h�����擾
		sound_ = new DirectSound(hwnd_);
		ZeroMemory(&sound_data_, 0, sizeof(IDirectSoundBuffer8));
	}

	/*
		�T�E���h�t�@�C������
	�����F
		alias �ǂݍ��ݎ��ɐݒ肵���T�E���h�t�@�C���̕ʖ�
	�߂�l�F
		�����@���@�T�E���h�f�[�^
		���s�@���@null
	*/
	IDirectSoundBuffer8* Find(std::string alias_);

	~AudioPlayer();

private:


	DirectSound* sound_;
	std::unordered_map<std::string, IDirectSoundBuffer8*> sound_data_; //�Z�J���_���o�b�t�@
	WAVEFORMATEX format_;			  //�f�[�^�t�H�[�}�b�g�\����
	DWORD size_;					  //wave�t�@�C���̃T�C�Y


};




#endif
