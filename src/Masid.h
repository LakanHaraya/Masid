#pragma once

#include <Arduino.h>

typedef const char* (*TimestampFunc)();

/**
 * @class Masid
 * @brief Lumilikha ng bagong logger na maaaring ikumpigura para sa structured logging.
 *
 * Pinapagana ng konstruktor na ito ang pagtatala ng mga log message gamit ang tinukoy
 * na output stream, pangalan ng logger, antas ng pinakamababang severity na maaaring itala, pinasadyang timestamp function,
 * at opsiyonal na tag para sa karagdagang konteksto.
 * 
 * @param stream   (Hinihingi) Output stream kung saan ilalathala ang mga log (hal. `Serial`, `SoftwareSerial`, `File`, atbp.).
 * @param logName  (Hinihingi) Pangalan ng logger o component na naglalabas ng log.
 * @param minLevel (Opsiyonal) Itakda ang minimum na severity level na ilalabas sa output. Default ay `Masid::DEBUG`.
 * @param tsFunc   (Opsiyonal) Timestamp function na magbabalik ng string (hal. oras). Default ay `nullptr`.
 * @param tag      (Opsiyonal) Tag para sa mga log upang magbigay ng karagdagang konteksto. Default ay `nullptr`.
 * 
 * @note - Kung walang `timestamp function`, walang timestamp na ilalabas sa log output.
 * 
 * @note - Ang makikitang log format sa output: `TIMESTAMP [SEVERITY] [LOGNAME] (Tag) Brief message.`
 * 
 * ### Mga Halimbawa ng Paggamit:
 * 
 * ```
 * // Pinakasimple
 * Masid masid1(Serial, "Demo1");
 * // Maglalabas: ` TIMESTAMP [DEBUG+] [Demo1] (Tag) Brief message. `
 * 
 * // May minimum severity
 * Masid masid2(Serial, "Demo2", Masid::INFO);
 * // Maglalabas: ` TIMESTAMP [INFO+] [Demo2] (Tag) Brief message. `
 * 
 * // May timestamp function
 * Masid masid3(Serial, "Demo3", Masid::DEBUG, getMillis);
 * // Maglalabas: ` 12345ms [DEBUG+] [Demo3] (Tag) Brief message. `
 * 
 * // Kompletong instantiation
 * Masid masid4(Serial, "Demo4", Masid::WARN, nullptr, "AkingTag");
 * // Maglalabas: ` [---] [WARN+] [Demo4] (Tag) Brief message. `
 * ```
 */
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

        // Kompletong konstruktor
        Masid(Stream &stream, const char* logName, Severity minLevel = Masid::INFO, TimestampFunc tsFunc = nullptr, const char* tag = nullptr);

        // Lagdas (Log)
        void emergency(const String& message);  
        void alert(const String& message);
        void critical(const String& message);
        void error(const String& message);
        void warning(const String& message);
        void notice(const String& message);
        void info(const String& message);
        void debug(const String& message);

        // Pantakda (Setter)
        void setMinSeverity(Severity level);
        void setTag(const char* tag);
        void setStream(Stream &stream);        
        void setTsFunc(TimestampFunc tsFunc);  
        void resetLogCount(); 

        // Pangkuha (Getter)
        size_t getLogCount() const;
        const char* getMinSeverity() const;

    private: 
        Stream* _stream;
        const char* _logName;
        Severity _minLevel;
        TimestampFunc _timestampFunc;
        const char* _tag;
        size_t _logCount = 0;           /** Bilang ng mga log entry */

        const char* _severityLabel(Severity severity) const;
        void _log(Severity severity, const char* message);
};