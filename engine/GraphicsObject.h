#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "GameObject.h"

namespace CMPUT350 {

class GameContext;

class GraphicsObject : public GameObject {
public:
    GraphicsObject(bool background) : isBackground(background) {
        if (background != true) {
            isBackground = false;
        }
    };

    virtual void RenderBackground(GameContext *context);
    virtual void RenderForeground(GameContext *context);

    bool isBackground;
};

}  // namespace CMPUT350

#endif
