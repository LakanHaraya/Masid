/**
 * @file Masid.cpp
 * @brief Implementasyon ng `Masid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "Masid.h"

// Kompletong konstruktor
Masid::Masid(
    Stream &stream, 
    const char* logName, 
    Severity minLevel, 
    TimestampFunc tsFunc, 
    LogFormat format,
    const char* tag) 
    : _logName(logName),
      _minLevel(minLevel),
      _timestampFunc(tsFunc),
      _format(format),
      _tag(tag),
      _logCount(0),
      _streamCount(0)
      {
        addStream(stream);  // Tiyaking may default stream
      }

// -----------------------------------------

void Masid::setMinSeverity(Severity level) {
    _minLevel = level;
}

void Masid::setTag(const char* tag) {
    _tag = tag;
}

void Masid::setStream(Stream &stream) {
    clearStreams();
    addStream(stream);
}

void Masid::setTsFunc(TimestampFunc tsFunc) {
    _timestampFunc = tsFunc;    // Pinapalitan ang timestamp function
}

void Masid::setLogFormat(LogFormat format) {
    _format = format;  // Itinatakda ang log format
}

bool Masid::addStream(Stream& stream) {
    if (_streamCount >= MAX_STREAMS) return false;
    _streams[_streamCount++] = &stream;
    return true;  // Nagdagdag ng bagong stream sa array
}

void Masid::clearStreams() {
    _streamCount = 0;  // I-clear ang lahat ng streams
}

uint8_t Masid::getStreamCount() const {
    return _streamCount;
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

    // Ihain sa tamang output format handler
    switch (_format) {
        case SIMPLE:
            _logSimple(severity, message);
            break;
        case CSV:
            _logCSV(severity, message);
            break;
        case JSON:
            _logJSON(severity, message);
            break;
        default:
            _logSimple(severity, message);  // Default sa SIMPLE kung hindi kilala ang format
    }
}

void Masid::_logSimple(Severity severity, const char* message) {
    for (uint8_t i = 0; i < _streamCount; ++i) {
        Stream* s = _streams[i];

        if (_timestampFunc) {
            s->print(_timestampFunc());
        } else {
            s->print("[---]");
        }
        s->print(" [");
        s->print(_severityLabel(severity));
        s->print("] [");
        s->print(_logName);
        s->print("] ");
        if (_tag) {
            s->print("(");
            s->print(_tag);
            s->print(") ");
        }
        s->println(message);
    }
}

void Masid::_logCSV(Severity severity, const char* message) {
    for (uint8_t i = 0; i < _streamCount; ++i) {
        Stream* s = _streams[i];

        if (_timestampFunc) {
            s->print(_timestampFunc());
        } else {
            s->print("---");
        }
        s->print(",");
        s->print(_severityLabel(severity));
        s->print(",");
        s->print(_logName);
        s->print(",");
        s->print(_tag ? _tag : "---");
        s->print(",\"");
        s->print(message);
        s->println("\"");
    }
}

void Masid::_logJSON(Severity severity, const char* message) {
    for (uint8_t i = 0; i < _streamCount; ++i) {
        Stream* s = _streams[i];

        s->print("{\"ts\":\"");
        s->print(_timestampFunc ? _timestampFunc() : "---");
        s->print("\",\"sev\":\"");
        s->print(_severityLabel(severity));
        s->print("\",\"src\":\"");
        s->print(_logName);
        s->print("\",\"tag\":\"");
        s->print(_tag ? _tag : "-");
        s->print("\",\"msg\":\"");
        s->print(message);
        s->println("\"}");
    }
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

void Masid::resetLogCount() {
    _logCount = 0;
}

bool Masid::shouldLog(Severity level) const {
    return level <= _minLevel;  // Nagbabalik ng true kung ang severity level ay dapat i-log
}

const char* Masid::getMinSeverityLabel() const {
    return _severityLabel(_minLevel);
}

Masid::Severity Masid::getMinSeverity() const {
    return _minLevel;
}

Masid::LogFormat Masid::getLogFormat() const {
    return _format;
}

const char* Masid::getTag() const {
    return _tag ? _tag : ""; 
}

const char* Masid::getLogName() const {
    return _logName; 
}

const char* Masid::getLogFormatLabel() const {
    switch (_format) {
        case SIMPLE: return "SIMPLE";
        case CSV: return "CSV";
        case JSON: return "JSON";
        default: return "DI-ALAM"; 
    }
}