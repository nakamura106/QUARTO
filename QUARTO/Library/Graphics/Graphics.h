#ifndef GRAHPICS
#define GRAHPICS

#include<d3d9.h>
#include<d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include <Windows.h>
#include <map>



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

	struct CustomVertex2D {
		// ���_���W
		float x;		// x�����W
		float y;		// y�����W
		float z;		// z�����W

		// ���Z��
		float rhw;		// ���Z��

		// �|���S���̐F
		DWORD color;	// �F���

		// �e�N�X�`�����W
		float tu;		// u�e�N�X�`�����W
		float tv;		// v�e�N�X�`�����W
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
	

	//UV�`��
	void DrawUIUVTexture(TEXTURE_DATA* texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_);

	/*�摜�Ǎ�
	�������̓t�@�C���p�X
	*/
	bool LoadTexture(const char* file_name_, TEXTURE_DATA* texture_);

	/** LoadTexture�̃I�[�o�[���[�h
	* @param[in] file_name_ �ǂݍ��ރe�N�X�`���̃t�@�C���̖��O
	* @param[in] key_name_ �ǂݍ��ރt�@�C���ɖ��O��t����
	*/
	bool LoadTexture(const std::string file_name_, std::string key_name_);

	//�摜�܂�܂�ꖇ�`��
	void DrawTexture(std::string key_, D3DXVECTOR2 pos_);

	/** DrawTexture�̃I�[�o�[���[�h
	* @brief 2D�p�`��֐�
	* @param[in] p_texture_ds_ �e�N�X�`���̃f�[�^
	* @param[in] pos_ �e�N�X�`���̈ʒu(x,y)
	* @param[in] transparency_ �e�N�X�`���̓��ߓx
	* @param[in] tex_width �e�N�X�`���̉���
	* @param[in] tex_height �e�N�X�`���̏c��
	*/
	void DrawFadeTexture(
		TEXTURE_DATA* p_texture_,
		D3DXVECTOR2 pos_,
		UCHAR transparency_ = 255,
		int tex_width = NULL,
		int tex_height = NULL);

	/**
	* @brief 2D�p�A�j���[�V�����֐�
	* @param[in] p_texture_ds_ �e�N�X�`���̃f�[�^
	* @param[in] pos_ �e�N�X�`���̈ʒu(x,y)
	* @param[in] split_x_ ���̕�����
	* @param[in] split_y_ �c�̕�����
	* @param[in] animation_graph_num_ �A�j���[�V��������e�N�X�`���̔ԍ�(���ォ��E���Ɍ�����)
	*/
	void Animation2D(
		TEXTURE_DATA* p_texture_,
		D3DXVECTOR2 pos_,
		int split_x_,
		int split_y_,
		int animation_graph_num_);

	/*����֐�
	�������Ŏw�肵���摜���������
	*/
	void ReleaseTexture(TEXTURE_DATA*);

	/*�����`��
	�������A�������͍��W
	��O�����Ŏw�肵��������`��
	��l�����̓T�C�Y
	��܈����͐F
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
