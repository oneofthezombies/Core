#pragma once

#include <cstddef>
#include <vector>

namespace ootz
{

template<typename T>
bool IsOutOfRange(const std::vector<T>& vector, const std::size_t index)
{
    return index >= vector.size();
}

bool IsOutOfRange(const std::size_t size, const int32_t index);

} // namespace ootz