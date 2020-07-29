#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include"Manager/SceneManager.h"
#include"Definition/Definition.h"

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
		
			THE_SCENE->Update();

			THE_SCENE->Draw();

			
		}
	}
	
	// エンジン終了
	THE_ENGINE->EndEngine();
}