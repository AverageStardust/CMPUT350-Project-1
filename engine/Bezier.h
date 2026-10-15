#include "MathUtil.h"

namespace CMPUT350 {
class Bezier {
private:
    Point2D points[4];

public:
    Bezier(const Point2D (&points)[4]);

    Point2D GetPoint(float t) const;
    Point2D GetSlope(float t) const;

    static Point2D GetPoint(const Point2D (&points)[4], float t);
    static Point2D GetSlope(const Point2D (&points)[4], float t);
};
}  // namespace CMPUT350
