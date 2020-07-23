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
	pAudio->Load(m_bgm,m_bgm_file);
	
}

void SoundManager::SoundBGM(std::string key_,int vol_)
{
	pAudio->Play(m_bgm,vol_,true);
}

void SoundManager::SoundSE(std::string key_, int vol_)
{
	pAudio->Play(sound_file[key_], vol_);
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
	
	m_bgm = "BGM";
	m_bgm_file = "Res/Sound/–³‘è.wav";

	sound_file["BGM"] = "BGM";
	sound_file["SE"] = "SE";

}
