#ifndef LIBRARYMANAGER_H_
#define LIBRARYMANAGER_H_

#include<d3dx9.h>

class AudioPlayer;
class Engine;
class Graphics;
class CAMERA;
class Input;
class Video;

class LibraryManager
{
public:
	static LibraryManager* Instance();
	LibraryManager();

	void Init();

	AudioPlayer* sound() { return m_Audio; };
	Engine* engine() { return m_Engne; };
	Graphics* graphics() { return m_Graphics; };
	Input* input() { return m_Input; }
	CAMERA* camera() { return m_Camera; };
	Video* video() { return m_Video; }

private:
	static LibraryManager* instance;

	AudioPlayer* m_Audio;
	Engine* m_Engne;
	Graphics* m_Graphics;
	Input* m_Input;
	CAMERA* m_Camera;
	Video* m_Video;

	D3DXVECTOR3 pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
};

#endif