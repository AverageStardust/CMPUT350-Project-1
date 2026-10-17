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
        Path(std::vector<Point2D> &pts);

        void MakePath(std::vector<Point2D> &pts) {
            for (int i = 0; i < (num_segments / 3); ++i) {
                bezierList.push_back(Bezier( {pts[3*i], pts[3*i + 1], pts[3*i + 2], pts[3*i + 3]} ));
            }
        }

        Point2D GetPosition(float stepAmount, float curLocation) {
            int curve = curLocation * num_segments;
            if (curve >= num_segments) {
                return bezierList[bezierList.size() - 1].GetPoint(1.0f);
            }
            float locationOnCurve = (curLocation * num_segments) - curve;
            float newLocation = stepAmount / bezierList[curve].GetSlope(locationOnCurve).Length();
            return bezierList[curve].GetPoint(newLocation);
        }
        
};

}  // namespace CMPUT350

#endif  // BEZIER_H
