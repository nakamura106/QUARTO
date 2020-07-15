#include"LibraryManager.h"
#include"../Library/Engine/Camera.h"
#include"../Library/Engine/Engine.h"
#include"../Library/Graphics/Graphics.h"
#include"../Library/Input/Input.h"
#include"../Library/Sound/Sound.h"
#include"../Library/Video/Video.h"

LibraryManager* LibraryManager::instance = 0;

LibraryManager* LibraryManager::Instance()
{
	if (instance == 0)
	{
		instance = new LibraryManager;
	}
	return instance;
}

LibraryManager::LibraryManager()
{
	m_Camera = new CAMERA(pos);
	m_Engne = new Engine;
	m_Graphics = new Graphics;
	m_Audio = AudioPlayer::GetInstance(m_Engne->GetWindowHandle());
	m_Input = new Input;
	m_Video = new Video;
}

void LibraryManager::Init()
{
	m_Camera = new CAMERA(pos);
	m_Engne = new Engine;
	m_Graphics = new Graphics;
	m_Audio = AudioPlayer::GetInstance(m_Engne->GetWindowHandle());
	m_Input = new Input;
	m_Video = new Video;
}

