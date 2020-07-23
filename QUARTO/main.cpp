#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include"Manager/LibraryManager.h"
#include"Manager/SoundManager.h"
#include"Definition/Definition.h"
#include"Library/Engine/Engine.h"
#include"Library/Graphics/Graphics.h"
#include"Library/Video/Video.h"

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	//LibraryManager::Instance()->Init();
	// �G���W���̏�����
	if (THE_ENGINE->InitEngine(1920, 1080, "Library") == false)
	{
		return 0;
	}

	//THE_VIDEO->Load("Res/Movie/�yPS3�z-El-Shaddai-�G���V���_�C-�@_���V�t�F��ver_-���掿��.avi");
	//THE_VIDEO->Play(5000);
	THE_SOUND->RegisterSound();
	

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (msg.message == WM_CLOSE)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			THE_GRAPHICS->DrawStart();
			THE_SOUND->SoundBGM("BGM");
			THE_GRAPHICS->DrawEnd();
			
		}
	}

	// �G���W���I��
	THE_ENGINE->EndEngine();
}