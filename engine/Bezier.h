#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

#include "MathUtil.h"

namespace CMPUT350 {
class Bezier {
private:
    Point2D points[4];

public:
    Bezier(const Point2D (&&points)[4]);

    Point2D GetPoint(float t) const;
    Point2D GetSlope(float t) const;

    static Point2D GetPoint(const Point2D (&points)[4], float t);
    static Point2D GetSlope(const Point2D (&points)[4], float t);
};

class Path {
private:
    std::vector<Point2D> pointList;
    std::vector<Bezier> bezierList;
    int num_segments;

public:
    Path(const std::vector<Point2D> &pts);

    Path(const std::vector<Point2D> &pts, Point2D loc);

    void MakePath(const std::vector<Point2D> &pts);
    Point2D GetLocation(float curLocation);
    Point2D GetSlope(float curLocation);
    float Increment(float stepAmount, float curLocation);
};

}  // namespace CMPUT350

#endif  // BEZIER_H
