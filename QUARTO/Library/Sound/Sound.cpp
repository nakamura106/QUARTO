#include "Sound.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

//===============================================
	//	�I�[�f�B�I���\�[�X�Ǘ�
	//===============================================

	//--------------------------------------------
	 //�@����Ăяo���p�R���X�g���N�^
DirectSound::DirectSound(HWND hwnd_) {


	DirectSoundCreate8(nullptr, &d_sound8_, nullptr);
	d_sound8_->SetCooperativeLevel(hwnd_, DSSCL_NORMAL);

	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = 0;
	desc.dwReserved = 0;
	desc.lpwfxFormat = nullptr;
	desc.guid3DAlgorithm = GUID_NULL;

	d_sound8_->CreateSoundBuffer(&desc, &primary_buffer_, nullptr);
}
//-------------------------------------
//�@�f�[�^�ǂݍ���
IDirectSoundBuffer8* DirectSound::LoadWaveFile(std::string file_name_) {


	HMMIO hmmio = nullptr;
	MMIOINFO mminfo = {};
	hmmio = mmioOpen((LPSTR)file_name_.c_str(), &mminfo, MMIO_READ);

	//�t�@�C���̃I�[�v���Ɏ��s�����ꍇ
	if (!hmmio) {
		MessageBox(0, "wave�t�@�C���̃I�[�v���Ɏ��s", 0, MB_OK);
		return nullptr;
	}

	MMRESULT result;
	MMCKINFO rif_chunk;
	rif_chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	result = mmioDescend(hmmio, &rif_chunk, NULL, MMIO_FINDRIFF);

	//�@���t�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	MMCKINFO fmt_chunk;
	fmt_chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	result = mmioDescend(hmmio, &fmt_chunk, &rif_chunk, MMIO_FINDCHUNK);

	// �t�H�[�}�b�g�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//������`�����l�����̏����i�[����
	WAVEFORMATEX format;
	DWORD fmsize = fmt_chunk.cksize;
	if (mmioRead(hmmio, (HPSTR)& format, fmsize) != fmsize) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//�f�[�^�����̈׈�x�߂�
	mmioAscend(hmmio, &fmt_chunk, 0);

	MMCKINFO data_chunk;
	data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	result = mmioDescend(hmmio, &data_chunk, &rif_chunk, MMIO_FINDCHUNK);
	// �f�[�^�`�����N�̌����Ɏ��s�����ꍇ
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	// �g�`�f�[�^
	DWORD data_size = data_chunk.cksize;
	BYTE* wav_data = new BYTE[data_chunk.cksize];
	if (mmioRead(hmmio, (HPSTR)wav_data, data_chunk.cksize) != data_chunk.cksize) {
		delete[] wav_data;
		return nullptr;
	}


	//����ǂݍ���
	mmioClose(hmmio, 0);

	// �Z�J���_���o�b�t�@�̐ݒ�
	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	desc.dwBufferBytes = data_size;   //�������T�C�Y
	desc.dwReserved = 0;			  //�\���
	desc.lpwfxFormat = &format;     //WAVE�t�H�[�}�b�g
	desc.guid3DAlgorithm = GUID_NULL; //3D�G�t�F�N�g���g�p���Ȃ�

	IDirectSoundBuffer* buf = 0;
	d_sound8_->CreateSoundBuffer(&desc, &buf, nullptr);

	//�߂�l��IDirectSoundBuffer�ׁ̈AIDirectSoundBuffer8�ɖ߂�
	buf->QueryInterface(IID_IDirectSoundBuffer8, (void**)& sec_buffer_);
	buf->Release();


	// WAV�f�[�^��������
	LPVOID write_data;
	DWORD len;
	sec_buffer_->Lock(
		0,		     	//���b�N�J�n�ʒu
		0,			    //�������T�C�Y
		&write_data,	//���b�N�ʒu�̃|�C���^
		&len,		    //�傫��
		NULL,	  	    //�͈͂𒴂����ꍇ�̃������̈�w��
		NULL,
		DSBLOCK_ENTIREBUFFER //�w��̑傫���������b�N����
	);

	memcpy(write_data, wav_data, len);
	sec_buffer_->Unlock(write_data, len, nullptr, 0);
	//�@���������폜
	delete[] wav_data;

	if (sec_buffer_ == nullptr) {
		MessageBox(0, "wave�t�@�C���̓ǂݍ��݂Ɏ��s", 0, MB_OK);
	}

	return sec_buffer_;
}

//-----------------------------------
//�@�f�X�g���N�^
DirectSound::~DirectSound() {

	d_sound8_->Release();
	//primary_buffer_->Release();
}



//==========================================
//  �T�E���h�v���[���[
//==========================================

bool AudioPlayer::Load(std::string alias_, std::string file_name_) {

	//�܂��ǂݍ���ł��Ȃ��T�E���h�f�[�^�ł���
	/*
		std::unordered_map.count(value�j
		 value���L�[�Ƃ����v�f�̌������s���B
		 �v�f���聨�P�@�v�f�Ȃ����O
	*/
	if (sound_data_.count(alias_) == 0) {
		sound_data_.emplace(alias_, sound_->LoadWaveFile(file_name_));
		return true;
	}
	return false;
}

//------------------------------------
// �Đ�
void AudioPlayer::Play(
	std::string alias_,
	int volume_,
	bool is_loop_
) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}

	if (is_loop_) {
		sound->SetVolume(volume_);
		sound->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		sound->SetVolume(volume_);
		sound->Play(0, 0, 0);
		sound->SetCurrentPosition(0);
	}
}

//----------------------------------
// ��~
void AudioPlayer::Stop(std::string alias_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}
	sound->Stop();
}

//----------------------------------
// �{�����[������
void AudioPlayer::SetVolume(std::string alias_, int volume_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}
	sound->SetVolume(volume_);
}

//-------------------------------
//�������
void AudioPlayer::Release(std::string alias_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//�T�E���h�f�[�^���Ȃ�����
	}

	if (sound) {
		sound->Release();
		sound = nullptr;
		sound_data_.erase(alias_);//�v�f�폜
	}
}

IDirectSoundBuffer8* AudioPlayer::Find(std::string alias_) {

	//�T�E���h�f�[�^���L�[�Ō���
	auto data = sound_data_.find(alias_);
	//�T�E���h�f�[�^���݂������ꍇ
	if (data != sound_data_.end()) {
		return data->second;
	}
	return nullptr;//������Ȃ������̂�null��n��
}

AudioPlayer::~AudioPlayer() {

	if (sound_data_.empty()) {
		//�v�f�̍폜�����ׂĊ������Ă���ꍇ�̓N���A
		sound_data_.clear();
	}
	//����R�ꂪ����ꍇ
	for (auto data : sound_data_) {
		IDirectSoundBuffer8* sound = data.second;
		if (sound == nullptr) {
			continue;
		}
		sound->Release();
		//sound_data_.erase(data.first);
	}
	sound_data_.clear();

	if (sound_) {
		delete sound_;
	}
}

