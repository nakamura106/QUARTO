#include"Graphics.h"
#include"../Engine/Engine.h"

bool Graphics::InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false)
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}
	if (CreateFontDevice() == false)
	{
		return false;
	}

	return true;
}

bool Graphics::CreateGraphicsInterface()
{
	// �C���^�[�t�F�[�X�쐬
	interface_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (interface_ == NULL)
	{
		return false;
	}

	return true;
}

bool Graphics::CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_)
{
	present_param_->BackBufferCount = 1;
	present_param_->BackBufferFormat = D3DFMT_A8R8G8B8;
	present_param_->Windowed = false;
	present_param_->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_param_->EnableAutoDepthStencil = true;
	present_param_->MultiSampleType = D3DMULTISAMPLE_NONE;
	present_param_->MultiSampleQuality = 0;

	// �f�v�X�ƃX�e���V���o�b�t�@�̃t�H�[�}�b�g�ݒ�
	present_param_->AutoDepthStencilFormat = D3DFMT_D24S8;

	// �����t���X�N���[���Ȃ�
	if (present_param_->Windowed == false)
	{
		present_param_->BackBufferWidth = 1920.0f;
		present_param_->BackBufferHeight = 1080.0f;

		present_param_->FullScreen_RefreshRateInHz = 60.0f;
	}

	if (FAILED(interface_->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param_,
		&device_)))
	{
		return false;
	}

	return true;
}

IDirect3DVertexBuffer9* Graphics::CreateVertexBuffer(const void* pVertices_, UINT size_)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// �w�肵���T�C�Y�̒��_�o�b�t�@���쐬
	if (FAILED(pDevice->CreateVertexBuffer(size_, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices_)
	{
		void* pData;
		// �o�b�t�@�����b�N���ăf�[�^����������
		if (SUCCEEDED(pVertexBuffer->Lock(0, size_, &pData, 0)))
		{
			memcpy(pData, pVertices_, size_);
			pVertexBuffer->Unlock();
		}
	}
	return pVertexBuffer;
}

IDirect3DIndexBuffer9* Graphics::CreateIndexBuffer(const UINT16* pIndeces_, UINT size_)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// 16byte�^�̃C���f�b�N�X�o�b�t�@���쐬
	if (FAILED(pDevice->CreateIndexBuffer(size_, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces_)
	{
		void* pData;
		// �o�b�t�@�����b�N���ăf�[�^����������
		if (SUCCEEDED(pIndexBuffer->Lock(0, size_, &pData, 0)))
		{
			memcpy(pData, pIndeces_, size_);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}

bool Graphics::SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_)
{
	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param_->BackBufferWidth;
	view_port.Height = present_param_->BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(device_->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void Graphics::ReleaseGraphics()
{
	for (int i = 0; i < FontSize::FONTSIZE_MAX; i++)
	{
		fontlist_[i]->Release();
	}
	device_->Release();
	interface_->Release();
}

// �`��X�e�[�g�̐ݒ�
void Graphics::SetRenderMode(ERenderMode mode_, bool enableAlpa_)
{
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// ���������ȏꍇ���͂��ꂽ�J���[�����̂܂܎g��
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpa_)
	{
		// �����L���ȏꍇ�̓��l���J���[�ɉe��������
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// ���e�X�g�Ń��l��0�̏ꍇ�͕`������Ȃ��悤�ɐݒ�
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// ���u�����h�ƃ��e�X�g�̗L����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpa_);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpa_);


	switch (mode_)
	{
	case NORMAL:
		// �����L�� : (SrcColor * 1)  + (DestColor * 0)
		// �������� : (SrcColor * ��) + (DestColor * (1 - ��))
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case ADD:
		// �����L���F(SrcColor * 1) + (DestColor * 1)
		// ���������F(SrcColor * ��) + (DestColor * 1)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case SUBTRACT:
		// �����L���F(DestColor * 1) - (SrcColor * 1)
		// ���������F(DestColor * 1) - (SrcColor * ��)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case MULTIPLE:
		// ���� : (SrcColor * 0) + (DestColor * SrcColor
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	default:
		break;
	}
}

void Graphics::DrawStart()
{
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);
	SetLight();
	device_->BeginScene();
}

void Graphics::DrawEnd()
{
	device_->EndScene();
	device_->Present(NULL, NULL, NULL, NULL);
}


// �e�N�X�`���[�̓ǂݍ���
bool Graphics::LoadTexture(const char* file_name_, TEXTURE_DATA* texture_)
{
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name_, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(device_,
		file_name_,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_->texture)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture_->texture->GetLevelDesc(0, &desc)))
		{
			texture_->texture->Release();
			texture_->texture = NULL;
			return false;
		}
		texture_->width = (float)desc.Width;
		texture_->height = (float)desc.Height;
	}
	return true;
}

void Graphics::DrawTexture(TEXTURE_DATA* texture_, D3DXVECTOR2 pos_)
{
	CUSTOM_VERTEX bg[4] =
	{
		// ���㒸�_
		{ pos_.x, pos_.y, 0.0f, 1.0f, 0.0f, 0.0f },
		// �E�㒸�_
		{ pos_.x + texture_->width, pos_.y, 0.0f, 1.0f, 1.0f, 0.0f },
		// �E�����_
		{ pos_.x + texture_->width, pos_.y + texture_->height, 0.0f, 1.0f, 1.0f, 1.0f },
		// �������_
		{ pos_.x, pos_.y + texture_->height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	device_->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	device_->SetTexture(0, texture_->texture);

	device_->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bg, sizeof(CUSTOM_VERTEX));
}

//UV�p
void Graphics::DrawUVTexture(TEXTURE_DATA * texture_, D3DXVECTOR3 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_, float Ttu_, float Ttv_, D3DXVECTOR3 angle_, D3DXVECTOR3 scale_)
{

	float harf_x = sprite_width_ / 2.0f;
	float harf_y = sprite_height_ / 2.0f;

	/*float Ttu_ = sprite_width_ / texture_->width;
	float Ttv_ = sprite_height_ / texture_->height;*/

	CUSTOM_VERTEX effect[4] =
	{
		{ -harf_x, harf_y, 0.0f,tu_, tv_ },
		{ harf_x, harf_y, 0.0f,tu_ + Ttu_, tv_ },
		{ harf_x, -harf_y, 0.0f, tu_ + Ttu_, tv_ + Ttv_ },
		{ -harf_x, -harf_y, 0.0f, tu_, tv_ + Ttv_ },
	};

	D3DXMATRIX mat_world, mat_trans, mat_scale, mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;
	D3DXMatrixIdentity(&mat_world);
	//D3DXMatrixIdentity(&mat_trans);

	// �ړ�
	D3DXMatrixTranslation(&mat_trans, pos_.x, pos_.y, pos_.z);

	D3DXMatrixScaling(&mat_scale, scale_.x, scale_.y, scale_.z);

	D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(angle_.x));
	D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(angle_.y));
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(angle_.z));

	mat_rot = mat_rot_x * mat_rot_y * mat_rot_z;

	mat_world = mat_scale * mat_rot * mat_trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat_world);

	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���_�\���̎w��
	device_->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	device_->SetTexture(0, texture_->texture);

	device_->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, effect, sizeof(CUSTOM_VERTEX));

}

