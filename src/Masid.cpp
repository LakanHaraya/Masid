/**
 * @file Masid.cpp
 * @brief Implementasyon ng `Masid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "Masid.h"

Masid::Masid(
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
    _tag(tag),
    _logCount(0)
{}

void Masid::setMinSeverity(Severity level) {
    _minLevel = level;
}

void Masid::setTag(const char* tag) {
    _tag = tag;
}

void Masid::setStream(Stream &stream) {
    _stream = &stream;      // Pinapalitan ang stream sa bagong ibinigay na Stream object
}

void Masid::setTsFunc(TimestampFunc tsFunc) {
    _timestampFunc = tsFunc;    // Pinapalitan ang timestamp function
}

const char* Masid::_severityLabel(Severity severity) {
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

void Masid::_log(Severity severity, const char* message) {
    if (severity > _minLevel) return; 

    _logCount++;        // Itala ang bilang ng log entry

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
        _stream->print(") ");
    }

    _stream->print(message);

    _stream->println(" ");
}

// Pinaikling metodo
void Masid::emergency(const String& message) { 
    _log(EMERGENCY, message.c_str()); 
}
void Masid::alert(const String& message) { 
    _log(ALERT, message.c_str()); 
}
void Masid::critical(const String& message) { 
    _log(CRITICAL, message.c_str()); 
}
void Masid::error(const String& message) { 
    _log(ERROR, message.c_str()); 
}
void Masid::warning(const String& message) { 
    _log(WARNING, message.c_str()); 
}
void Masid::notice(const String& message) { 
    _log(NOTICE, message.c_str()); 
}
void Masid::info(const String& message) { 
    _log(INFO, message.c_str()); 
}
void Masid::debug(const String& message) { 
    _log(DEBUG, message.c_str()); 
}

size_t Masid::getLogCount() const {
    return _logCount;
}

void Masid::resetLogCount() {
    _logCount = 0;
}