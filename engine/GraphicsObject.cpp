#include "GraphicsObject.h"
#include "MathUtil.h"

namespace CMPUT350 {

void GraphicsObject::RenderBackground(GameContext *contextrender) { return; }
void GraphicsObject::RenderForeground(GameContext *contextrender) { return; }

Transform2D GraphicsObject::GetTransform() const {
    // rotate around origin, then translate
    return Transform2D::Translation(GetLocation()) * Transform2D::Rotation(GetRotation());
}

}  // namespace CMPUT350
