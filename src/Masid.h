#pragma once

#include <Arduino.h>
#include <SD.h>

typedef const char* (*TimestampFunc)();

class Masid {
    public:
        enum Severity : uint8_t {
            EMERGENCY,  /**< KAGIPITAN: Hindi na maaaring maaaring magpatuloy ang sistema. */
            ALERT,      /**< ALERTO: Agarang aksiyon ay kinakailangan. */
            CRITICAL,   /**< KRITIKAL: Malubhang kondisyon ng sistema. */
            ERROR,      /**< KAMALIAN: Pangkalahatang pagkakamali. */
            WARNING,    /**< BABALA: Posibleng isyu o anomalya. */
            NOTICE,     /**< PANSIN: Karaniwan ngunit mahalagang kondisyon. */
            INFO,       /**< IMPORMASYON: Karaniwang operasyon ng sistema. */
            DEBUG       /**< DALISAP: Detalyado para sa debugging. */
        };

        enum LogFormat : uint8_t {
            SIMPLE,      /**< Simpleng format (default). */
            CSV,        /**< Comma-separated format. */
            JSON        /**< Structured format para sa machine-parsing. */
        };

        // Kompletong konstruktor
        Masid(
            Stream &stream,
            const char* logName,
            Severity minLevel = Masid::INFO,
            TimestampFunc tsFunc = nullptr,
            LogFormat format = SIMPLE,
            const char* tag = nullptr
        );

        // Tagalista (Log)
        void emergency(const String& message);  
        void alert(const String& message);
        void critical(const String& message);
        void error(const String& message);
        void warning(const String& message);
        void notice(const String& message);
        void info(const String& message);
        void debug(const String& message);

        // Stream management utilities
        bool hasStream(Stream& stream) const;
        bool addStreamIfAbsent(Stream& stream, LogFormat format = SIMPLE);

        // Pangtakda (Setter)
        void setMinSeverity(Severity level);
        void setTag(const char* tag);
        void setStream(Stream &stream);        
        void setTsFunc(TimestampFunc tsFunc);  
        void resetLogCount(); 
        void setLogFormat(LogFormat format);
        bool addStream(Stream& stream, LogFormat format = SIMPLE);
        void clearStreams();
        bool addFileStream(File& file, LogFormat format = SIMPLE);

        // Pangkuha (Getter)
        const char* getLogName() const;
        const char* getTag() const; 
        size_t getLogCount() const;
        bool shouldLog(Severity level) const;
        const char* getMinSeverityLabel() const;
        Severity getMinSeverity() const;
        LogFormat getLogFormat() const;
        const char* getLogFormatLabel() const;
        uint8_t getStreamCount() const;
    
    private: 
        static const uint8_t MAX_STREAMS = 4; 
        struct StreamConfig {
            Stream* stream;
            LogFormat format;
        };
        StreamConfig _streams[MAX_STREAMS];
        uint8_t _streamCount = 0;
        const char* _logName;
        Severity _minLevel;
        TimestampFunc _timestampFunc;
        LogFormat _format = SIMPLE;
        const char* _tag;
        size_t _logCount = 0;           /** Bilang ng mga log entry */

        const char* _severityLabel(Severity severity) const;
        void _log(Severity severity, const char* message);
        void _logSimple(Stream* s, Severity severity, const char* message);
        void _logCSV(Stream* s, Severity severity, const char* message);
        void _logJSON(Stream* s, Severity severity, const char* message);
};