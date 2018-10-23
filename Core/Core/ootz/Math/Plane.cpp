#include "stdafx.h"
#include "plane.h"

namespace ootz
{

Plane::Plane(const float a, const float b, const float c, const float d)
    : a(a)
    , b(b)
    , c(c)
    , d(d)
{
}

Plane::Plane(const Vector3& point, const Vector3& normal)
    : a(normal.x)
    , b(normal.y)
    , c(normal.z)
    , d(CoefficientD(point, normal))
{
}

Plane::Plane(const Vector3& p0, const Vector3& p1, const Vector3& p2)
{
    const Vector3 normal(Vector3::Cross(p1 - p0, p2 - p0));

    a = normal.x;
    b = normal.y;
    c = normal.z;
    d = CoefficientD(p0, normal);
}

Plane::~Plane()
{
}

float Plane::DistanceFromPointSigned(const Vector3& point) const
{
    return (a * point.x + b * point.y + c * point.z + d) / Vector3(a, b, c).Length();
}

float Plane::DistanceFromPoint(const Vector3& point) const
{
    return std::abs(DistanceFromPointSigned(point));
}

float Plane::CoefficientD(const Vector3& point, const Vector3& normal)
{
    return -(normal.x * point.x + normal.y * point.y + normal.z * point.z);
}

std::ostream& operator<<(std::ostream& ostream, const Plane& plane)
{
    ostream << plane.a << ' ' << plane.b << ' ' << plane.c << ' ' << plane.d;
    return ostream;
}

} // namespace ootz