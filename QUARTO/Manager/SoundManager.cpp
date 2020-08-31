#include"../Definition/Definition.h"
#include"SoundManager.h"

SoundManager* SoundManager::p_instance = 0;

SoundManager* SoundManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new SoundManager;
	}

	return p_instance;
}

void SoundManager::RegisterSound()
{
	pAudio->Load("Title",sound_file["Title"]);
	pAudio->Load("Game",sound_file["Game"]);
	pAudio->Load("Result",sound_file["Result"]);
	
}

void SoundManager::SoundBGM(std::string key_,int vol_)
{
	pAudio->Play(key_,vol_,true);
}

void SoundManager::SoundSE(std::string key_, int vol_)
{
	pAudio->Play(key_, vol_);
}

void SoundManager::Stop(std::string name_)
{
	pAudio->Stop(name_);
}

void SoundManager::ReleaseSound()
{
	for (auto v : sound_file)
	{
		pAudio->Release(v.second);
	}
}

SoundManager::SoundManager()
{
	pAudio = AudioPlayer::GetInstance(FindWindow(WINDOW_CLASS_NAME,nullptr));
	
	
	
	sound_file["Title"] = "Res/Sound/BGM/Wading.wav";
	sound_file["Game"] = "Res/Sound/BGM/Game.wav";
	sound_file["Result"] = "Res/Sound/BGM/Result.wav";

	RegisterSound();
}
