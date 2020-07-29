#include <fbxsdk.h>
#include <Windows.h>
#include <thread>
#include"Manager/LibraryManager.h"
#include"Manager/SoundManager.h"
#include"Manager/FbxManager.h"
#include"Definition/Definition.h"
#include"Library/Engine/Engine.h"
#include"Library/Input/Input.h"
#include"Library/Graphics/Graphics.h"
#include"Library/Video/Video.h"
#include"Library/Engine/Camera.h"

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
	Graphics::TEXTURE_DATA tex;
	THE_SOUND->RegisterSound();
	THE_FBX->LoadFbxMesh("Box","Res/Fbx/WorldBoxA02.fbx");
	THE_GRAPHICS->LoadTexture("Res/Tex/Title_3D_A.png",&tex);

	D3DXVECTOR3 pos=D3DXVECTOR3(0,-1,0);
	D3DXMATRIX world;
	D3DXMATRIX move;
	D3DXMATRIX scale;


	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scale,250,350,250);
	D3DXMatrixTranslation(&move,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&world, &scale, &move);
	
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
		
			THE_CAMERA->Update();

			THE_INPUT->UpdateInput();
			
			THE_GRAPHICS->DrawStart();

			if (THE_INPUT->GetKey(KeyCode::A_KEY)||THE_INPUT->IsButtonPush(KeyCode::A_BUTTON)||THE_INPUT->OnMousePush(KeyCode::LEFT))
			{
				THE_GRAPHICS->DrawTexture(&tex,D3DXVECTOR2(0,0));
				THE_GRAPHICS->DrawFont(0, 0, "ABCDE", Graphics::FontSize::SMALL, Graphics::BLACK);
			}
			
			THE_FBX->DrawFbx("Box", world);
			THE_GRAPHICS->DrawEnd();
			
		}
	}
	THE_FBX->ReleaseFbxMesh("Box");
	// エンジン終了
	THE_ENGINE->EndEngine();
}