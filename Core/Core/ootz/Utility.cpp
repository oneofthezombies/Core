#include "stdafx.h"
#include "Utility.hpp"

namespace ootz
{

bool IsOutOfRange(const std::size_t size, const int32_t index)
{
    return index < 0 
        || static_cast<std::size_t>(index) >= size;
}

} // namespace ootz