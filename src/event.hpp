#pragma once

#include <unordered_map>

#include "time.hpp"

namespace Core
{
    struct Event
    {
        std::string name;
        Time time;
        uint32_t id;
        uint32_t tableID; // If event id is not 2, then table is 0, thus not remaining 
    };
}

