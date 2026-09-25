#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>

namespace CMPUT350 {

struct Point2D {
    float x, y;

    Point2D(float x = 0, float y = 0) : x(x), y(y) {}

    Point2D operator+(const Point2D &other) const { return Point2D(x + other.x, y + other.y); }
    Point2D operator+(const float &scalar) const { return Point2D(x + scalar, y + scalar); }
    Point2D operator-(const Point2D &other) const { return Point2D(x - other.x, y - other.y); }
    Point2D operator-(const float &scalar) const { return Point2D(x - scalar, y - scalar); }
    Point2D operator*(const float &scalar) const { return Point2D(x * scalar, y * scalar); }
    Point2D operator/(const float &scalar) const { return Point2D(x / scalar, y / scalar); }
    float operator*(const Point2D &other) const { return x * other.x + y * other.y; }
    bool operator==(const Point2D &other) const { return x == other.x && y == other.y; }
    bool operator<(const Point2D &other) const { return x < other.x && y < other.y; }
    bool operator>(const Point2D &other) const { return x > other.x && y > other.y; }

    Point2D &operator+=(const Point2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point2D &operator+=(const float &scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    Point2D &operator-=(const Point2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Point2D &operator-=(const float &scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }
    Point2D &operator*=(const float &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Point2D &operator/=(const float &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Point2D Min(Point2D other) const { return Point2D(fmin(x, other.x), fmin(y, other.y)); }
    Point2D Max(Point2D other) const { return Point2D(fmax(x, other.x), fmax(y, other.y)); }
    float Dot(Point2D other) const { return x * other.x + y * other.y; }
    float Cross(Point2D other) const { return x * other.y - y * other.x; }
    float Distance(const Point2D &other) const { return hypotf(x - other.x, y - other.y); }
    void Normalize() { *this /= this->Length(); }
    Point2D Normalized() const { return *this / this->Length(); }
    float Length() const { return hypot(x, y); }
    float LengthSq() const { return x * x + y * y; }
    static float Dot(Point2D a, Point2D b) { return a.x * b.x + a.y * b.y; }
    static float Cross(Point2D a, Point2D b) { return a.x * b.y - a.y * b.x; }
};

static std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

static Point2D operator*(float scalar, const Point2D &point) {
    return Point2D(scalar * point.x, scalar * point.y);
}

struct Line {
    Point2D p1, p2;

    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}

    float Length() const { return p1.Distance(p2); }
    Point2D ClosestPoint(const Point2D &p) const {
        Point2D diff = p2 - p1;
        float t = (p - p1).Dot(diff) / diff.LengthSq();
        t = fmax(t, fmin(t, 1));  // clamp
        return p1 + diff * t;
    }
    bool IsOnLeftSide(const Point2D &p) const { return (p1 - p).Cross(p2 - p) < 0; }
    bool Crosses(Line other, Point2D &crossingPoint) const {
        bool crossesForThis = IsOnLeftSide(other.p1) != IsOnLeftSide(other.p2);
        bool crossesForOther = other.IsOnLeftSide(p1) != other.IsOnLeftSide(p2);
        return crossesForThis && crossesForOther;
    }
};

static std::ostream &operator<<(std::ostream &os, const Line &l) {
    os << "(" << l.p1 << ", " << l.p2 << ")";
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    Point2D bottomRight;

    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(top, left)), bottomRight(Point2D(top + width, left + height)) {}
    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0)
        : topLeft(tl), bottomRight(tl + Point2D(w, h)) {}
    // Creates bounding box around p1 and p2 with positive width/height
    Rect(Point2D p1, Point2D p2) : topLeft(p1.Min(p2)), bottomRight(p1.Max(p2)) {}
    Rect(Point2D center, float radius)
        : topLeft(center.x - radius),
          bottomRight(center.x + radius) {}
    Rect(Circle circle)
        : topLeft(circle.center - circle.radius),
          bottomRight(circle.center + circle.radius) {}

    Rect operator|(const Point2D &other) const {
        Rect result;
        result.topLeft = topLeft.Min(other);
        result.bottomRight = bottomRight.Max(other);
        return result;
    }
    Rect operator|(const Rect &other) const {
        if (!other.IsEmpty()) {
            return *this | other.topLeft | other.bottomRight;
        } else {
            return *this;
        }
    }
    Rect operator|(const Line &other) const { return *this | other.p1 | other.p2; }
    Rect operator&(const Rect &other) const {
        if (!other.IsEmpty()) {
            Rect result;
            result.topLeft = topLeft.Max(other.topLeft);
            result.bottomRight =
                bottomRight.Min(other.bottomRight);  // stop points from crossing over
            return result;
        } else {
            return *this;
        }
    }
    Rect operator+(const Point2D &other) const { return *this + other; }

    Rect &operator|=(const Point2D &other) {
        topLeft = topLeft.Min(other);
        bottomRight = bottomRight.Max(other);
        return *this;
    }
    Rect &operator|=(const Rect &other) {
        if (!other.IsEmpty()) {
            *this |= other.topLeft;
            *this |= other.bottomRight;
        }
        return *this;
    }
    Rect &operator|=(const Line &other) {
        *this |= other.p1;
        *this |= other.p2;
        return *this;
    }
    Rect &operator&=(const Rect &other) {
        if (!other.IsEmpty()) {
            topLeft = topLeft.Max(other.topLeft);
            bottomRight = bottomRight.Min(other.bottomRight);
        }
        return *this;
    }
    Rect &operator+=(const Point2D &other) {
        *this |= other;
        return *this;
    }

    void Inset(int inset) {
        topLeft += inset;
        bottomRight -= inset;
    }
    Rect Inseted(int inset) const {
        Rect result;
        result.topLeft = topLeft + inset;
        result.bottomRight = topLeft - inset;
        return result;
    }
    bool IsInside(const Point2D &p) const {
        return p.x >= topLeft.x && p.x <= bottomRight.x && p.y >= topLeft.y && p.y <= bottomRight.y;
    }
    bool IsEmpty() const { return !(topLeft < bottomRight); }
};

static std::ostream &operator<<(std::ostream &os, const Rect &r) {
    os << "(" << r.topLeft << ", " << r.bottomRight << ")";
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
