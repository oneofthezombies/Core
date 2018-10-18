#include "stdafx.h"
#include "Time.h"

#include <cassert>
#include <ctime>

namespace ootz
{

namespace Time
{

ElapsedTimer::ElapsedTimer(const std::function<void()>& operation)
    : ElapsedTimerBase(operation)
{
}

SystemElapsedTimer::SystemElapsedTimer(const std::function<void()>& operation)
    : ElapsedTimerBase(operation)
{
}

std::string SystemElapsedTimer::GetStartTimeString()
{
    return TimePointToString(_GetStartTime());
}

std::string SystemElapsedTimer::GetFinishTimeString()
{
    return TimePointToString(_GetFinishTime());
}

std::string SystemElapsedTimer::TimePointToString(const TimePoint& timePoint)
{
    std::time_t time = Clock::to_time_t(timePoint);

    std::string timeStr(ctime(&time));
    timeStr.pop_back();

    return timeStr;
}

} // namespace Time

} // namespace ootz
