#pragma once

#include <chrono>

#include "ootz/base.h"

namespace ootz
{

namespace time
{

std::string TimePointToString(const std::chrono::system_clock::time_point& timePoint)
{
    const time_t t = std::chrono::system_clock::to_time_t(timePoint);
    std::string timeString(ctime(&t));
    timeString.pop_back();
    return timeString;
}

template<
    typename T, 
    typename = std::enable_if_t<
        std::is_same_v<T, std::chrono::steady_clock> || 
        std::is_same_v<T, std::chrono::system_clock>>>
class ElapsedTimerBase
{
public:
    using clock_type = T;
    using time_point_type = std::chrono::time_point<clock_type>;
    using duration_type = std::chrono::duration<float>;

    ElapsedTimerBase()
        : _startTime()
        , _finishTime()
        , _duration()
    {
        start();
    }

    ~ElapsedTimerBase() {}

    constexpr void start()
    {
        _startTime = clock_type::now();
    }
    
    constexpr void finish()
    {
        _finishTime = clock_type::now();
        _duration = _finishTime - _startTime;
    }

    constexpr float getElapsedTime() const 
    { 
        return _duration.count(); 
    }

protected:
    time_point_type _startTime;
    time_point_type _finishTime;
    duration_type _duration;
};

class ElapsedTimer : public ElapsedTimerBase<std::chrono::steady_clock>
{
public:
    ElapsedTimer()
        : ElapsedTimerBase<std::chrono::steady_clock>()
    {}

    ~ElapsedTimer() {}
};

class SystemElapsedTimer 
    : public ElapsedTimerBase<std::chrono::system_clock>
{
public:
    SystemElapsedTimer()
        : ElapsedTimerBase<std::chrono::system_clock>()
    {}

    ~SystemElapsedTimer() {}

    std::string getStartTime() const
    {
        return TimePointToString(_startTime);
    }

    std::string getFinishTime() const
    {
        return TimePointToString(_finishTime);
    }
};

} // namespace time

} // namespace ootz