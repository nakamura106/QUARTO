#ifndef VIDEO_H_
#define VIDEO_H_

#include<Windows.h>
#include<dshow.h>
#include<string>

class Video
{
public:
	Video();
	HRESULT InitCom();
	HRESULT MediaControl();
	HRESULT MediaEvent();
	HRESULT Load(std::string filename_);
	void Play(int time_);

private:
	HRESULT hRes;
	IGraphBuilder *m_Graph;
	IMediaControl* m_Control;
	IMediaEvent* m_Event;
};

#endif // !VIDEO_H_

