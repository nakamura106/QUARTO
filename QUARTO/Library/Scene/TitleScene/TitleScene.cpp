#include"TitleScene.h"
#include"../../../Definition/Definition.h"
#include"../../Input/Input.h"
#include"../../Sound/Sound.h"
#include"../../FBX/FBX.h"

TitleScene::TitleScene()
{
}

void TitleScene::InitScene()
{
	//THE_VIDEO->Load("Res/Movie/【PS3】-El-Shaddai-エルシャダイ-　_ルシフェルver_-高画質版.avi");
	//THE_VIDEO->Play(5000);
	
	//THE_SOUND->RegisterSound();
	//THE_SOUND->SoundBGM("BGM");
	//THE_FBX->LoadFbxMesh("Box", "Res/Fbx/WorldBoxA02.fbx");
	//THE_GRAPHICS->LoadTexture("Res/Tex/Title_3D_A.png", &tex);

	
	title_info.title_num = TitleNum::Title1;
	title_info.title_state = TitleState::title;

	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scale, 250, 350, 250);
	D3DXMatrixTranslation(&move, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &scale, &move);

	THE_SCENE->SetSceneStep(SceneStep::Main);

}

void TitleScene::UpdateScene()
{
	
	if (THE_INPUT->GetKeyDown(KeyCode::ONE_KEY))
	{
		if (title_info.title_num == TitleNum::Title1)
		{
			title_info.title_num = TitleNum::Title2;
		}
		else
		{
			title_info.title_num = TitleNum::Title1;
		}
	}
	else if (THE_INPUT->GetKeyDown(KeyCode::TWO_KEY))
	{
		if (title_info.title_num == TitleNum::Title1)
		{
			title_info.title_state = TitleState::Help;
		}
		else
		{
			title_info.title_state = TitleState::Game;
		}
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
	else if (THE_INPUT->GetKeyDown(KeyCode::THREE_KEY))
	{
		if (title_info.title_num == TitleNum::Title1)
		{
			title_info.title_state = TitleState::End;
		}
		else
		{
			title_info.title_state = TitleState::Game;
		}
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
}

void TitleScene::EndScene()
{
	//THE_GRAPHICS->ReleaseTexture(&tex);
	//THE_FBX->ReleaseFbxMesh("Box");

	THE_SCENE->SetSceneStep(SceneStep::Init);
	if (title_info.title_state == TitleState::Game)
	{
		THE_SCENE->SetSceneId(SceneId::Game);
	}
	else if (title_info.title_state == TitleState::Help)
	{
		THE_SCENE->SetSceneId(SceneId::Help);
	}
	else if (title_info.title_state == TitleState::End)
	{
		
	}
	
}

void TitleScene::Draw()
{
	//THE_GRAPHICS->DrawTexture(&tex, D3DXVECTOR2(0, 0));
	if (title_info.title_num == TitleNum::Title1)
	{
		THE_GRAPHICS->DrawFont(0, 0, "TITLE1", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 15, "Title2:1_key", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 30, "Help:2_key", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 45, "End:3_key", Graphics::FontSize::SMALL, Graphics::BLACK);
	}
	else
	{
		THE_GRAPHICS->DrawFont(0, 0, "TITLE2", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 15, "Title1:1_key", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 30, "None Time Mode:2_key", Graphics::FontSize::SMALL, Graphics::BLACK);
		THE_GRAPHICS->DrawFont(0, 45, "1 hand 1 minute:3_key", Graphics::FontSize::SMALL, Graphics::BLACK);

	}
	//THE_FBX->DrawFbx("Box", world);

}
