#pragma once

#include "ootz/math/vector3.h"

namespace ootz
{

namespace math
{

// coefficients of the plane equation, ax + by + cz + d = 0
struct Plane
{
    // attributes

    float a;
    float b;
    float c;
    float d;

    // constructors

    // constructor of plane
    // coefficients of the plane equation, ax + by + cz + d = 0
    Plane(const float a, const float b, const float c, const float d);

    // constructor of plane
    // a point on the plane and normal vector of the plane
    Plane(const Vector3& point, const Vector3& normal);

    // constructor of plane
    // three points on the plane
    // the normal of this plane is calculated clockwise from p0, p1 and p2
    Plane(const Vector3& p0, const Vector3& p1, const Vector3& p2);

    // default destructor

    ~Plane();

    // public methods

    // calculate signed distance between this plane and the point
    float DistanceFromPointSigned(const Vector3& point) const;

    // calculate unsigned distance between this plane and the point
    float DistanceFromPoint(const Vector3& point) const;

private:

    // private methods

    // D is coefficient of the plane equation, ax + by + cz + d = 0
    float CoefficientD(const Vector3& point, const Vector3& normal);
};

// helper functions

std::ostream& operator<<(std::ostream& ostream, const Plane& plane);

} // namespace math

} // namespace ootz