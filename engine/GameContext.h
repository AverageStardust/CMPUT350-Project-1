#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "DrawContext.h"
#include "EngineView.h"
#include "GameObject.h"

#include <vector>

namespace CMPUT350 {

class GameContext {
public:
    EngineView *mEngineView;
    DrawContext *ScreenContext;

    std::vector<bool> inputs; // Should contain 3 booleans representing {leftPressed, rightPressed, wantToShoot}
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
