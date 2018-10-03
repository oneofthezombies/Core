#include "stdafx.h"
#include "Vector2.hpp"

/* assert() */
#include <cassert>

/* boost::hash_combine() */
#include <boost/functional/hash.hpp>

namespace ootz
{

Vector2::Vector2()
    : x(0.0f)
    , y(0.0f)
{
}

Vector2::Vector2(const float x, const float y)
    : x(x)
    , y(y)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2& Vector2::operator*=(const float other)
{
    x *= other;
    y *= other;

    return *this;
}

Vector2& Vector2::operator/=(const float other)
{
    assert(other != 0.0f && "divided by zero.");

    x /= other;
    y /= other;

    return *this;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x == rhs.x
        && lhs.y == rhs.y;
}

bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
    return ! (lhs == rhs);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x + rhs.x,
                   lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(lhs.x - rhs.x,
                   lhs.y - rhs.y);
}

Vector2 operator*(const Vector2& lhs, const float rhs)
{
    return Vector2(lhs.x * rhs,
                   lhs.y * rhs);
}

Vector2 operator*(const float lhs, const Vector2& rhs)
{
    return rhs * lhs;
}

Vector2 operator/(const Vector2& lhs, const float rhs)
{
    assert(rhs != 0.0f && "divided by zero.");

    return Vector2(lhs.x / rhs,
                   lhs.y / rhs);
}

Vector2 operator/(const float lhs, const Vector2& rhs)
{
    return rhs / lhs;
}

std::ostream& operator<<(std::ostream& ostream, const Vector2& value)
{
    ostream << "X: " << value.x << ", Y: " << value.y;
    return ostream;
}

bool IsEqual(const Vector2& lhs, const Vector2& rhs, const float epsilon)
{
    return std::abs(lhs.x - rhs.x) < epsilon
        && std::abs(lhs.y - rhs.y) < epsilon;
}

std::size_t Vector2::Hash::operator()(const Vector2 & key) const
{
    std::size_t seed = 0;
    boost::hash_combine(seed, key.x);
    boost::hash_combine(seed, key.y);

    return seed;
}

} // namespace ootz