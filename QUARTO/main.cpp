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
	// エンジンの初期化
	if (THE_ENGINE->InitEngine(1920, 1080, "Library") == false)
	{
		return 0;
	}

	//THE_VIDEO->Load("Res/Movie/【PS3】-El-Shaddai-エルシャダイ-　_ルシフェルver_-高画質版.avi");
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

	// エンジン終了
	THE_ENGINE->EndEngine();
}