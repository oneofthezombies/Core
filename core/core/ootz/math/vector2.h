#pragma once

namespace ootz
{

namespace math
{

// Vector2 contains two float value
struct Vector2
{
    // attributes

    float x;
    float y;

    // constructors and destructors

    Vector2();
    Vector2(const float x, const float y);
    ~Vector2();

    // operators

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const float other);
    Vector2& operator/=(const float other);

    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator*(const Vector2& lhs, const float rhs);
    friend Vector2 operator*(const float lhs, const Vector2& rhs);
    friend Vector2 operator/(const Vector2& lhs, const float rhs);
    friend Vector2 operator/(const float lhs, const Vector2& rhs);

    // hasher for unordered associative containers
    struct Hash
    {
        size_t operator()(const Vector2& key) const;
    };
};

// global operators

bool operator==(const Vector2& lhs, const Vector2& rhs);
bool operator!=(const Vector2& lhs, const Vector2& rhs);

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, const float rhs);
Vector2 operator*(const float lhs, const Vector2& rhs);
Vector2 operator/(const Vector2& lhs, const float rhs);
Vector2 operator/(const float lhs, const Vector2& rhs);

// helper functions

std::ostream& operator<<(std::ostream& ostream, const Vector2& value);
bool IsEqual(const Vector2& lhs, const Vector2& rhs, const float epsilon = std::numeric_limits<float>::epsilon());

} // namespace math

} // namespace ootz