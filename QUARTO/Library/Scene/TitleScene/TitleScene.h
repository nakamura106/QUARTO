#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"../BaseScene.h"
#include"../../Graphics/Graphics.h"



class TitleScene :public BaseScene
{
public:
	enum class TitleState
	{
		title,
		Help,
		Game,
		End,
	};

	enum class TitleNum
	{
		Title1,
		Title2,
	};
private:
private:
	D3DXVECTOR3 pos = D3DXVECTOR3(0, -1, 0);
	D3DXMATRIX world;
	D3DXMATRIX move;
	D3DXMATRIX scale;

	struct TitleInfo
	{
		TitleState title_state;
		TitleNum title_num;
	}title_info;

	Graphics::TEXTURE_DATA tex;


public:
	TitleScene();

	void InitScene()override;
	void UpdateScene()override;
	void EndScene()override;

	const TitleInfo* GetTitleInfo()const { return &title_info; }

	void Draw()override;




};


#endif // !TITLESCENE_H_
