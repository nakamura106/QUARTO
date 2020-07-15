#ifndef DIRECTSOUND_H_
#define DIRECTSOUND_H_


#include <string>
#include <unordered_map>
#include <string>
#include <dsound.h>

class DirectSound {

public:


	DirectSound(HWND hwnd = nullptr);

	/*
	　
	 wavファイルの書き出しを行い、データを返す

	使用方法：
		DirectSound("hoge.wave");
	*/
	IDirectSoundBuffer8* LoadWaveFile(std::string file_name);

	~DirectSound();

private:

	IDirectSound8* m_DSound8;			//サウンドインターフェース
	IDirectSoundBuffer* m_PrimaryBuffer;//プライマリーバッファ―
	IDirectSoundBuffer8* m_SecBuffer;
};





//============================
// オーディオプレイヤークラス
//============================

class AudioPlayer {

public:

	static AudioPlayer* GetInstance(HWND hwnd = nullptr) {
		static AudioPlayer instance(hwnd);
		return &instance;
	}

	/*
		ウェブファイル読み込み
	引数：
		alias サウンドを使用する際の別名
		file_name サウンドファイル名
	概要：
		指定されたサウンドファイルを読み込む
	*/
	bool Load(std::string alias, std::string file_name);

	/*
		再生処理
	引数：
		volumr  音量（０で最大　-10000で無音）
		is_loop 再生方法（true=ループ再生）

	概要：
	　　指定された音量で、第２引数でしていされた
	  　再生方法により再生する
	*/
	void Play(
		std::string alias,
		int volume = -1000,
		bool is_loop = false);

	// 停止
	void Stop(std::string alias);

	/*
		ボリューム設定
	引数：
		volume 音量（0で最大 -10000で無音）
	*/
	void SetVolume(std::string alias, int volume);

	//解放処理
	void Release(std::string alias);

private:

	//コンストラクタ
	AudioPlayer(HWND hwnd) {
		//再生先のウィンドウハンドルを取得
		m_Sound = new DirectSound(hwnd);
		ZeroMemory(&m_SoundData, 0, sizeof(IDirectSoundBuffer8));
	}

	/*
		サウンドファイル検索
	引数：
		alias 読み込み時に設定したサウンドファイルの別名
	戻り値：
		成功　→　サウンドデータ
		失敗　→　null
	*/
	IDirectSoundBuffer8* Find(std::string alias);

	~AudioPlayer();

private:


	DirectSound* m_Sound;
	std::unordered_map<std::string, IDirectSoundBuffer8*> m_SoundData; //セカンダリバッファ
	WAVEFORMATEX m_format;			  //データフォーマット構造体
	DWORD m_size;					  //waveファイルのサイズ


};




#endif
