#include "GraphicsObject.h"

#include "MathUtil.h"

namespace CMPUT350 {

void GraphicsObject::RenderBackground(GameContext *contextrender) { return; }
void GraphicsObject::RenderForeground(GameContext *contextrender) { return; }

Point2D GraphicsObject::GetLocation() const { return {}; }
float GraphicsObject::GetRotation() const { return 0; }

Transform2D GraphicsObject::GetTransform() const {
    return transform;
}
void GraphicsObject::UpdateTransform() {
    // rotate around origin, then translate
    transform = Transform2D::Translation(GetLocation()) * Transform2D::Rotation(GetRotation());
}

}  // namespace CMPUT350
