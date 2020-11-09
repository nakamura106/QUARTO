#include "NowLoading.h"
#include "../Definition/Definition.h"

void NowLoading::Update()
{
	m_num++;
	if (m_num >= 5)
	{
		m_texnum++;
		m_num = 0;
		if (m_texnum >= 38)
		{
			m_texnum = 0;
		}
	}
}

void NowLoading::Draw()
{
	THE_GRAPHICS->DrawTexture(
		THE_GRAPHICS->GetTexture("loading_background"),
		{ 0.0f,0.0f },
		255);

	THE_GRAPHICS->Animation2D(
		THE_GRAPHICS->GetTexture("now_loading"),
		m_pos,
		38, 1,
		m_texnum);
}