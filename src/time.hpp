#pragma once

#include <cstdint>
#include <ostream>

namespace Core
{
    class Time
    {
    public:
        Time() = default;
        Time(uint32_t _hour, uint32_t _minutes);

        Time& operator=(const Time& t);
        bool operator<(const Time& t);
        bool operator>(const Time& t);
        bool operator==(const Time& t);

    private:
        uint32_t hour;
        uint32_t minutes;

        friend std::ostream& operator<<(std::ostream& output, const Time& t);
    };


    std::ostream& operator<<(std::ostream& output, const Time& t);
}
