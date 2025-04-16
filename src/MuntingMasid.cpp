/**
 * @file MuntingMasid.cpp
 * @brief Implementasyon ng `MuntingMasid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "MuntingMasid.h"

MuntingMasid::MuntingMasid(
    Stream &stream,
    const char* appName,
    Severity minLevel,
    TimestampFunc tsFunc
) : 
    _stream(&stream),
    _appName(appName),
    _minLevel(minLevel),
    _timestampFunc(tsFunc),
    _tag(nullptr)
{}

void MuntingMasid::setMinimumSeverity(Severity level) {
    _minLevel = level;
}

void MuntingMasid::setTag(const char* tag) {
    _tag = tag;
}

void MuntingMasid::showTimestamp(bool enabled) {
    _showTimestamp = enabled;
}

void MuntingMasid::showSeverityLabel(bool enabled) {
    _showSeverityLabel = enabled;
}

void MuntingMasid::showAppName(bool enabled) {
    _showAppName = enabled;
}

void MuntingMasid::showTag(bool enabled) {
    _showTag = enabled;
}

const char* MuntingMasid::_severityLabel(Severity severity) {
    static const char* labels[] = {
        "KAGI", // Emergency
        "ALRT", // Alert
        "KRIT", // Critical
        "MALI", // Error
        "BALA", // Warning
        "PNSN", // Notice
        "IMPO", // Info
        "DALI"  // Debug
    };
    return labels[severity];
}

void MuntingMasid::_log(Severity severity, const char* message) {
    if (severity > _minLevel) return; 

    // Kung may timestamp function, tawagin ito at iprint ito sa stream
    if (_showTimestamp && _timestampFunc) {
        _stream->print(_timestampFunc());
        _stream->print(" ");
    }
    
    if (_showSeverityLabel) {
        _stream->print("[");
        _stream->print(_severityLabel(severity));
        _stream->print("] ");
    }

    if (_showTag && _tag) {
        _stream->print("[");
        _stream->print(_tag);
        _stream->print("] ");
    }

    if (_showAppName) {
        _stream->print("[");
        _stream->print(_appName);
        _stream->print("] ");
    }
    _stream->println(message);
}

// Pinaikling metodo
void MuntingMasid::emergency(const char* message) { _log(EMERGENCY, message); }
void MuntingMasid::alert(const char* message) { _log(ALERT, message); }
void MuntingMasid::critical(const char* message) { _log(CRITICAL, message); }
void MuntingMasid::error(const char* message) { _log(ERROR, message); }
void MuntingMasid::warning(const char* message) { _log(WARNING, message); }
void MuntingMasid::notice(const char* message) { _log(NOTICE, message); }
void MuntingMasid::info(const char* message) { _log(INFO, message); }
void MuntingMasid::debug(const char* message) { _log(DEBUG, message); }
