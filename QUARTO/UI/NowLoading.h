#ifndef NOW_LOADING_H_
#define NOW_LOADING_H_

#include "UIBase.h"

class NowLoading :public UIBase
{
public:
	NowLoading(D3DXVECTOR2 pos_) :
		UIBase(pos_)
	{
		m_num = 0;
		m_texnum = 0;
	}
	virtual ~NowLoading() {}

public:
	virtual void Update()override;
	virtual void Draw()override;

private:
	int m_num;
	int m_texnum;

};

#endif