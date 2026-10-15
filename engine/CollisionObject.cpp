#include "CollisionObject.h"
#include "MathUtil.h"

namespace CMPUT350 {
void CollisionObject::UpdateBounds() {
    const std::vector<Shape> shapes = GetShapes();
    const Transform2D transform = GetTransform();

    bounds = {};  // empty rect
    for (Shape shape : shapes) {
        switch (shape.t) {
            case ShapeType::kLine:
                bounds |= transform * shape.shape.line;
                break;
            case ShapeType::kCircle:
                bounds |= transform * shape.shape.circle;
                break;
            case ShapeType::kRect:
                bounds |= transform * shape.shape.rect;
                break;
        }
    }
}
}  // namespace CMPUT350
