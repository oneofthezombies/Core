#include "stdafx.h"
#include "Vector3.h"

#include <cassert>

namespace ootz
{

namespace Math
{

Vector3::Vector3()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
{
}

Vector3::Vector3(const float x, const float y, const float z)
    : x(x)
    , y(y)
    , z(z)
{
}

float Vector3::Dot(const Vector3& other) const
{
    return Vector3::Dot(*this, other);
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    return Vector3::Cross(*this, other);
}

Vector3 Vector3::Normalize() const
{
    return Vector3::Normalize(*this);
}

float Vector3::Length() const
{
    return Vector3::Length(*this);
}

float Vector3::Dot(const Vector3& v0, const Vector3& v1)
{
    return v0.x * v1.x 
         + v0.y * v1.y 
         + v0.z * v1.z;
}

Vector3 Vector3::Cross(const Vector3& v0, const Vector3& v1)
{
    return Vector3(  v0.y * v1.z - v0.z * v1.y, 
                   -(v0.x * v1.z - v0.z * v1.x), 
                     v0.x * v1.y - v0.y * v1.x);
}

Vector3 Vector3::Normalize(const Vector3& vector3)
{
    return vector3 / Length(vector3);
}

float Vector3::Length(const Vector3& vector3)
{
    return std::sqrt(LengthSq(vector3));
}

float Vector3::LengthSq(const Vector3& vector3)
{
    return vector3.x * vector3.x
         + vector3.y * vector3.y
         + vector3.z + vector3.z;
}

Vector3 operator+(const Vector3& v0, const Vector3& v1)
{
    return Vector3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

Vector3 operator-(const Vector3& v0, const Vector3& v1)
{
    return Vector3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

Vector3 operator/(const Vector3& vector3, const float value)
{
    assert(value && "divided by zero.");

    return Vector3(vector3.x / value, 
                   vector3.y / value, 
                   vector3.z / value);
}

std::ostream& operator<<(std::ostream& ostream, const Vector3& vector3)
{
    ostream << vector3.x << ' ' << vector3.y << ' ' << vector3.z;
    return ostream;
}

} // namespace Math

} // namespace ootz

