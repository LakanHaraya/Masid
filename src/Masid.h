#pragma once

#include <Arduino.h>

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
            PLAIN,      /**< Simpleng format (default). */
            CSV,        /**< Comma-separated format. */
            JSON        /**< Structured format para sa machine-parsing. */
        };

        // Kompletong konstruktor
        Masid(
            Stream &stream,
            const char* logName,
            Severity minLevel = Masid::INFO,
            TimestampFunc tsFunc = nullptr,
            LogFormat format = PLAIN,
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

        // Pangtakda (Setter)
        void setMinSeverity(Severity level);
        void setTag(const char* tag);
        void setStream(Stream &stream);        
        void setTsFunc(TimestampFunc tsFunc);  
        void resetLogCount(); 
        void setLogFormat(LogFormat format);

        // Pangkuha (Getter)
        const char* getLogName() const;
        const char* getTag() const; 
        size_t getLogCount() const;
        bool shouldLog(Severity level) const;
        const char* getMinSeverityLabel() const;
        Severity getMinSeverity() const;
        LogFormat getLogFormat() const;
    

    private: 
        Stream* _stream;
        const char* _logName;
        Severity _minLevel;
        TimestampFunc _timestampFunc;
        LogFormat _format = PLAIN;
        const char* _tag;
        size_t _logCount = 0;           /** Bilang ng mga log entry */

        const char* _severityLabel(Severity severity) const;
        void _log(Severity severity, const char* message);
        void _logPlain(Severity severity, const char* message);
        void _logCSV(Severity severity, const char* message);
        void _logJSON(Severity severity, const char* message);
};