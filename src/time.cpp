#include "time.hpp"

using namespace Core;

Time::Time(uint32_t _hour, uint32_t _minutes)
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
