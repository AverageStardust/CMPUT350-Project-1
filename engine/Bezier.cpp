#include "Bezier.h"

#include <algorithm>

namespace CMPUT350 {
Bezier::Bezier(const Point2D (&&points)[4]) { std::copy(points, points + 4, this->points); }

Point2D Bezier::GetPoint(float t) const {
    return Bezier::GetPoint(points, t);
}

Point2D Bezier::GetSlope(float t) const {
    return Bezier::GetSlope(points, t);
}

Point2D Bezier::GetPoint(const Point2D (&points)[4], float t) {
    return (1 - t) * (1 - t) * (1 - t) * points[0] + 3 * t * (1 - t) * (1 - t) * points[1] +
           3 * t * t * (1 - t) * points[2] + t * t * t * points[3];
}

Point2D Bezier::GetSlope(const Point2D (&points)[4], float t) {
    return 3 * (1 - t) * (1 - t) * (points[1] - points[0]) +
           6 * t * (1 - t) * (points[2] - points[1]) + 3 * t * t * (points[3] - points[2]);
}

}  // namespace CMPUT350
