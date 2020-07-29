#ifndef GRAHPICS
#define GRAHPICS

#include<d3d9.h>
#include<d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include <Windows.h>



// ���
#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }

// ��������p�̃}�N�����`
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }


#define SMALL_FONT_SIZE (16)	//!< �t�H���g�T�C�Y(��)
#define REGULAR_FONT_SIZE (60)	//!< �t�H���g�T�C�Y(��)
#define LARGE_FONT_SIZE (120)	//!< �t�H���g�T�C�Y(��)
#define	TEXTURE_MAX	1000

class Graphics
{
public:
	struct TEXTURE_DATA
	{
		LPDIRECT3DTEXTURE9 texture;
		float width;
		float height;
	};

	struct LoadedTextureInfo
	{
		char		filename[MAX_PATH];
		int			count;
		TEXTURE_DATA tex_data;
	}loaded_textures_[TEXTURE_MAX] = {};

	struct Size
	{
		Size()
		{
			width = 0.0f;
			height = 0.0f;
		}

		Size(float width_, float height_)
		{
			width = width_;
			height = height_;
		}

		Size(const Size& size)
		{
			this->width = size.width;
			this->height = size.height;
		}

		float width;
		float height;
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
		NORMAL,		// ��������
		ADD,		// ���Z
		SUBTRACT,	// ���Z
		MULTIPLE,	// ��Z
	};

	enum FontColor
	{
		BLACK,
		WHITE,
		RED,
		YELLOW,
	};

	enum FontSize
	{
		SMALL,
		REGULAR,
		LARGE,
		FONTSIZE_MAX,
	};

public:
	
	bool InitGraphics();

	// ���_�o�b�t�@�̐���
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices_, UINT size_);

	// �C���f�b�N�X�o�b�t�@�̐���
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces_, UINT size_);

	void ReleaseGraphics();

	void DrawStart();

	void DrawEnd();
	
	void DrawUVTexture(TEXTURE_DATA* texture_, D3DXVECTOR3 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_, float Ttu_, float Ttv_, D3DXVECTOR3 angle_, D3DXVECTOR3 scale_);

	void DrawUIUVTexture(TEXTURE_DATA* texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_);

	bool LoadTexture(const char* file_name_, TEXTURE_DATA* texture_);

	void DrawTexture(TEXTURE_DATA* texture_, D3DXVECTOR2 pos_);

	void ReleaseTexture(TEXTURE_DATA*);

	void DrawFont(float pos_x_, float pos_y_, const char* text_, FontSize font_type_, FontColor color_);	

	const LPDIRECT3DDEVICE9 GetD3DDevice(void);

	void SetRenderMode(ERenderMode mode_, bool enableAlpa_);

	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_);

	void SetLight();

    private:
		
		bool CreateGraphicsInterface();
		bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_);
		bool CreateFontDevice();
		

	private:
		LPDIRECT3D9 interface_;
		LPDIRECT3DDEVICE9 device_;
		LPD3DXFONT fontlist_[FontSize::FONTSIZE_MAX];

};


#endif
