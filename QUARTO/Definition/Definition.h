#ifndef Difinition_H_
#define Difinition_H_

#include"../Manager/LibraryManager.h"

#define THE_INPUT LibraryManager::Instance()->GetInput()
#define THE_GRAPHICS LibraryManager::Instance()->GetGraphics()
#define THE_SOUND LibraryManager::Instance()->GetAudio()
#define THE_ENGINE LibraryManager::Instance()->GetEngine()
#define THE_CAMERA LibraryManager::Instance()->GetCamera()
#define THE_VIDEO LibraryManager::Instance()->GetVideo()
#endif // !Difinition_H_
