#include "stdafx.h"
#include "example.h"

namespace ootz
{

namespace diamond
{

size_t CommuteTimeTable::GetNumCurrentEmployees(const size_t currentTime)
{
    size_t numCurrentEmployees = 0;
    for (size_t i = 0; i < kNumEmployee; ++i)
    {
        if (enter[i] <= currentTime && 
            exit[i] > currentTime)
        {
            numCurrentEmployees++;
        }
    }

    return numCurrentEmployees;
}

void StringManipulation::Reverse(char* pString)
{
    if (nullptr == pString) 
        return;

    const size_t size = std::strlen(pString);
    const size_t halfSize = size / 2;
    
    for (size_t i = 0; i < halfSize; ++i)
    {
        std::swap(pString[i], pString[size - 1 - i]);
    }
}

void StringManipulation::RemoveDuplicate(char* pString)
{
    if (nullptr == pString)
        return;

    char* pLast = pString;
    char* pTraverse = pString;

    while (*pTraverse)
    {
        if (*pLast != *pTraverse)
        {
            pLast++;
            *pLast = *pTraverse;
        }

        pTraverse++;
    }

    pLast++;
    *pLast = 0;
}

bool BitwiseManipulation::IsOnNthBit(const int data, const int n)
{
    return data & (1 << n);
}

} // namespace diamond

} // namespace ootz


