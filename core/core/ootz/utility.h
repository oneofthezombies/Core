#pragma once

#include "ootz/base.h"

namespace ootz
{

constexpr bool IsOutOfRange(const size_t size, const size_t index)
{
    return index >= size;
}

template<typename T>
constexpr bool IsOutOfRange(const std::vector<T>& vector, const size_t index)
{
    return IsOutOfRange(vector.size(), index);
}

template<typename T>
constexpr bool IsValidIndex(const std::vector<T>& vector, const size_t index)
{
    return false == IsOutOfRange(vector.size(), index);
}

} // namespace ootz