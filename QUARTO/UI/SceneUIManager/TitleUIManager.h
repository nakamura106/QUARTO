#ifndef TITLE_UI_MANAGER_H_
#define TITLE_UI_MANAGER_H_

#include "SceneUIManager.h"

class TitleUIManager :public SceneUIManager
{
public:
	TitleUIManager()
	{
		m_transparency = 0;
	}
	virtual ~TitleUIManager()
	{

	}

public:
	virtual bool CreateUI()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void AllDelete()override;

	bool FadeOut();

private:
	int m_transparency;		// “§‰ßˆ——p

};

#endif