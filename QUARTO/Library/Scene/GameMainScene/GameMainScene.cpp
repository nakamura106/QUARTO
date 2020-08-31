#include "GameMainScene.h"
#include"../../../Definition/Definition.h"
#include"../../FBX/FBX.h"
#include"../../Sound/Sound.h"
#include"../../Input/Input.h"

GameMainScene::GameMainScene()
{
	
}

void GameMainScene::InitScene()
{
	THE_SOUND->SoundBGM("Game");

	GameState = MainStatus::Game;
	CoE = ContinueorEnd::Continue;
	//THE_GRAPHICS->LoadTexture("Res/Tex/END.png",&tex);
	THE_SCENE->SetSceneStep(SceneStep::Main);
}

void GameMainScene::UpdateScene()
{
	if (THE_INPUT->GetKeyDown(KeyCode::ONE_KEY)&&GameState == MainStatus::Game)
	{
		THE_SOUND->Stop("Game");
		THE_SOUND->SoundBGM("Result");
		GameState = MainStatus::Result;
	}
	else if (THE_INPUT->GetKeyDown(KeyCode::ONE_KEY) && GameState == MainStatus::Result)
	{
		CoE = ContinueorEnd::Continue;
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
	else if (THE_INPUT->GetKeyDown(KeyCode::TWO_KEY)&& GameState == MainStatus::Result)
	{
		CoE = ContinueorEnd::End;
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
}

void GameMainScene::EndScene()
{
	THE_SOUND->Stop("Result");
	//THE_GRAPHICS->ReleaseTexture(&tex);
	THE_SCENE->SetSceneStep(SceneStep::Init);
	if (CoE == ContinueorEnd::End)
	{
		THE_SCENE->SetSceneId(SceneId::Title);
	}
	else if (CoE == ContinueorEnd::Continue)
	{
		THE_SCENE->SetSceneId(SceneId::Game);
	}
}

void GameMainScene::Draw()
{
	//THE_GRAPHICS->DrawTexture(&tex, D3DXVECTOR2(0, 0));
	if (GameState == MainStatus::Game)
	{
		THE_GRAPHICS->DrawFont(0, 0, "GameMain", Graphics::FontSize::SMALL, Graphics::FontColor::BLACK);
		THE_GRAPHICS->DrawFont(0, 15, "Result:1_key", Graphics::FontSize::SMALL, Graphics::FontColor::BLACK);
	}
	else if (GameState == MainStatus::Result)
	{
		THE_GRAPHICS->DrawFont(0, 0, "Result", Graphics::FontSize::SMALL, Graphics::FontColor::BLACK);
		THE_GRAPHICS->DrawFont(0, 15, "Continue:1_key", Graphics::FontSize::SMALL, Graphics::FontColor::BLACK);
		THE_GRAPHICS->DrawFont(0, 30, "End:2_key", Graphics::FontSize::SMALL, Graphics::FontColor::BLACK);
	}
	
}
