#ifndef BEZIER_H
#define BEZIER_H

#include "MathUtil.h"
#include <vector>

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

        void MakePath(const std::vector<Point2D> &pts) {
            assert((pts.size() % 3) == 1);
            for (int i = 0; i < num_segments; ++i) {
                bezierList.push_back(Bezier( {pts[3*i], pts[3*i + 1], pts[3*i + 2], pts[3*i + 3]} ));
            }
        }

        Point2D GetLocation(float curLocation) {
            float scaledLocation = curLocation * num_segments;
            int curve = static_cast<int>(scaledLocation);
            if (curve < num_segments) {
                return bezierList[curve].GetPoint(scaledLocation - curve);
            }
            else {
                return bezierList[bezierList.size() - 1].GetPoint(1.0f);
            }
        }

        float Increment(float stepAmount, float curLocation) {
            // Returns the incremented location on the curve
            int curve = curLocation * num_segments;
            if (curve >= num_segments) {
                return 1.0f;
            }
            float locationOnCurve = (curLocation * num_segments) - curve;
            return stepAmount / bezierList[curve].GetSlope(locationOnCurve).Length() + curLocation;
        }
        
};

}  // namespace CMPUT350

#endif  // BEZIER_H
