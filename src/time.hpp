#pragma once

#include <cstdint>
#include <ostream>

namespace Core
{
    class Time
    {
    public:
        Time() = default;
        Time(int32_t _hour, int32_t _minutes);

        inline int32_t getHour() const { return hour; }
        inline int32_t getMinute() const { return minutes; } 

        Time& operator=(const Time& t);
        bool operator<(const Time& t);
        bool operator>(const Time& t);
        bool operator==(const Time& t);
        Time& operator+=(const Time& t);
        Time operator+(const Time& t);
        Time operator-(const Time& t);

    private:
        int32_t hour;
        int32_t minutes;

        friend std::ostream& operator<<(std::ostream& output, const Time& t);
    };


    std::ostream& operator<<(std::ostream& output, const Time& t);
}
