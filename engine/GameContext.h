#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H


#include "DrawContext.h"
#include "EngineView.h"
#include "NotificationManager.h"

namespace CMPUT350 {

class GameContext {
public:
    GameContext(EngineView *mEngineView, DrawContext *ScreenContext, DrawContext *GUIContext, std::shared_ptr<NotificationManager> mNotificationManager)
        : mEngineView(mEngineView), ScreenContext(ScreenContext), GUIContext(GUIContext), mNotificationManager(mNotificationManager) {};

    EngineView *mEngineView;
	DrawContext *ScreenContext;
	DrawContext *GUIContext;
	std::weak_ptr<GameObject> CurrObject;
	std::shared_ptr<NotificationManager> mNotificationManager;
	int currentFrame;
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
