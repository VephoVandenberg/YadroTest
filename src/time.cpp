#include "time.hpp"

using namespace Core;

Time::Time(int32_t _hour, int32_t _minutes)
    : hour(_hour)
    , minutes(_minutes)
{
}

Time& Time::operator=(const Time& t)
{
    if (*this == t)
    { 
        return *this;
    }

    hour = t.hour;
    minutes = t.minutes;

    return *this;
}

bool Time::operator==(const Time& t)
{
    return hour == t.hour && minutes == t.minutes;
}

bool Time::operator<(const Time& t)
{
    if (hour < t.hour)
    {
        return true;
    }

    if (hour == t.hour && minutes < t.minutes)
    {
        return true;
    }

    return false;
}

bool Time::operator>(const Time& t)
{
    return !(*this < t);
}

Time& Time::operator+=(const Time& t) 
{
    hour += t.hour;
    hour += (minutes + t.minutes) / 60;

    minutes = (minutes + t.minutes) % 60;

    return *this;
}

Time Time::operator+(const Time& t)
{
    int32_t hour_ = hour + t.hour;
    hour_ += (minutes + t.minutes) / 60;
    int32_t minutes_ = (minutes + t.minutes) % 60;
    
    return Time(hour_, minutes_);
}

Time Time::operator-(const Time& t) 
{
    int32_t hour_ = hour - t.hour;
    hour -= (minutes - t.minutes) < 0 ? 1 : 0;
    int32_t minutes_ = (minutes - t.minutes) < 0 ? (60 - std::abs(minutes - t.minutes)) : minutes - t.minutes;
    return Time(hour_, minutes_);
}

std::ostream& Core::operator<<(std::ostream& output, const Time& t)
{
    if (t.hour < 10)
    {
        output << 0;
    }
    output << t.hour << ':';

    if (t.minutes < 10)
    {
        output << 0;
    }
    output << t.minutes;

    return output;
}
