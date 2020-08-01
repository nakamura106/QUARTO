#include "HelpScene.h"
#include"../../../Definition/Definition.h"
#include"../../../Manager/SceneManager.h"
#include"../../Graphics/Graphics.h"
#include"../../Input/Input.h"

HelpScene::HelpScene()
{
}

void HelpScene::InitScene()
{
	THE_SCENE->SetSceneStep(SceneStep::Main);
}

void HelpScene::UpdateScene()
{
	if (THE_INPUT->GetKeyDown(KeyCode::ONE_KEY))
	{
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
}

void HelpScene::EndScene()
{
	THE_SCENE->SetSceneStep(SceneStep::Init);
	THE_SCENE->SetSceneId(SceneId::Title);
}

void HelpScene::Draw()
{
	THE_GRAPHICS->DrawFont(0,0,"Help",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
	THE_GRAPHICS->DrawFont(0,15,"Title:1_key",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
}
