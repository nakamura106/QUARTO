#include "HelpScene.h"
#include"../../../Definition/Definition.h"
#include"../../../Manager/SceneManager.h"
#include"../../Graphics/Graphics.h"
#include"../../Video/Video.h"
#include"../../Input/Input.h"

HelpScene::HelpScene()
{
}

void HelpScene::InitScene()
{
	THE_VIDEO->LoadFile(L"Res/Movie/ƒWƒ‡ƒWƒ‡.avi");
	
	THE_SCENE->SetSceneStep(SceneStep::Main);
	
}

void HelpScene::UpdateScene()
{
	THE_VIDEO->WaitMessage();

	if (THE_INPUT->GetKeyDown(KeyCode::TWO_KEY))
	{
		THE_VIDEO->Play(D3DXVECTOR2(540, 0));
	}
	if (THE_INPUT->GetKeyDown(KeyCode::THREE_KEY))
	{
		THE_VIDEO->Stop();
	}
	if (THE_INPUT->GetKeyDown(KeyCode::ONE_KEY))
	{
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
}

void HelpScene::EndScene()
{
	THE_VIDEO->Stop();
	THE_SCENE->SetSceneStep(SceneStep::Init);
	THE_SCENE->SetSceneId(SceneId::Title);
}

void HelpScene::Draw()
{
	THE_GRAPHICS->DrawFont(0,0,"Help",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
	THE_GRAPHICS->DrawFont(0,15,"Title:1_key",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
	THE_GRAPHICS->DrawFont(0,30,"MovieStart:2_key",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
	THE_GRAPHICS->DrawFont(0,45,"MovieStop:3_key",Graphics::FontSize::SMALL,Graphics::FontColor::BLACK);
}
