#pragma once

#include <Arduino.h>

enum Severity {
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR, 
    WARNING,
    NOTICE,
    INFO, 
    DEBUG
};

typedef const char* (*TimestampFunc)();

class MuntingMasid {
    public:
        MuntingMasid(Stream &stream, const char* appName, Severity minLevel = DEBUG, TimestampFunc tsFunc = nullptr);

        void setMinimumSeverity(Severity level);
        void log(Severity severity, const char* message);

        void emergency(const char* message);
        void alert(const char* message);
        void critical(const char* message);
        void error(const char* message);
        void warning(const char* message);
        void notice(const char* message);
        void info(const char* message);
        void debug(const char* message);

    private: 
        Stream* _stream;
        const char* _appName;
        Severity _minLevel;
        TimestampFunc _timestampFunc;
        const char* _severityLabel(Severity severity);
};