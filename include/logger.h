#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

enum LogType
{
    UNKNOWN = 0,
    FATAL   = 1,
    ERROR   = 2,
    PLAY    = 3,
    INFO    = 4,
    DEBUG   = 5,
    DUMP    = 6
};

struct Logger
{
    static Logger* getLogger()
    {
        static Logger lgr;
        return &lgr;
    }

    void log(const LogType& logType, const std::string& msg) const
    {
        if (logType <= logLevel)
            std::cout << logType << " - " << msg << std::endl;
    }

//    LogType logLevel = LogType::PLAY;
    LogType logLevel = LogType::DUMP;
};


#endif // LOGGER_H
