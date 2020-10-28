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
	THE_SOUND->SoundBGM("Title");

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
	
	THE_SOUND->Stop("Title");

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
}
