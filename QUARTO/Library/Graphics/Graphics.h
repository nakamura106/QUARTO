#ifndef GRAHPICS
#define GRAHPICS

#include<d3d9.h>
#include<d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include <Windows.h>
#include <map>



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

	struct CustomVertex2D {
		// 頂点座標
		float x;		// x軸座標
		float y;		// y軸座標
		float z;		// z軸座標

		// 除算数
		float rhw;		// 除算数

		// ポリゴンの色
		DWORD color;	// 色情報

		// テクスチャ座標
		float tu;		// uテクスチャ座標
		float tv;		// vテクスチャ座標
	};

	enum ERenderMode
	{
		NORMAL,		// 書き込み
		ADD,		// 加算
		SUBTRACT,	// 減算
		MULTIPLE,	// 乗算
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

	// 頂点バッファの生成
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices_, UINT size_);

	// インデックスバッファの生成
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces_, UINT size_);

	void ReleaseGraphics();

	void DrawStart();

	void DrawEnd();
	

	//UV描画
	void DrawUIUVTexture(TEXTURE_DATA* texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_);

	/*画像読込
	第一引数はファイルパス
	*/
	bool LoadTexture(const char* file_name_, TEXTURE_DATA* texture_);

	/** LoadTextureのオーバーロード
	* @param[in] file_name_ 読み込むテクスチャのファイルの名前
	* @param[in] key_name_ 読み込むファイルに名前を付ける
	*/
	bool LoadTexture(const std::string file_name_, std::string key_name_);

	//画像まるまる一枚描画
	void DrawTexture(std::string key_, D3DXVECTOR2 pos_);

	/** DrawTextureのオーバーロード
	* @brief 2D用描画関数
	* @param[in] p_texture_ds_ テクスチャのデータ
	* @param[in] pos_ テクスチャの位置(x,y)
	* @param[in] transparency_ テクスチャの透過度
	* @param[in] tex_width テクスチャの横幅
	* @param[in] tex_height テクスチャの縦幅
	*/
	void DrawFadeTexture(
		TEXTURE_DATA* p_texture_,
		D3DXVECTOR2 pos_,
		UCHAR transparency_ = 255,
		int tex_width = NULL,
		int tex_height = NULL);

	/**
	* @brief 2D用アニメーション関数
	* @param[in] p_texture_ds_ テクスチャのデータ
	* @param[in] pos_ テクスチャの位置(x,y)
	* @param[in] split_x_ 横の分割数
	* @param[in] split_y_ 縦の分割数
	* @param[in] animation_graph_num_ アニメーションするテクスチャの番号(左上から右下に向けて)
	*/
	void Animation2D(
		TEXTURE_DATA* p_texture_,
		D3DXVECTOR2 pos_,
		int split_x_,
		int split_y_,
		int animation_graph_num_);

	/*解放関数
	第一引数で指定した画像を解放する
	*/
	void ReleaseTexture(TEXTURE_DATA*);

	/*文字描画
	第一引数、第二引数は座標
	第三引数で指定した文字を描画
	第四引数はサイズ
	第五引数は色
	*/
	void DrawFont(float pos_x_, float pos_y_, const char* text_, FontSize font_type_, FontColor color_);	

	const LPDIRECT3DDEVICE9 GetD3DDevice(void);

	void SetRenderMode(ERenderMode mode_, bool enableAlpa_);

	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_);

	void SetLight();

	TEXTURE_DATA* GetTexture(std::string key_name_) {
		if (HasKeyName(key_name_) == false)
		{
			return nullptr;
		}
		return m_texture_list[key_name_];
	}

    private:
		
		bool CreateGraphicsInterface();
		bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_);
		bool CreateFontDevice();
		bool HasKeyName(std::string key_name_);

	private:
		LPDIRECT3D9 interface_;
		LPDIRECT3DDEVICE9 device_;
		LPD3DXFONT fontlist_[FontSize::FONTSIZE_MAX];

		std::map<std::string, TEXTURE_DATA*> m_texture_list;

};


#endif
