#include <iostream>
#include <fstream>
#include <sstream>

#include "src/event.hpp"
#include "src/time.hpp"
#include "src/club.hpp"

bool strToUInt32(const std::string& s, uint32_t& n);
bool strToTime(const std::string& s, Core::Time& t);
bool parseEventRecord(const std::string& s, Core::Club& club);
bool checkName(const std::string& s);

const std::string g_criteria = "abcdefghijklmnopqrstuvwxyz0123456789_-";

int main(int argc, char **argv)
{
    std::cout << 46 / 60 << std::endl; 

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cout << "ERROR::Could_not_open '" << argv[1] << '\'' << std::endl;
    }

    std::string line;
    std::getline(inputFile, line);
    
    // Get number of tables of Club
    uint32_t nTables;
    if (!strToUInt32(line, nTables))
    {
        std::cout << "Error::'" << line << '\'' << std::endl;
        return -1;
    }

    // Get working hours of Club
    std::string start, end;
    Core::Time tStart, tEnd;
    std::getline(inputFile, start, ' ');
    std::getline(inputFile, end, '\n');
    if (!strToTime(start, tStart) || !strToTime(end, tEnd))
    {
        std::cout << "Error::Read_time::'" << start << ' ' << end  << '\'' << std::endl;
        return -1;
    }
    
    if (tStart > tEnd || tStart == tEnd)
    {
        std::cout << "Error::Invalid_time_range'" << start << ' ' << end  << '\'' << std::endl;
        return -1;
    }

    // Get coins per hour
    std::getline(inputFile, line);
    uint32_t coinsPerHour;
    if (!strToUInt32(line, coinsPerHour))
    {
        std::cout << "Error::'" << line << '\'' << std::endl;
        return -1;
    }

    Core::Club club(nTables, coinsPerHour, tStart, tEnd);
    // Parse all commands
    while (std::getline(inputFile, line))
    {
        if (!parseEventRecord(line, club))
        {
            std::cout << "Error::'" << line << '\'' << std::endl;
            return -1;
        }
    }

    club.processEvents();

    return 0;
}

bool strToUInt32(const std::string& s, uint32_t& n)
{
    n = 0;
    for (uint32_t i = 0; i < s.size(); i++)
    {
        if (!std::isdigit(s[i]))
        {
            return false;
        }
        n = n * 10 + s[i] - '0';
    }

    return true;
}

bool strToTime(const std::string& s, Core::Time& t)
{
    int32_t hour = 0;
    int32_t minutes = 0;

    if (s.size() != 5 && s[2] == ':')
    {
        return false;
    }

    bool hoursCalculated = false;
    for (uint32_t i = 0; i < s.size(); i++)
    {
        if (s[i] == ':')
        {
            hoursCalculated = true;
            continue;
        }

        if (!std::isdigit(s[i]))
        {
            return false;
        }

        if (!hoursCalculated)
        {
            hour = hour * 10 + s[i] - '0';
        }
        else
        {
            minutes = minutes * 10 + s[i] - '0';
        }
    }

    if (hour > 23 || minutes > 59)
    {
        return false;
    }

    t = Core::Time(hour, minutes);

    return true;
}

bool checkName(const std::string& s)
{
    return std::string::npos == s.find_first_not_of(g_criteria);
}

bool parseEventRecord(const std::string& s, Core::Club& club)
{
    std::vector<std::string> tokens;
    
    std::stringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, ' '))
    {
        tokens.push_back(token);
    }
    
    if (tokens.size() != 3 && tokens.size() != 4)
    {
        return false;
    }

    Core::Time t;
    uint32_t id;
    
    if (!strToTime(tokens[0], t) || 
        !strToUInt32(tokens[1], id) || 
        !checkName(tokens[2]))
    {
        return false;
    }

    switch(id)
    {
    case 1: 
    case 3:
    case 4: {
        Core::Event e;
        e.id = id;
        e.name = tokens[2];
        e.time = t;
        e.tableID = 0;

        club.pushEvent(e);
    }break;

    case 2: {
        uint32_t tableId = 0;
        if (!strToUInt32(tokens[3], tableId))
        {
            return false;
        }

        Core::Event e;
        e.id = id;
        e.name = tokens[2];
        e.time = t;
        e.tableID = tableId;

        club.pushEvent(e);
    }break;
    
    default: {
        return false;
    }break;
    }

    return true;
}