//UV�p
void Graphics::DrawUIUVTexture(TEXTURE_DATA * texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_)
{
	float Ttu = sprite_width_ / texture_->width;
	float Ttv = sprite_height_ / texture_->height;

	CUSTOM_VERTEX effect[4] =
	{
		{ pos_.x, pos_.y, 0.0f, 1.0f, tu_, tv_ },
		{ pos_.x + sprite_width_, pos_.y, 0.0f, 1.0f, tu_ + Ttu , tv_ },
		{ pos_.x + sprite_width_, pos_.y + sprite_height_, 0.0f, 1.0f, tu_ + Ttu, tv_ + Ttv},
		{ pos_.x, pos_.y + sprite_height_, 0.0f, 1.0f, tu_, tv_ + Ttv },
	};

	// ���_�\���̎w��
	device_->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	device_->SetTexture(0, texture_->texture);

	device_->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, effect, sizeof(CUSTOM_VERTEX));

}

// �e�N�X�`���[�̉��
void Graphics::ReleaseTexture(TEXTURE_DATA * texture_data_ptr_)
{
	if (texture_data_ptr_ == NULL) return;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &loaded_textures_[i];
		if (pInfo->count == 0) continue;

		if (pInfo->tex_data.texture == texture_data_ptr_->texture)
		{
			pInfo->count--;
			if (pInfo->count == 0)
			{
				ZeroMemory(pInfo, sizeof(*pInfo));

				SAFE_RELEASE(texture_data_ptr_->texture);
			}
		}
	}
}

//�����`��
void Graphics::DrawFont(float pos_x_, float pos_y_, const char* text_, FontSize font_type_, FontColor color_)
{
	RECT rect =
	{
		(long)pos_x_,
		(long)pos_y_,
		(long)pos_x_ + 400,
		(long)pos_y_ + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color_ == FontColor::BLACK)
	{
		r = g = b = 0;
	}
	else if (color_ == FontColor::RED)
	{
		r = 255;
		g = b = 0;
	}
	else if (color_ == FontColor::YELLOW)
	{
		r = 255;
		g = 225;
		b = 0;
	}

	fontlist_[font_type_]->DrawTextA(
		NULL,
		text_,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}


bool Graphics::CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for (int i = 0; i < FontSize::FONTSIZE_MAX; i++)
	{
		if (FAILED(D3DXCreateFont(device_,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("�l�r�@�o�S�V�b�N"),
			&fontlist_[i])))
		{
			return false;
		}
	}

	return true;
}

const LPDIRECT3DDEVICE9 Graphics::GetD3DDevice(void)
{
	return device_;
}

void Graphics::SetLight()
{
	D3DLIGHT9 light;
	D3DXVECTOR3 vec_direction(0, 0, 1);
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction.x = 0.0f;
	light.Direction.y = -0.5f;
	light.Direction.z = 0.2f;
	light.Diffuse.a = 1.0f;
	light.Diffuse.r = 0.8f;
	light.Diffuse.g = 0.8f;
	light.Diffuse.b = 0.8f;
	light.Ambient.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	D3DXVec3Normalize((D3DXVECTOR3*)& light.Direction, &vec_direction);
	light.Range = 200.0f;
	device_->SetLight(0, &light);
	device_->LightEnable(0, true);
	device_->SetRenderState(D3DRS_LIGHTING, false);
}
