#pragma once

#include "ootz/base.h"

namespace ootz
{

namespace diamond
{

class CommuteTimeTable
{
public:
    static const size_t kNumEmployee = 4;

    size_t GetNumCurrentEmployees(const size_t currentTime);

private:
    uint32_t enter[kNumEmployee];
    uint32_t exit[kNumEmployee];
};

class StringManipulation
{
public:
    static void Reverse(char* pString);
    static void RemoveDuplicate(char* pString);
};

class BitwiseManipulation
{
public:
    static bool IsOnNthBit(const int data, const int n);
};

} // namespace diamond

} // namespace ootz