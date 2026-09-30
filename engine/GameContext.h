#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <vector>

#include "DrawContext.h"
#include "EngineView.h"
#include "GameObject.h"

namespace CMPUT350 {

class GameContext {
public:
    GameContext(EngineView *mEngineView, DrawContext *ScreenContext)
        : mEngineView(mEngineView), ScreenContext(ScreenContext) {};

    EngineView *mEngineView;
    DrawContext *ScreenContext;

    std::vector<bool> inputs = {
        false, false,
        false};  // Should contain 3 booleans representing {leftPressed, rightPressed, wantToShoot}
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
