#ifndef LIBRARYMANAGER_H_
#define LIBRARYMANAGER_H_

#include<d3dx9.h>

class AudioPlayer;
class Engine;
class Graphics;
class Camera;
class Input;
class Videoclass;

class LibraryManager
{
public:
	static LibraryManager* Instance();
	

	void Init();

	Engine* GetEngine() { return engine_ptr_; };
	Graphics* GetGraphics() { return graphics_ptr_; };
	Input* GetInput() { return input_ptr_; }
	Camera* GetCamera() { return camera_ptr_; };
	Videoclass* GetVideo() { return video_ptr_; }

private:
	LibraryManager();
	LibraryManager(LibraryManager& librarymanager) = delete;
private:
	static LibraryManager* instance_;

	Engine* engine_ptr_;
	Graphics* graphics_ptr_;
	Input* input_ptr_;
	Camera* camera_ptr_;
	Videoclass* video_ptr_;

	D3DXVECTOR3 pos=D3DXVECTOR3(0.0f,0.0f,10.0f);
};

#endif