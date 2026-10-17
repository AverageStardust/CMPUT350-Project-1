#include "Bezier.h"

#include <algorithm>
#include <vector>
#include <iostream>

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

Path::Path(const std::vector<Point2D> &pts) : pointList(pts) {
    num_segments = (pts.size() - 1) / 3;
    MakePath(pointList);
}

Path::Path(const std::vector<Point2D> &pts, Point2D loc) : pointList(pts) {
    pointList[pointList.size() - 1] = loc;
    num_segments = (pts.size() - 1) / 3;
    MakePath(pointList);
}

void Path::MakePath(const std::vector<Point2D> &pts) {
    assert((pts.size() % 3) == 1);

    for (int i = 0; i < num_segments; ++i) {
        bezierList.push_back(
            Bezier({pts[3 * i], pts[3 * i + 1], pts[3 * i + 2], pts[3 * i + 3]}));
    }
}

Point2D Path::GetLocation(float curLocation) {
    float scaledLocation = curLocation * num_segments;
    int curve = static_cast<int>(scaledLocation);
    if (curve < num_segments) {
        return bezierList[curve].GetPoint(scaledLocation - curve);
    } else {
        return bezierList[bezierList.size() - 1].GetPoint(1.0f);
    }
}

Point2D Path::GetSlope(float curLocation) {
    float scaledLocation = curLocation * num_segments;
    int curve = static_cast<int>(scaledLocation);
    if (curve < num_segments) {
        return bezierList[curve].GetSlope(scaledLocation - curve);
    } else {
        return bezierList[bezierList.size() - 1].GetSlope(1.0f);
    }
}

float Path::Increment(float stepAmount, float curLocation) {
    // Returns the incremented location on the curve
    int curve = curLocation * num_segments;
    if (curve >= num_segments) {
        return 1.0f;
    }
    float locationOnCurve = (curLocation * num_segments) - curve;
    return stepAmount / bezierList[curve].GetSlope(locationOnCurve).Length() + curLocation;
}

}  // namespace CMPUT350
