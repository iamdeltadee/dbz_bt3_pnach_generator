#pragma once


enum LogLevel
{
    INFO,
    WARNING,
    ERROR
};


#ifdef LOGGER_ENABLED

#include <stdio.h>

LogLevel gLogLevel = INFO;

#define LOG(aLogLevel, ...) if(gLogLevel >= aLogLevel) { printf(__VA_ARGS__); printf("\n"); }
#define SET_LOG_LEVEL(aLogLevel) gLogLevel = aLogLevel;

#else // disabled logging

#define LOG(aLogLevel, ...) 
#define SET_LOG_LEVEL(aLogLevel)

#endif // LOGGER_ENABLED