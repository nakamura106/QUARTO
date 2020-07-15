#ifndef GRAHPICS
#define GRAHPICS

#include<d3d9.h>
#include<d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include <Windows.h>



// 解放
#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }

// 解放処理用のマクロを定義
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }


#define SMALL_FONT_SIZE (16)	//!< フォントサイズ(小)
#define REGULAR_FONT_SIZE (60)	//!< フォントサイズ(中)
#define LARGE_FONT_SIZE (120)	//!< フォントサイズ(大)
#define	TEXTURE_MAX	1000

class Graphics
{
public:
	struct TEXTURE_DATA
	{
		LPDIRECT3DTEXTURE9 Texture;
		float Width;
		float Height;
	};

	struct LoadedTextureInfo
	{
		char		filename[MAX_PATH];
		int			count;
		TEXTURE_DATA texData;
	}loadedTextures[TEXTURE_MAX] = {};

	struct Size
	{
		Size()
		{
			Width = 0.0f;
			Height = 0.0f;
		}

		Size(float width, float height)
		{
			Width = width;
			Height = height;
		}

		Size(const Size& size)
		{
			this->Width = size.Width;
			this->Height = size.Height;
		}

		float Width;
		float Height;
	};

	struct CUSTOM_VERTEX
	{
		float x;
		float y;
		float z;
		float rhw;
		float tu;
		float tv;
	};

	enum ERenderMode
	{
		Normal,		// 書き込み
		Add,		// 加算
		Subtract,	// 減算
		Multiple,	// 乗算
	};

	enum FontColor
	{
		Black,
		White,
		Red,
		Yellow,
	};

	enum FontSize
	{
		Small,
		Regular,
		Large,
		FontSizeMax,
	};

public:
	void SetRenderMode(ERenderMode mode_, bool enableAlpa_);

	bool InitGraphics();

	void ReleaseGraphics();

	bool CreateGraphicsInterface();

	bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param);

	// 頂点バッファの生成
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size);
	// インデックスバッファの生成
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size);

	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);

	void DrawStart();

	void DrawEnd();

	
	void DrawUVTexture(TEXTURE_DATA* texture, D3DXVECTOR3 pos_, float sprite_width, float sprite_height, float tu, float tv, float Ttu, float Ttv, D3DXVECTOR3 angle, D3DXVECTOR3 scale);

	void DrawUIUVTexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos_, float sprite_width, float sprite_height, float tu, float tv);

	bool LoadTexture(const char* file_name, TEXTURE_DATA* texture);

	void DrawTexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos);

	void ReleaseTexture(TEXTURE_DATA*);

	void DrawFont(float pos_x, float pos_y, const char* text, FontSize font_type, FontColor color);

	bool CreateFontDevice();

	const LPDIRECT3DDEVICE9 GetD3DDevice(void);

	void SetLight();

	private:
		LPDIRECT3D9 Interface;
		LPDIRECT3DDEVICE9 Device;
		LPD3DXFONT FontList[FontSize::FontSizeMax];

};


#endif
