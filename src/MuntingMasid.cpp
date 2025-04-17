/**
 * @file MuntingMasid.cpp
 * @brief Implementasyon ng `MuntingMasid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "MuntingMasid.h"

MuntingMasid::MuntingMasid(
    Stream &stream,
    const char* appName,
    Severity minLevel,
    TimestampFunc tsFunc,
    const char* tag
) : 
    _stream(&stream),
    _appName(appName),
    _minLevel(minLevel),
    _timestampFunc(tsFunc),
    _tag(tag)
{}

void MuntingMasid::setMinSeverity(Severity level) {
    _minLevel = level;
}

void MuntingMasid::setTag(const char* tag) {
    _tag = tag;
}

void MuntingMasid::setStream(Stream &stream) {
    _stream = &stream;      // Pinapalitan ang stream sa bagong ibinigay na Stream object
}

void MuntingMasid::setTsFunc(TimestampFunc tsFunc) {
    _timestampFunc = tsFunc;    // Pinapalitan ang timestamp function
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

    // Kung may timestamp function, tawagin ito at ilathala sa stream
    if (_timestampFunc) {
        _stream->print(_timestampFunc());
    } else {
        _stream->print("[---]");      // Walang tinakda
    }
    _stream->print(" ");
    
    _stream->print("[");
    _stream->print(_severityLabel(severity));
    _stream->print("] ");

    _stream->print("[");
    _stream->print(_appName);
    _stream->print("] ");

    if (_tag) {
        _stream->print("(");
        _stream->print(_tag);
        _stream->print(")");
    }

    _stream->print(" ");
    _stream->print(message);

    _stream->println(" ");
}

// Pinaikling metodo
void MuntingMasid::emergency(const String& message) { 
    _log(EMERGENCY, message.c_str()); 
}
void MuntingMasid::alert(const String& message) { 
    _log(ALERT, message.c_str()); 
}
void MuntingMasid::critical(const String& message) { 
    _log(CRITICAL, message.c_str()); 
}
void MuntingMasid::error(const String& message) { 
    _log(ERROR, message.c_str()); 
}
void MuntingMasid::warning(const String& message) { 
    _log(WARNING, message.c_str()); 
}
void MuntingMasid::notice(const String& message) { 
    _log(NOTICE, message.c_str()); 
}
void MuntingMasid::info(const String& message) { 
    _log(INFO, message.c_str()); 
}
void MuntingMasid::debug(const String& message) { 
    _log(DEBUG, message.c_str()); 
}
