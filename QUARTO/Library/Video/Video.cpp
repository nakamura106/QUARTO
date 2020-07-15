#include"Video.h"

Video::Video()
{
	InitCom();
	MediaControl();
	MediaEvent();
}

HRESULT Video::InitCom()
{
	hRes = CoInitialize(NULL);
	if (FAILED(hRes))
	{
		return false;
	}
	hRes = CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&m_Graph
	);

	if (FAILED(hRes))
		return hRes;
}

HRESULT Video::MediaControl()
{
	hRes = m_Graph->QueryInterface(IID_IMediaControl, (void**)&m_Control);
	if (FAILED(hRes))
		return hRes;
}

HRESULT Video::MediaEvent()
{
	hRes = m_Graph->QueryInterface(IID_IMediaEvent, (void**)&m_Event);
	if (FAILED(hRes))
		return hRes;
}

HRESULT Video::Load(std::string filename_)
{
	hRes = m_Graph->RenderFile(L"Res/Movie/【PS3】-El-Shaddai-エルシャダイ-　_ルシフェルver_-高画質版.avi", NULL);
	if (FAILED(hRes))
		return hRes;
}

void Video::Play(int time_)
{
	if (SUCCEEDED(hRes))
	{
		hRes = m_Control->Run();
		if (SUCCEEDED(hRes))
		{
			long pEvCode;
			hRes = m_Event->WaitForCompletion(INFINITE, &pEvCode);
		}
	}

	if (m_Control != NULL)
	{
		m_Control->Stop();

		m_Control->Release();
	}
	if (m_Event != NULL)
	{
		m_Event->Release();
	}
	if (m_Graph != NULL)
	{
		m_Graph->Release();
	}
	

	CoUninitialize();
}

