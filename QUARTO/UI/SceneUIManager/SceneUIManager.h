#ifndef SCENE_UI_MANAGER_H_
#define SCENE_UI_MANAGER_H_

class SceneUIManager
{
public:
	SceneUIManager() {}
	virtual ~SceneUIManager() {}

public:
	virtual bool CreateUI() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void AllDelete() = 0;

};

#endif