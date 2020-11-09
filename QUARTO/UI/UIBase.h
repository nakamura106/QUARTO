#ifndef UI_BASE_H_
#define UI_BASE_H_

#include <d3dx9.h>

class UIBase
{
public:
	UIBase(D3DXVECTOR2 pos_)
	{
		m_pos = pos_;
	}
	virtual ~UIBase() {}

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	D3DXVECTOR2 m_pos;

};

#endif