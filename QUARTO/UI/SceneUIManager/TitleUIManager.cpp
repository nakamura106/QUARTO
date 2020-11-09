#include "../SceneUIManager/TitleUIManager.h"
#include "../../Definition/Definition.h"

bool TitleUIManager::CreateUI()
{
	return false;
}

void TitleUIManager::Update()
{
	
}

bool TitleUIManager::FadeOut()
{
	++m_transparency;
	if (m_transparency >= 255)
	{
		return true;
	}
	return false;
}

void TitleUIManager::Draw()
{
	// フェードアウト用
	THE_GRAPHICS->DrawTexture(
		THE_GRAPHICS->GetTexture("loading_background"),
		{ 0.0f,0.0f },
		m_transparency);
}

void TitleUIManager::AllDelete()
{
}