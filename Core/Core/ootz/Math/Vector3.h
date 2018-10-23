#pragma once

#include "ootz/base.h"

namespace ootz
{

struct Vector3
{
    // attributes

    float x;
    float y;
    float z;

    // constructors and destructors

    // default constructor of the 3-dimentional vector
    // set the attributes to zero
    Vector3();

    // constructor of the 3-dimentional vector
    Vector3(const float x, const float y, const float z);

    // default destructor
    ~Vector3();

    // public methods

    float Dot(const Vector3& other) const;

    // calculate cross production from this to other, this X other
    Vector3 Cross(const Vector3& other) const;

    Vector3 Normalize() const;

    float Length() const;

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

    // hasher for unordered associative containers
    struct Hash
    {
        size_t operator()(const Vector3& key) const;
    };
};

// global operators

Vector3 operator+(const Vector3& v0, const Vector3& v1);
Vector3 operator-(const Vector3& v0, const Vector3& v1);
Vector3 operator/(const Vector3& vector3, const float value);

// helper functions

std::ostream& operator<<(std::ostream& ostream, const Vector3& vector3);

} // namespace ootz