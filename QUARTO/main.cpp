#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include"Manager/SceneManager.h"
#include"Definition/Definition.h"
#include"Library/Scene/TitleScene/TitleScene.h"

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmpLine,
	INT nCmdShow)
{
	// エンジンの初期化
	if (THE_ENGINE->InitEngine(1920, 1080, "Library") == false)
	{
		return 0;
	}

	// 「ロード中…」だけメインに入る前に読み込む
	THE_GRAPHICS->LoadTexture("Res/Tex/Loading_BackGround.bmp", "loading_background");
	THE_GRAPHICS->LoadTexture("Res/Tex/AngelWand.png", "now_loading");
	
	while (THE_SCENE->GetTitle()->GetTitleInfo()->title_state != TitleScene::TitleState::End)
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