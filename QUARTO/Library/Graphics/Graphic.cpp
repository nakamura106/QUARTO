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
	// インターフェース作成
	Interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (Interface == NULL)
	{
		return false;
	}

	return true;
}

bool Graphics::CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param)
{
	present_param->BackBufferCount = 1;
	present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	present_param->Windowed = true;
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_param->EnableAutoDepthStencil = true;
	present_param->MultiSampleType = D3DMULTISAMPLE_NONE;
	present_param->MultiSampleQuality = 0;

	// デプスとステンシルバッファのフォーマット設定
	present_param->AutoDepthStencilFormat = D3DFMT_D24S8;

	// もしフルスクリーンなら
	if (present_param->Windowed == false)
	{
		present_param->BackBufferWidth = 1920.0f;
		present_param->BackBufferHeight = 1080.0f;

		present_param->FullScreen_RefreshRateInHz = 60.0f;
	}

	if (FAILED(Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&Device)))
	{
		return false;
	}

	return true;
}

IDirect3DVertexBuffer9* Graphics::CreateVertexBuffer(const void* pVertices, UINT size)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// 指定したサイズの頂点バッファを作成
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pVertices, size);
			pVertexBuffer->Unlock();
		}
	}
	return pVertexBuffer;
}

IDirect3DIndexBuffer9* Graphics::CreateIndexBuffer(const UINT16* pIndeces, UINT size)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// 16byte型のインデックスバッファを作成
	if (FAILED(pDevice->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pIndexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pIndeces, size);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}

bool Graphics::SetUpViewPort(D3DPRESENT_PARAMETERS* present_param)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = present_param->BackBufferWidth;
	view_port.Height = present_param->BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(Device->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

void Graphics::ReleaseGraphics()
{
	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		FontList[i]->Release();
	}
	Device->Release();
	Interface->Release();
}

// 描画ステートの設定
void Graphics::SetRenderMode(ERenderMode mode_, bool enableAlpa_)
{
	IDirect3DDevice9* pDevice = GetD3DDevice();
	// αが無向な場合入力されたカラーをそのまま使う
	DWORD srcColorblend = D3DBLEND_ONE;
	DWORD dstColorblend = D3DBLEND_ZERO;
	if (enableAlpa_)
	{
		// αが有効な場合はα値をカラーに影響させる
		srcColorblend = D3DBLEND_SRCALPHA;
		dstColorblend = D3DBLEND_INVSRCALPHA;
		// αテストでα値が0の場合は描画をしないように設定
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}
	// αブレンドとαテストの有無を設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, enableAlpa_);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enableAlpa_);


	switch (mode_)
	{
	case Normal:
		// αが有効 : (SrcColor * 1)  + (DestColor * 0)
		// αが無効 : (SrcColor * α) + (DestColor * (1 - α))
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, dstColorblend);
		break;
	case Add:
		// αが有効：(SrcColor * 1) + (DestColor * 1)
		// αが無効：(SrcColor * α) + (DestColor * 1)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Subtract:
		// αが有効：(DestColor * 1) - (SrcColor * 1)
		// αが無効：(DestColor * 1) - (SrcColor * α)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, srcColorblend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case Multiple:
		// 共通 : (SrcColor * 0) + (DestColor * SrcColor
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
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	Device->BeginScene();
}

void Graphics::DrawEnd()
{
	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}


// テクスチャーの読み込み
bool Graphics::LoadTexture(const char* file_name, TEXTURE_DATA* texture)
{
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(Device,
		file_name,
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
		&texture->Texture)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture->Texture->GetLevelDesc(0, &desc)))
		{
			texture->Texture->Release();
			texture->Texture = NULL;
			return false;
		}
		texture->Width = (float)desc.Width;
		texture->Height = (float)desc.Height;
	}
	return true;
}

