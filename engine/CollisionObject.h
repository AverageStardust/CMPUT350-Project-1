#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <memory>
#include <vector>

#include "GraphicsObject.h"
#include "GameEngine.h"
#include "MathUtil.h"

namespace CMPUT350 {

enum class ShapeType { kLine, kCircle, kRect };
union ShapeUnion {
    ShapeUnion(Line l) : line(l) {}
    ShapeUnion(Circle c) : circle(c) {}
    ShapeUnion(Rect r) : rect(r) {}
    Line line;
    Circle circle;
    Rect rect;  // Axis-aligned rectangle
};
struct Shape {
    Shape(const Line &l) : shape(l), t(ShapeType::kLine) {}
    Shape(const Circle &c) : shape(c), t(ShapeType::kCircle) {}
    Shape(const Rect &r) : shape(r), t(ShapeType::kRect) {}
    ShapeUnion shape;
    ShapeType t;
};

class CollisionObject : public GraphicsObject {
private:
    // global bounds
    Rect bounds;
    friend class GameEngine;

public:
    virtual void CollisionEnter(const std::shared_ptr<CollisionObject> &obj) = 0;
    virtual void CollisionEnter(const std::shared_ptr<CollisionObject> &obj, const Point2D &collisionPoint)
	{ CollisionEnter(obj); }

	// calls GetShapes and generates a bounding box for itself
    void UpdateBounds();
    bool CheckCollision(CollisionObject &other);

    // Return the internal shapes in the object. Shapes can be:
    // lines, points/circles, or axis-aligned rectangles
    virtual const std::vector<Shape> &GetShapes() = 0;
};

}  // namespace CMPUT350

#endif
