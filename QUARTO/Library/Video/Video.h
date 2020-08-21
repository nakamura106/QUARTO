#ifndef VIDEO_H_
#define VIDEO_H_

#include<Windows.h>
#include<dshow.h>
#include<string>
#include<d3d9.h>
#include<d3dx9.h>
#include<vmr9.h>


//class Video
//{
//public:
//	Video();
//	HRESULT InitCom();
//	HRESULT InitVmr();
//	void WindowSpecification();
//	void SizeSpecification();
//	void FilterConnection();
//	HRESULT MediaControl();
//	HRESULT MediaEvent();
//	HRESULT Load(LPCWCHAR filename_);
//	void Play(int time_);
//
//private:
//	HRESULT h_res_;
//	IGraphBuilder* graph_;
//	ICaptureGraphBuilder2* graph2_ = NULL;
//	IMediaControl* control_;
//	IMediaEvent* event_;
//
//	IBaseFilter* pVMR9 = NULL;
//	IBaseFilter* pSource = NULL;
//
//	IVMRFilterConfig* pVMRCfg = NULL;
//	IVMRWindowlessControl* pVMRWndCont = NULL;
//
//	LONG W, H;
//	RECT SrcR, DestR;
//};

class Videoclass
{
public:
	Videoclass() ;
	~Videoclass();

	void InitInterface();

	void LoadFile(LPCWCHAR filename_);

	void SetMessage();

	void SetWind();

	void Play(D3DXVECTOR2 pos_);

	void WaitMessage();

	void Stop();

private:
	// �`��E�B���h�E�̐ݒ�
	HWND     hNotifyWnd;        // DirectShow���C�u��������̃��b�Z�[�W���M��E�B���h�E
	UINT     nGraphNotifyMsg;   // �ʒm���b�Z�[�W
	LPCTSTR  lpszFilename;      // �Đ��f���̃t�@�C����

	// �`��pDirectShow�C���^�[�t�F�C�X
	IGraphBuilder* pGraphBuilder;
	IMediaControl* pMediaControl;
	IMediaEventEx* pMediaEvent;
	IVideoWindow* pVideoWindow;
	IMediaPosition* pMediaPosition;
};

#endif // !VIDEO_H_

