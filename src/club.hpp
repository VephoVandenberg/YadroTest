#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

namespace Core
{
    class Time;
    struct Event;

    class Club
    {
    public:
        Club(uint32_t nTables, uint32_t coinsPerHour, const Time& start, const Time& end);
        ~Club() = default;

        void pushEvent(Event& e);
        void processEvents();

    private:
        struct Table 
        {
            uint32_t coins = 0;
            Time totalTime = Time(0, 0);
            std::string clientName = ""; // if his field is empty, table is free;
        };

        uint32_t m_nTables;
        uint32_t m_coinsPerHour;

        std::unordered_map<uint32_t, Table> m_tables; // If value exists table is not free
        std::set<std::string> m_clientsWaiting;
        std::vector<Event> m_events; 

        Time m_start;
        Time m_end;
    };
}