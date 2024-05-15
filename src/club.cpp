#include <iostream>

#include "time.hpp"
#include "event.hpp"

#include "club.hpp"

using namespace Core;

enum class Error : int8_t
{
    YouShallNotPass,
    NotOpenYet,
    PlaceIsBusy,
    ClientUknown,
    ICantWaitNoLonger,
};

std::unordered_map<Error, const std::string> g_errors = {
    { Error::YouShallNotPass,   "YouShallNotPass"   },
    { Error::NotOpenYet,        "NotOpenYet"        },
    { Error::PlaceIsBusy,       "PlaceIsBusy"       },
    { Error::ClientUknown,      "ClientUknown"      },
    { Error::ICantWaitNoLonger, "ICantWaitNoLonger" },
};

Club::Club(uint32_t nTables, uint32_t coinsPerHour, const Time& start, const Time& end)
    : m_nTables(nTables)
    , m_coinsPerHour(coinsPerHour)
    , m_start(start)
    , m_end(end)
{
    for (uint32_t iTable = 1; iTable <= m_nTables; iTable++)
    {
        m_tables[iTable] = Table{.coins = 0, .totalTime = Time(0, 0), .clientName = ""};
    }
}

void Club::pushEvent(Event& e)
{
    m_events.push_back(e);
}

void Club::processEvents()
{
    std::cout << m_start << std::endl;

    for (auto& e : m_events)
    {
        std::cout << e.time << ' ' << e.id << ' ' << e.name << ' ';
        switch(e.id)
        {
        case 1:{
            std::cout << std::endl;
            if (m_clientsWaiting.count(e.name))
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::YouShallNotPass] << std::endl;
                break;
            }
            if (e.time < m_start)
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::NotOpenYet] << std::endl;
                break;
            }

            m_clientsWaiting.insert(e.name);
        }break;

        case 2:{
            std::cout << e.tableID << std::endl;

            if (!m_clientsWaiting.count(e.name))
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::ClientUknown] << std::endl;
                break;
            }

            
            if (!m_tables[e.tableID].clientName.empty())
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::PlaceIsBusy] << std::endl;
                break;
            }

            for (size_t iTable = 1; iTable <= m_nTables; iTable++)
            {
                if (m_tables[iTable].clientName == e.name)
                {
                    m_tables[iTable].clientName = "";
                }
            }

            if (m_tables[e.tableID].clientName.empty())
            {
                m_tables[e.tableID].clientName = e.name;
                m_clientsWaiting.erase(e.name);
            }

        }break;

        case 3:{
            std::cout << std::endl;
            if (!m_clientsWaiting.count(e.name))
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::ClientUknown] << std::endl;
                break;
            }

            bool hasFreeTable = false;
            for (auto& pair : m_tables)
            {
                if (pair.second.clientName.empty())
                {
                    hasFreeTable = true;
                    break;
                }
            }

            if (hasFreeTable)
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::ICantWaitNoLonger] << std::endl;
                break;
            }

            if (m_clientsWaiting.size() > m_nTables)
            {
                std::cout << e.time << ' ' << 11 << ' ' << e.name << std::endl;
            }
        }break;

        case 4:{
            std::cout << std::endl;

            bool hasClient = false;
            for (uint32_t iTable = 1; iTable <= m_nTables; iTable++)
            {
                if (m_tables[iTable].clientName == e.name)
                {
                    m_tables[iTable].clientName = "";
                    hasClient = true;

                    if (!m_clientsWaiting.empty())
                    {
                        m_tables[iTable].clientName = *m_clientsWaiting.begin();
                        m_clientsWaiting.erase(*m_clientsWaiting.begin());
                        std::cout << e.time << ' ' << 12 << ' ' << e.name << ' ' << iTable << std::endl; 
                    }

                    break;
                }
            }

            if (hasClient)
            {
                break;
            }

            if (!m_clientsWaiting.count(e.name))
            {
                std::cout << e.time << ' ' << 13 << ' ' << g_errors[Error::ClientUknown] << std::endl;
                break;
            }
            
        }break;
        }

        
    }

    for (uint32_t iTable = 1; iTable <= m_nTables; iTable++)
    {
        if (!m_tables[iTable].clientName.empty())
        {
            m_clientsWaiting.insert(m_tables[iTable].clientName);
        }
    }

    for (auto& client : m_clientsWaiting)
    {
        std::cout << m_end << ' ' << 4 << ' ' << client << std::endl;
    }

    std::cout << m_end << std::endl;
}

