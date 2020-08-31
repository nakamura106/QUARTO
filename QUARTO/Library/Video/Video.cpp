#include"Video.h"
#include"../Engine/Engine.h"
#include"../../Definition/Definition.h"
#include"../Input/Input.h"

#define _WIN32_DCOM

//Video::Video()
//{
//	InitCom();
//	InitVmr();	
//	FilterConnection();
//	MediaControl();
//	MediaEvent();
//}
//
//HRESULT Video::InitCom()
//{
//	h_res_ = CoInitialize(NULL);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//	h_res_ = CoCreateInstance(
//		CLSID_FilterGraph,
//		NULL,
//		CLSCTX_INPROC_SERVER,
//		IID_IGraphBuilder,
//		(void**)&graph_
//	);
//
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//	h_res_ = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)& graph2_);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//	h_res_ = graph2_->SetFiltergraph(graph_);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//}
//
//HRESULT Video::InitVmr()
//{
//	h_res_ = CoCreateInstance(CLSID_VideoMixingRenderer9,NULL,
//		CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void**)& pVMR9);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//
//	graph_->AddFilter(pVMR9, L"VMR9");
//	pVMR9->QueryInterface(IID_IVMRFilterConfig9,(void**)&pVMRCfg);
//	pVMRCfg->SetRenderingMode(VMRMode_Windowless);
//	WindowSpecification();
//	pVMRCfg->Release();
//}
//
//void Video::WindowSpecification()
//{
//	pVMR9->QueryInterface(IID_IVMRWindowlessControl9, (void**)& pVMRWndCont);
//	pVMRWndCont->SetVideoClippingWindow(THE_ENGINE->GetWindowHandle());
//	SizeSpecification();
//}
//
//void Video::SizeSpecification()
//{
//	h_res_ = pVMRWndCont->GetNativeVideoSize(&W,&H,NULL,NULL);
//	SetRect(&SrcR,0,0,W,H);
//	GetClientRect(THE_ENGINE->GetWindowHandle(),&DestR);
//	h_res_ = pVMRWndCont->SetVideoPosition(&SrcR,&DestR);
//	pVMRWndCont->Release();
//}
//
//void Video::FilterConnection()
//{
//	graph2_->RenderStream(0,0,pSource,0,pVMR9);
//}
//
//HRESULT Video::MediaControl()
//{
//	h_res_ = graph_->QueryInterface(IID_IMediaControl, (void**)&control_);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//}
//
//HRESULT Video::MediaEvent()
//{
//	h_res_ = graph_->QueryInterface(IID_IMediaEvent, (void**)&event_);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//}
//
//HRESULT Video::Load(LPCWCHAR filename_)
//{
//	WCHAR wfilename[] = L"Res/Movie/【PS3】-El-Shaddai-エルシャダイ-　_ルシフェルver_-高画質版.avi";
//	h_res_ = graph_->AddSourceFilter(wfilename, wfilename, &pSource);
//	//h_res_ = graph_->RenderFile(filename_, NULL);
//	if (FAILED(h_res_))
//	{
//		return h_res_;
//	}
//}
//
//void Video::Play(int time_)
//{
//	if (SUCCEEDED(h_res_))
//	{
//		h_res_ = control_->Run();
//		if (SUCCEEDED(h_res_))
//		{
//			long pEvCode;
//			h_res_ = event_->WaitForCompletion(INFINITE, &pEvCode);
//		}
//	}
//
//	if (control_ != NULL)
//	{
//		control_->Stop();
//
//		control_->Release();
//	}
//	if (event_ != NULL)
//	{
//		event_->Release();
//	}
//	if (graph_ != NULL)
//	{
//		graph_->Release();
//	}
//	if (pVMR9 != NULL)
//	{
//		pVMR9->Release();
//	}
//	
//
//	CoUninitialize();
//}
//



Videoclass::Videoclass()
{
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		int a = 0;
	}
	InitInterface();
}

