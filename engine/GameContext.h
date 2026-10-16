#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "DrawContext.h"
#include "EngineView.h"
#include "MathUtil.h"
#include "NotificationManager.h"

namespace CMPUT350 {

class GameContext {
public:
    GameContext(EngineView *mEngineView, DrawContext *ScreenContext, DrawContext *GUIContext,
                NotificationManager *mNotificationManager)
        : mEngineView(mEngineView),
          ScreenContext(ScreenContext),
          GUIContext(GUIContext),
          mNotificationManager(mNotificationManager) {};

    EngineView *mEngineView;
    DrawContext *ScreenContext;
    DrawContext *GUIContext;
    std::weak_ptr<GameObject> CurrObject;
    NotificationManager *mNotificationManager;
    int currentFrame;
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
