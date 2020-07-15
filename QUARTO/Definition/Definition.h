#ifndef Difinition_H_
#define Difinition_H_

#include"../Manager/LibraryManager.h"

#define THE_INPUT LibraryManager::Instance()->input()
#define THE_GRAPHICS LibraryManager::Instance()->graphics()
#define THE_SOUND LibraryManager::Instance()->sound()
#define THE_ENGINE LibraryManager::Instance()->engine()
#define THE_CAMERA LibraryManager::Instance()->camera()
#define THE_VIDEO LibraryManager::Instance()->video()
#endif // !Difinition_H_
