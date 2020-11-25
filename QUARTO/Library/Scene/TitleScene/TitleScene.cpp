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
	

	title_info.title_num = TitleNum::Title1;
	title_info.title_state = TitleState::title;

	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scale, 250, 350, 250);
	D3DXMatrixTranslation(&move, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &scale, &move);

	THE_SCENE->SetSceneStep(SceneStep::Main);

	// シャン追加 //
	m_p_now_loading = new NowLoading({ 1700.0f, 860.0f });
	m_p_title_ui_manager = new TitleUIManager();

	m_load_finished = false;
	m_fadeout = false;

	// マルチスレッド作成
	m_thread_handle = CreateThread(
		NULL,
		0,
		Load,
		NULL,
		0,
		&m_dw_thread_id
	);


	// //

}

// シャン追加 //
DWORD __stdcall TitleScene::Load(LPVOID param_)
{
	// タイトルシーンに必要なテクスチャ全部
	THE_GRAPHICS->LoadTexture("Res/Tex/Title/BG.png","BG");
	// デバッグ用
	Sleep(1000);

	return 0;
}
// //

void TitleScene::UpdateScene()
{
	// シャン追加 //
	if (m_load_finished == false)
	{
		if (WaitForSingleObject(m_thread_handle, 0) != WAIT_OBJECT_0)
		{
			m_p_now_loading->Update();
			return;
		}
		// 下記に必要なオブジェクトまたはUIなどを作成


		m_load_finished = true;
	}

	if (m_fadeout == true)
	{
		if (m_p_title_ui_manager->FadeOut())
		{
			title_info.title_state = TitleState::Game;
			m_fadeout = false;
		}
		return;
	}
	// //

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
			m_fadeout = true;
			//title_info.title_state = TitleState::Game;
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
			m_fadeout = true;
			//title_info.title_state = TitleState::Game;
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
	// シャン追加 //
	if (WaitForSingleObject(m_thread_handle, 0) != WAIT_OBJECT_0)
	{
		m_p_now_loading->Draw();
		return;
	}

	THE_GRAPHICS->DrawTexture("BG", D3DXVECTOR2(0, 0));
	// //

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