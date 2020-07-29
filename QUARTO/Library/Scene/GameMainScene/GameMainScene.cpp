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
	THE_GRAPHICS->LoadTexture("Res/Tex/END.png",&tex);
	THE_SCENE->SetSceneStep(SceneStep::Main);
}

void GameMainScene::UpdateScene()
{
	if (THE_INPUT->GetKeyDown(KeyCode::F_KEY))
	{
		THE_SCENE->SetSceneStep(SceneStep::End);
	}
}

void GameMainScene::EndScene()
{
	THE_GRAPHICS->ReleaseTexture(&tex);
	THE_SCENE->SetSceneStep(SceneStep::Init);
	THE_SCENE->SetSceneId(SceneId::Title);
}

void GameMainScene::Draw()
{
	//THE_GRAPHICS->DrawTexture(&tex, D3DXVECTOR2(0, 0));
}
