#pragma once

/* std::size_t */
#include <cstddef>

/* std::numeric_limits */
#include <limits>

/* std::ostream */
#include <ostream>

namespace ootz
{

/*  Vector2 contains two float value
*/
struct Vector2
{
    /* properties */

    float x;
    float y;

    /* constructors and destructors */

     Vector2();
     Vector2(const float x, const float y);
    ~Vector2();

    /* operators */

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

    /* hasher for unordered associative containers */
    struct Hash
    {
        std::size_t operator()(const Vector2& key) const;
    };
};

/* operators */

bool operator==(const Vector2& lhs, const Vector2& rhs);
bool operator!=(const Vector2& lhs, const Vector2& rhs);

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, const float rhs);
Vector2 operator*(const float lhs, const Vector2& rhs);
Vector2 operator/(const Vector2& lhs, const float rhs);
Vector2 operator/(const float lhs, const Vector2& rhs);

/* utilities */

std::ostream& operator<<(std::ostream& ostream, const Vector2& value);
bool IsEqual(const Vector2& lhs, const Vector2& rhs, const float epsilon = std::numeric_limits<float>::epsilon());

} // namespace ootz