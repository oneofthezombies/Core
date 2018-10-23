#pragma once

#include <cassert>
#include <chrono>
#include <functional>
#include <string>

namespace ootz
{

namespace Time
{

template<typename ClockType>
class ElapsedTimerBase
{
public:
    float GetElapsedTime() const { return _elapsedTime; }

protected:
    using Clock = ClockType;
    using TimePoint = std::chrono::time_point<ClockType>;
    using Duration = std::chrono::duration<float>;

    ElapsedTimerBase(const std::function<void()>& operation)
        : _startTime()
        , _finishTime()
        , _elapsedTime(0.0f)
    {
        _Start();
        operation();
        _Finish();
    }

    ~ElapsedTimerBase() {}

    void _Start()
    {
        _startTime = Clock::now();
    }

    void _Finish()
    {
        _finishTime = Clock::now();
        _elapsedTime = Duration(_finishTime - _startTime).count();
    }

    const TimePoint& _GetStartTime() const { return _startTime; }
    const TimePoint& _GetFinishTime() const { return _finishTime; }

private:
    TimePoint _startTime;
    TimePoint _finishTime;
    float     _elapsedTime;
};

class ElapsedTimer 
    : public ElapsedTimerBase<std::chrono::steady_clock>
{
public:
    ElapsedTimer(const std::function<void()>& operation);
};

class SystemElapsedTimer 
    : public ElapsedTimerBase<std::chrono::system_clock>
{
public:
    SystemElapsedTimer(const std::function<void()>& operation);

    std::string GetStartTimeString();
    std::string GetFinishTimeString();

private:
    std::string TimePointToString(const TimePoint& timePoint);
};

}

} // namespace ootz