#include "CollisionObject.h"

#include "MathUtil.h"

namespace CMPUT350 {
void CollisionObject::UpdateCollider() {
    const Transform2D transform = GetTransform();

    shapes = GetShapes();
    bounds = {};  // empty

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

// feels like this could be done with meta programming but I can't be damned
bool Intersects(const Shape &shapeA, const Transform2D &transformA, const Shape &shapeB,
                const Transform2D &transformB, Point2D point) {
    switch (shapeA.t) {
        case ShapeType::kLine: {
            Line transformedA = transformA * shapeA.shape.line;
            switch (shapeB.t) {
                case ShapeType::kLine:
                    return transformedA.Intersects(transformB * shapeB.shape.line, point);
                case ShapeType::kCircle:
                    return transformedA.Intersects(transformB * shapeB.shape.circle, point);
                case ShapeType::kRect:
                    return transformedA.Intersects(transformB * shapeB.shape.rect, point);
            }
        }

        case ShapeType::kCircle: {
            Circle transformedA = transformA * shapeA.shape.circle;
            switch (shapeB.t) {
                case ShapeType::kLine:
                    return transformedA.Intersects(transformB * shapeB.shape.line, point);
                case ShapeType::kCircle:
                    return transformedA.Intersects(transformB * shapeB.shape.circle, point);
                case ShapeType::kRect:
                    return transformedA.Intersects(transformB * shapeB.shape.rect, point);
            }
        }

        case ShapeType::kRect: {
            Quad transformedA = transformA * shapeA.shape.rect;
            switch (shapeB.t) {
                case ShapeType::kLine:
                    return transformedA.Intersects(transformB * shapeB.shape.line, point);
                case ShapeType::kCircle:
                    return transformedA.Intersects(transformB * shapeB.shape.circle, point);
                case ShapeType::kRect:
                    return transformedA.Intersects(transformB * shapeB.shape.rect, point);
            }
        }
    }
}

Collision CollisionObject::CheckCollision(CollisionObject &other) {
    // short circuit if bounds don't overlap
    if (!bounds.IsOverlapping(other.bounds)) return {};

    const Transform2D transformA = GetTransform();
    const Transform2D transformB = other.GetTransform();

    Point2D point;
    for (Shape shapeA : shapes) {
        for (Shape shapeB : other.shapes) {
            if (Intersects(shapeA, transformA, shapeB, transformB, point)) {
                return {point};
            }
        }
    }

    return {};
}
}  // namespace CMPUT350
