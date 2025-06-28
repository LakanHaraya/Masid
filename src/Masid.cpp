/**
 * @file Masid.cpp
 * @brief Implementasyon ng `Masid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "Masid.h"

// Kompletong konstruktor
Masid::Masid(Stream &stream, const char* logName, Severity minLevel, TimestampFunc tsFunc, const char* tag) 
    : _stream(&stream),
      _logName(logName),
      _minLevel(minLevel),
      _timestampFunc(tsFunc),
      _tag(tag),
      _logCount(0) {}

// -----------------------------------------

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

bool Masid::shouldLog(Severity level) const {
    return level <= _minLevel;  // Nagbabalik ng true kung ang severity level ay dapat i-log
}

const char* Masid::_severityLabel(Severity severity) const {
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
    _stream->print(_logName);
    _stream->print("] ");

    if (_tag) {
        _stream->print("(");
        _stream->print(_tag);
        _stream->print(") ");
    }

    _stream->println(message);
}

// Pinaikling metodo
void Masid::emergency(const String& message) { 
    _log(Masid::EMERGENCY, message.c_str()); 
}
void Masid::alert(const String& message) { 
    _log(Masid::ALERT, message.c_str()); 
}
void Masid::critical(const String& message) { 
    _log(Masid::CRITICAL, message.c_str()); 
}
void Masid::error(const String& message) { 
    _log(Masid::ERROR, message.c_str()); 
}
void Masid::warning(const String& message) { 
    _log(Masid::WARNING, message.c_str()); 
}
void Masid::notice(const String& message) { 
    _log(Masid::NOTICE, message.c_str()); 
}
void Masid::info(const String& message) { 
    _log(Masid::INFO, message.c_str()); 
}
void Masid::debug(const String& message) { 
    _log(Masid::DEBUG, message.c_str()); 
}

// ------------------------
// Mga Pangkuhang Metodo
// ------------------------

size_t Masid::getLogCount() const {
    return _logCount;
}

const char* Masid::getMinSeverity() const {
    return _severityLabel(_minLevel);
}

void Masid::resetLogCount() {
    _logCount = 0;
}