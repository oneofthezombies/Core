#pragma once

#include <ostream>

namespace ootz
{

namespace Math
{

struct Vector3
{
    // attributes

    float x;
    float y;
    float z;

    // constructors

    // default constructor of the 3-dimentional vector
    // set the attributes to zero
    Vector3();

    // constructor of the 3-dimentional vector
    Vector3(const float x, const float y, const float z);

    // public methods

    float Dot(const Vector3& other);

    // calculate cross production from this to other, this X other
    Vector3 Cross(const Vector3& other);

    Vector3 Normalize();

    // operators

    friend Vector3 operator+(const Vector3& v0, const Vector3& v1);
    friend Vector3 operator-(const Vector3& v0, const Vector3& v1);
    friend Vector3 operator/(const Vector3& vector3, const float value);

    // static methods

    static float Dot(const Vector3& v0, const Vector3& v1);

    // calculate cross production from v0 to v1, v0 X v1
    static Vector3 Cross(const Vector3& v0, const Vector3& v1);


    static Vector3 Normalize(const Vector3& vector3);


    static float Length(const Vector3& vector3);

    static float LengthSq(const Vector3& vector3);
};

// global operators

Vector3 operator+(const Vector3& v0, const Vector3& v1);
Vector3 operator-(const Vector3& v0, const Vector3& v1);
Vector3 operator/(const Vector3& vector3, const float value);

// helper functions

std::ostream& operator<<(std::ostream& ostream, const Vector3& vector3);

} // namespace Math

} // namespace ootz