void Graphics::DrawTexture(TEXTURE_DATA* texture, D3DXVECTOR2 pos)
{
	CUSTOM_VERTEX bg[4] =
	{
		// 左上頂点
		{ pos.x, pos.y, 0.0f, 1.0f, 0.0f, 0.0f },
		// 右上頂点
		{ pos.x + texture->Width, pos.y, 0.0f, 1.0f, 1.0f, 0.0f },
		// 右下頂点
		{ pos.x + texture->Width, pos.y + texture->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		// 左下頂点
		{ pos.x, pos.y + texture->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	Device->SetTexture(0, texture->Texture);

	Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, bg, sizeof(CUSTOM_VERTEX));
}

//UV用
void Graphics::DrawUVTexture(TEXTURE_DATA * texture, D3DXVECTOR3 pos_, float sprite_width, float sprite_height, float tu, float tv, float Ttu, float Ttv, D3DXVECTOR3 angle, D3DXVECTOR3 scale)
{

	float harf_x = sprite_width / 2.0f;
	float harf_y = sprite_height / 2.0f;

	/*float Ttu = sprite_width / texture->Width;
	float Ttv = sprite_height / texture->Height;*/

	CUSTOM_VERTEX effect[4] =
	{
		{ -harf_x, harf_y, 0.0f,tu, tv },
		{ harf_x, harf_y, 0.0f,tu + Ttu, tv },
		{ harf_x, -harf_y, 0.0f, tu + Ttu, tv + Ttv },
		{ -harf_x, -harf_y, 0.0f, tu, tv + Ttv },
	};

	D3DXMATRIX mat_world, mat_trans, mat_scale, mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;
	D3DXMatrixIdentity(&mat_world);
	//D3DXMatrixIdentity(&mat_trans);

	// 移動
	D3DXMatrixTranslation(&mat_trans, pos_.x, pos_.y, pos_.z);

	D3DXMatrixScaling(&mat_scale, scale.x, scale.y, scale.z);

	D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(angle.x));
	D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(angle.y));
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(angle.z));

	mat_rot = mat_rot_x * mat_rot_y * mat_rot_z;

	mat_world = mat_scale * mat_rot * mat_trans;

	GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat_world);

	GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 頂点構造の指定
	Device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	Device->SetTexture(0, texture->Texture);

	Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, effect, sizeof(CUSTOM_VERTEX));

}

//UV用
void Graphics::DrawUIUVTexture(TEXTURE_DATA * texture, D3DXVECTOR2 pos_, float sprite_width, float sprite_height, float tu, float tv)
{
	float Ttu = sprite_width / texture->Width;
	float Ttv = sprite_height / texture->Height;

	CUSTOM_VERTEX effect[4] =
	{
		{ pos_.x, pos_.y, 0.0f, 1.0f, tu, tv },
		{ pos_.x + sprite_width, pos_.y, 0.0f, 1.0f, tu + Ttu , tv },
		{ pos_.x + sprite_width, pos_.y + sprite_height, 0.0f, 1.0f, tu + Ttu, tv + Ttv},
		{ pos_.x, pos_.y + sprite_height, 0.0f, 1.0f, tu, tv + Ttv },
	};

	// 頂点構造の指定
	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	Device->SetTexture(0, texture->Texture);

	Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, effect, sizeof(CUSTOM_VERTEX));

}

// テクスチャーの解放
void Graphics::ReleaseTexture(TEXTURE_DATA * pTextureData)
{
	if (pTextureData == NULL) return;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (pInfo->texData.Texture == pTextureData->Texture)
		{
			pInfo->count--;
			if (pInfo->count == 0)
			{
				ZeroMemory(pInfo, sizeof(*pInfo));

				SAFE_RELEASE(pTextureData->Texture);
			}
		}
	}
}

//文字描画
void Graphics::DrawFont(float pos_x, float pos_y, const char* text, FontSize font_type, FontColor color)
{
	RECT rect =
	{
		(long)pos_x,
		(long)pos_y,
		(long)pos_x + 400,
		(long)pos_y + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (color == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}
	else if (color == FontColor::Yellow)
	{
		r = 255;
		g = 225;
		b = 0;
	}

	FontList[font_type]->DrawTextA(
		NULL,
		text,
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

	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		if (FAILED(D3DXCreateFont(Device,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("ＭＳ　Ｐゴシック"),
			&FontList[i])))
		{
			return false;
		}
	}

	return true;
}

const LPDIRECT3DDEVICE9 Graphics::GetD3DDevice(void)
{
	return Device;
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
	Device->SetLight(0, &light);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_LIGHTING, false);
}
