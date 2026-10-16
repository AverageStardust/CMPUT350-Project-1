#include "MathUtil.h"

#include <cmath>

namespace CMPUT350 {

Point2D Point2D::operator+(const Point2D &other) const { return Point2D(x + other.x, y + other.y); }
Point2D Point2D::operator+(const float &scalar) const { return Point2D(x + scalar, y + scalar); }
Point2D Point2D::operator-(const Point2D &other) const { return Point2D(x - other.x, y - other.y); }
Point2D Point2D::operator-(const float &scalar) const { return Point2D(x - scalar, y - scalar); }
Point2D Point2D::operator*(const float &scalar) const { return Point2D(x * scalar, y * scalar); }
Point2D Point2D::operator/(const float &scalar) const { return Point2D(x / scalar, y / scalar); }
float Point2D::operator*(const Point2D &other) const { return x * other.x + y * other.y; }
bool Point2D::operator==(const Point2D &other) const { return x == other.x && y == other.y; }
bool Point2D::operator<(const Point2D &other) const { return x < other.x && y < other.y; }
bool Point2D::operator>(const Point2D &other) const { return x > other.x && y > other.y; }
bool Point2D::operator<=(const Point2D &other) const { return x <= other.x && y <= other.y; }
bool Point2D::operator>=(const Point2D &other) const { return x >= other.x && y >= other.y; }

Point2D &Point2D::operator+=(const Point2D &other) {
    x += other.x;
    y += other.y;
    return *this;
}
Point2D &Point2D::operator+=(const float &scalar) {
    x += scalar;
    y += scalar;
    return *this;
}
Point2D &Point2D::operator-=(const Point2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
Point2D &Point2D::operator-=(const float &scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}
Point2D &Point2D::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Point2D &Point2D::operator/=(const float &scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Point2D Point2D::Min(Point2D other) const { return Point2D(fmin(x, other.x), fmin(y, other.y)); }
Point2D Point2D::Max(Point2D other) const { return Point2D(fmax(x, other.x), fmax(y, other.y)); }
float Point2D::Dot(Point2D other) const { return x * other.x + y * other.y; }
float Point2D::Cross(Point2D other) const { return x * other.y - y * other.x; }
float Point2D::Distance(const Point2D &other) const { return hypotf(x - other.x, y - other.y); }
void Point2D::Normalize() { *this /= this->Length(); }
Point2D Point2D::Normalized() const { return *this / this->Length(); }
void Point2D::Rotate(float thetaRadians) {
    float sinTheta = sinf(thetaRadians);
    float cosTheta = cosf(thetaRadians);
    float tempX = x;
    x = x * cosTheta - y * sinTheta;
    y = tempX * sinTheta + y * cosTheta;
}
Point2D Point2D::Rotated(float thetaRadians) const {
    float sinTheta = sinf(thetaRadians);
    float cosTheta = cosf(thetaRadians);
    return Point2D(x * cosTheta - y * sinTheta, x * sinTheta + y * cosTheta);
}
Point2D Point2D::Perpendicular() const { return Point2D(-y, x); }
float Point2D::Length() const { return hypot(x, y); }
float Point2D::LengthSq() const { return x * x + y * y; }
float Point2D::Dot(Point2D a, Point2D b) { return a.x * b.x + a.y * b.y; }
float Point2D::Cross(Point2D a, Point2D b) { return a.x * b.y - a.y * b.x; }

sf::Vector2f Point2D::AsSfmlVector() const { return sf::Vector2f(x, y); }

std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
Point2D operator*(float scalar, const Point2D &point) {
    return Point2D(scalar * point.x, scalar * point.y);
}

float Line::Length() const { return p1.Distance(p2); }
Point2D Line::ClosestPoint(const Point2D &p) const {
    Point2D diff = p2 - p1;
    float t = (p - p1).Dot(diff) / diff.LengthSq();
    t = fmax(t, fmin(t, 1));  // clamp
    return p1 + diff * t;
}
bool Line::IsOnLeftSide(const Point2D &p) const { return (p1 - p).Cross(p2 - p) < 0; }
// bool Line::Intersects(const Line &other, Point2D &point) const {
//     float determinant = (p2 - p1).Cross(other.p2 - other.p1);

//     if (determinant == 0)
//         return false;

//     float t = (other.p1 - p1).Cross(other.p2 - other.p1) / determinant;


//     (p1+(p2-p1) * t).Distance(other.p1) /
//     dist(p1+(p2-p1) * t, P) / |P->|

//     return;
// }

std::ostream &operator<<(std::ostream &os, const Line &l) {
    os << "(" << l.p1 << ", " << l.p2 << ")";
    return os;
}

Rect Rect::operator|(const Point2D &other) const {
    if (Exists()) {
        Rect result;
        result.topLeft = topLeft.Min(other);
        result.bottomRight = bottomRight.Max(other);
        return result;
    } else {
        return Rect(other);
    }
}
Rect Rect::operator|(const Rect &other) const {
    if (!other.Exists()) return *this;

    return *this | other.topLeft | other.bottomRight;
}
Rect Rect::operator|(const Line &other) const { return *this | other.p1 | other.p2; }
Rect Rect::operator&(const Rect &other) const {
    if (Exists() && other.Exists()) {
        Rect result;
        result.topLeft = topLeft.Max(other.topLeft);
        result.bottomRight = bottomRight.Min(other.bottomRight);
        return result;
    } else {
        return {};
    }
}
Rect &Rect::operator|=(const Point2D &other) {
    if (Exists()) {
        topLeft = topLeft.Min(other);
        bottomRight = bottomRight.Max(other);
    } else {
        topLeft = other;
        bottomRight = other;
    }

    return *this;
}
Rect &Rect::operator|=(const Rect &other) {
    if (other.Exists()) {
        *this |= other.topLeft;
        *this |= other.bottomRight;
    }

    return *this;
}
Rect &Rect::operator|=(const Line &other) {
    *this |= other.p1;
    *this |= other.p2;
    return *this;
}
Rect &Rect::operator&=(const Rect &other) {
    if (!Exists()) return *this;
    if (!other.Exists()) {
        return *this = {};
    }

    topLeft = topLeft.Max(other.topLeft);
    bottomRight = bottomRight.Min(other.bottomRight);

    return *this;
}

void Rect::Inset(int inset) {
    topLeft += inset;
    bottomRight -= inset;
}
Rect Rect::Inseted(int inset) const {
    Rect result;
    result.topLeft = topLeft + inset;
    result.bottomRight = topLeft - inset;
    return result;
}
bool Rect::IsInside(const Point2D &p) const {
    return p.x >= topLeft.x && p.x <= bottomRight.x && p.y >= topLeft.y && p.y <= bottomRight.y;
}
float Rect::Width() const {
    if (!Exists()) return 0;
    return bottomRight.x - topLeft.x;
}
float Rect::Height() const {
    if (!Exists()) return 0;
    return bottomRight.y - topLeft.y;
}
Point2D Rect::Size() const {
    if (!Exists()) return {};
    return bottomRight - topLeft;
}
Point2D Rect::Center() const {
    if (!Exists()) return {};
    return (bottomRight + topLeft) / 2.0;
}
bool Rect::Exists() const { return bottomRight >= topLeft; }

bool Rect::Intersects(const Rect &p, Point2D &point) const {
    Rect intersection = *this & p;
    bool intersects = intersection.Exists();

    if (intersects)
        point = intersection.Center();

    return intersects;
}

std::ostream &operator<<(std::ostream &os, const Rect &r) {
    os << "(" << r.topLeft << ", " << r.bottomRight << ")";
    return os;
}

Matrix2::Matrix2(float (&&basis)[4]) { std::copy(basis, basis + 4, this->cells); }

Matrix2 Matrix2::operator*(const float &scalar) const {
    return Matrix2(cells[0] * scalar, cells[1] * scalar, cells[2] * scalar, cells[3] * scalar);
}
Point2D Matrix2::operator*(const Point2D &vector) const {
    return Point2D(cells[0] * vector.x + cells[1] * vector.y,
                   cells[2] * vector.x + cells[3] * vector.y);
}
Matrix2 Matrix2::operator*(const Matrix2 &other) const {
    return Matrix2(cells[0] * other.cells[0] + cells[1] * other.cells[2],
                   cells[0] * other.cells[1] + cells[1] * other.cells[3],
                   cells[2] * other.cells[0] + cells[3] * other.cells[2],
                   cells[2] * other.cells[1] + cells[3] * other.cells[3]);
}

float Matrix2::Determinant() const { return cells[0] * cells[3] - cells[1] * cells[2]; }
Matrix2 Matrix2::Inverse() const {
    float determinant = Determinant();
    assert(determinant != 0);
    return Matrix2(cells[3], -cells[1], -cells[2], cells[0]) * (1 / determinant);
}

std::ostream &operator<<(std::ostream &os, const Matrix2 &m) {
    os << "(" << m.cells << ")";
    return os;
}

Transform2D Transform2D::Rotation(float angle) {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return Transform2D(Matrix2(cosAngle, -sinAngle, sinAngle, cosAngle), {});
}
Transform2D Transform2D::Translation(Point2D offset) { return Transform2D({}, offset); }
Transform2D Transform2D::Scale(float factor) { return Transform2D({factor, 0.0, 0.0, factor}, {}); }

Point2D Transform2D::operator*(const Point2D &vector) const { return basis * vector + origin; }
Line Transform2D::operator*(const Line &line) const {
    return Line(*this * line.p1, *this * line.p2);
}
Circle Transform2D::operator*(const Circle &circle) const {
    // assumes uniform scaling
    float scalingFactor = hypotf(basis.cells[0], basis.cells[2]);
    return Circle(circle.center, circle.radius * scalingFactor);
}
Rect Transform2D::operator*(const Rect &rect) const {
    Point2D p0 = *this * rect.topLeft;
    Point2D p1 = *this * Point2D(rect.topLeft.x, rect.bottomRight.y);
    Point2D p2 = *this * rect.bottomRight;
    Point2D p3 = *this * Point2D(rect.bottomRight.x, rect.topLeft.y);
    return Rect(p0, p1) | p2 | p3;
}
Transform2D Transform2D::operator*(const Transform2D &other) const {
    return Transform2D(basis * other.basis, basis * other.origin + origin);
}
Transform2D Transform2D::Inverse() const { return Transform2D(basis.Inverse(), origin * -1); }

std::ostream &operator<<(std::ostream &os, const Transform2D &t) {
    os << "(" << t.basis << ", " << t.basis << ")";
    return os;
}

}  // namespace CMPUT350