Videoclass::~Videoclass()
{
	if (pVideoWindow != NULL)
	{
		pVideoWindow->Release();
		pVideoWindow = NULL;
	}
	if (pMediaPosition != NULL)
	{
		pMediaPosition->Release();
		pMediaPosition = NULL;

	}	
	if (pMediaEvent != NULL)
	{
		pMediaEvent->Release();
		pMediaEvent = NULL;
	}
	if (pMediaControl != NULL)
	{
		pMediaControl->Release();
		pMediaControl = NULL;
	}
	if (pGraphBuilder != NULL)
	{
		pGraphBuilder->Release();
		pGraphBuilder = NULL;
	}
	CoUninitialize();
}

void Videoclass::InitInterface()
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)& pGraphBuilder);
	if (FAILED(hr))
	{
		return;
	}
	hr = pGraphBuilder->QueryInterface(IID_IMediaControl, (LPVOID*)& pMediaControl);
	if (FAILED(hr))
	{
		return;
	}
	hr = pGraphBuilder->QueryInterface(IID_IMediaEventEx, (LPVOID*)& pMediaEvent);
	if (FAILED(hr))
	{
		return;
	}
	hr = pGraphBuilder->QueryInterface(IID_IMediaPosition, (LPVOID*)& pMediaPosition);
	if (FAILED(hr))
	{
		return;
	}
	hr = pGraphBuilder->QueryInterface(IID_IVideoWindow, (LPVOID*) &pVideoWindow);
	if (FAILED(hr))
	{
		return;
	}
	pGraphBuilder->Release();
}

void Videoclass::LoadFile(LPCWCHAR filename_)
{
	HRESULT hr;
	BSTR str = SysAllocString(filename_);
	hr = pMediaControl->RenderFile(str);
	if (FAILED(hr))
	{
		return;
	}
	SetMessage();
}

void Videoclass::SetMessage()
{
	HRESULT hr;
	hr= pMediaEvent->SetNotifyWindow((OAHWND)THE_ENGINE->GetWindowHandle(), nGraphNotifyMsg, NULL);
	if (FAILED(hr))
	{
		return;
	}
}

void Videoclass::SetWind()
{	

	HRESULT hr;

	hr = pVideoWindow->put_Owner((OAHWND)THE_ENGINE->GetWindowHandle());
	if (FAILED(hr))
	{
		return;
	}
//	hr = pVideoWindow->put_WindowStyle(WS_CHILD);
	hr = pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->put_Visible(OAFALSE);
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->SetWindowForeground(OATRUE);
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->put_FullScreenMode(OAFALSE);
	if (FAILED(hr))
	{
		return;
	}

	
}

void Videoclass::Play(D3DXVECTOR2 pos_)
{
	HRESULT hr;

	SetWind();
	hr=pVideoWindow->SetWindowPosition(pos_.x, pos_.y,500, 500);
	if (FAILED(hr))
	{
		return;
	}
	hr = pMediaPosition->put_CurrentPosition((REFTIME)0.0);
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->put_Visible(OATRUE);
	if (FAILED(hr))
	{
		return;
	}
	hr = pMediaControl->Run();
	if (FAILED(hr))
	{
		return;
	}
}

void Videoclass::WaitMessage()
{
	long evCode;

	LONG_PTR param1 = 0, param2 = 0;

	while (SUCCEEDED(pMediaEvent->GetEvent(&evCode, &param1, &param2, 0)))
	{
		pMediaEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
			return;
		};
	};
}

void Videoclass::Stop()
{
	pMediaPosition->put_CurrentPosition((REFTIME)0.0);
	HRESULT hr;
	hr = pMediaControl->Stop();
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->put_Owner(NULL);
	if (FAILED(hr))
	{
		return;
	}
	hr = pVideoWindow->put_Visible(OAFALSE);
	if (FAILED(hr))
	{
		return;
	}	

}
