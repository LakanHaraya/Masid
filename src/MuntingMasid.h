#pragma once

#include <Arduino.h>

/**
 * @brief Mga antas ng kalubhaan (severity level) para sa pag-log ng mensahe.
 */
enum Severity {
    EMERGENCY,  /**< KAGIPITAN: Hindi na maaaring maaaring magpatuloy ang sistema. */
    ALERT,      /**< ALERTO: Agarang aksiyon ay kinakailangan. */
    CRITICAL,   /**< KRITIKAL: Malubhang kondisyon ng sistema. */
    ERROR,      /**< KAMALIAN: Pangkalahatang pagkakamali. */
    WARNING,    /**< BABALA: Posibleng isyu o anomalya. */
    NOTICE,     /**< PANSIN: Karaniwan ngunit mahalagang kondisyon. */
    INFO,       /**< IMPORMASYON: Karaniwang operasyon ng sistema. */
    DEBUG       /**< DALISAP: Detalyado para sa debugging. */
};

/**
 * @brief Uri ng function pointer para sa timestamp function.
 * 
 * Ginagamit upang magbigay ng timestamp string para sa bawat log entry.
 */
typedef const char* (*TimestampFunc)();

/**
 * @class MuntingMasid
 * @brief Lumilikha ng bagong logger na maaaring ikumpigura para sa structured logging.
 *
 * Pinapagana ng konstruktor na ito ang pagtatala ng mga log message gamit ang tinukoy
 * na output stream, pangalan ng application, antas ng minimum na severity, timestamp function,
 * at opsiyonal na tag para sa karagdagang konteksto.
 * 
 * @param stream   Humihingi ng output stream kung saan ilalathala ang mga log (hal. `Serial`, `SoftwareSerial`, `File`, atbp.).
 * @param appName  Humihingi ng pangalan ng application o component na naglalabas ng log.
 * @param minLevel Itinatakda ang minimum na severity level na ilalabas sa output. Default ay `DEBUG`.
 * @param tsFunc   Opsiyonal na timestamp function na magbabalik ng string (hal. oras). Default ay `nullptr`.
 * @param tag      Opsiyonal na tag para sa mga log upang magbigay ng karagdagang konteksto. Default ay `nullptr`.
 * 
 * @note - Kung walang `timestamp function`, walang timestamp na ilalabas sa log output.
 * 
 * @note - Ang makikitang log format sa output: `TIMESTAMP [SEVERITY] [APPNAME] (Tag) Brief message.`
 * 
 * ### Mga Halimbawa ng Paggamit:
 * 
 * ```
 * // Pinakasimple
 * MuntingMasid masid1(Serial, "Demo1");
 * // Maglalabas: ` TIMESTAMP [DEBUG+] [Demo1] (Tag) Brief message. `
 * 
 * // May minimum severity
 * MuntingMasid masid2(Serial, "Demo2", INFO);
 * // Maglalabas: ` TIMESTAMP [INFO+] [Demo2] (Tag) Brief message. `
 * 
 * // May timestamp function
 * MuntingMasid masid3(Serial, "Demo3", DEBUG, getMillis);
 * // Maglalabas: ` 12345ms [DEBUG+] [Demo3] (Tag) Brief message. `
 * 
 * // Kompletong instantiation
 * MuntingMasid masid4(Serial, "Demo4", WARN, nullptr, "AkingTag");
 * // Maglalabas: ` [---] [WARN+] [Demo4] (Tag) Brief message. `
 * ```
 */
class MuntingMasid {
    public:
        MuntingMasid(Stream &stream, const char* appName, Severity minLevel = DEBUG, TimestampFunc tsFunc = nullptr, const char* tag = nullptr);

        /** 
         * @brief Itinatakda ng pinakamababang severity level na dapat ilathala sa log output.
         * 
         * Kapag tinawag, ang logger ay hindi na maglalabas ng mga log entry na may severity level
         * na mas mababa sa itinakda. Halimbawa, kung itinakda sa `WARNING`, tanging mga mensaheng
         * may kapantay at mataas na priyoridad tulad ng `WARNING`, `ERROR`, `CRITICAL`, at pataas lamang ang lalabas.
         * 
         * #### Mga Antas ng Severity:
         * 
         * |– `EMERGENCY` – `[KAGI]`: Hindi na maaaring maaaring magpatuloy ang sistema.
         * 
         * |– `ALERT` – `[ALRT]`: Agarang aksiyon ay kinakailangan.
         * 
         * |– `CRITICAL` – `[KRIT]`: Malubhang kondisyon ng sistema.
         * 
         * |– `ERROR` – `[MALI]`: Pangkalahatang pagkakamali.
         * 
         * |– `WARNING` – `[BALA]`: Posibleng isyu o anomalya.
         * 
         * |– `NOTICE` – `[PNSN]`: Karaniwan ngunit mahalagang kondisyon. 
         * 
         * |– `INFO` – `[IMPO]`: Karaniwang operasyon ng sistema. 
         * 
         * |– `DEBUG` – `[DALI]`: Detalyado para sa debugging. 
         * 
         * @param[in] level Ang bagong minimum severity level (hal. `DEBUG`, `INFO`, `WARNING`, atbp.).
         * 
         * #### Halimbawa ng Paggamit:
         * ```cpp
         * masid.setMinSeverity(WARNING);
         * masid.info("Hindi na ito lalabas.");       // Hindi ito ipapakita
         * masid.error("May problema!");              // Ito ay ipapakita
         * ```
         */
        void setMinSeverity(Severity level);
        
        /**
         * 
         * @brief Itinatakda ang opsiyonal na tag na idadagdag sa bawat log entry para sa karagdagang konteksto.
         * 
         * Maaaring gamitin ang tag upang tukuyin ang bahagi ng sistema, device ID, o anumang
         * kategorya para sa mas madaling pag-trace ng log outputs. Kung walang tag na itatakda,
         * maaaring itakda ito sa `nullptr` upang alisin.
         * 
         * @param[in] tag Isang C-string na magsisilbing tag sa bawat log line (hal. `"Sensor-A"`, `"GPS"`).  
         * Gumamit ng `nullptr` kung walang nais gamitin na tag.
         * 
         * ### Halimbawa ng Paggamit:
         * ```cpp
         * masid.setTag("Sensor-A");
         * masid.notice("Mababa ang signal."); 
         * // Maglalabas: ` TIMESTAMP [SEVERITY] [APPNAME] (Sensor-A) Mababa ang signal. `
         * 
         * masid.setTag(nullptr);
         * masid.notice("Walang tag na ito."); 
         * // Maglalabas: ` TIMESTAMP [SEVERITY] [APPNAME] Mababa ang signal. `
         * ```
         * 
         */
        void setTag(const char* tag);

        void setStream(Stream &stream);        
        void setTsFunc(TimestampFunc tsFunc);   

        size_t getLogCount() const;

        void resetLogCount();

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `EMERGENCY`.
         * 
         * Ginagamit ito para mag-log ng mga mensaheng pangkagipitan, tulad ng mga
         * sistemang pumalya o mga pagkabigo na hindi na kayang itama ng sistema.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.emergency("Kagipitang mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. int → String)
         * masid.emergency("Nadetek ang pagkabigo: " + String(errorCode) + ", di makapagpatuloy.")
         * ```
         */
        void emergency(const String& message);  

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `ALERT`.
         * 
         * Ginagamit ito kapag may nakitang alert condition, tulad ng pagkaabot sa kritikal na limitasyon.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.alert("Alertong mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. int → String)
         * masid.alert("Malapit nang mapuno sa maximum na lulan nito: " + String(currentLoad) + "%.")
         * ```
         */
        void alert(const String& message);

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `CRITICAL`.
         * 
         * Ginagamit ito para sa mga seryosong error na nakakaapekto sa pangunahing operasyon, ngunit hindi pa isang ganap na pagkabigo.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.critical("Kritikal na mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. int → String)
         * masid.critical("Kritikal na pagkakamali sa kalibrasyon ng sensor: " + String(sensorID) + " ay hindi tumutugma.")
         * ```
         */
        void critical(const String& message);

        /** 
         *
         * @brief Nagpapadala ng mensahe sa log na may severity na `ERROR`.
         * 
         * Ginagamit ito para sa mga error na nagiging sanhi ng pag-abort  ng ilang proseso o operasyon.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.error("Kamaliang mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos
         * masid.error("Nangyari habang kumokonekta sa server: " + String(serverIP) + ". Tumigil ang operasyon.")
         * ```
         */
        void error(const String& message);

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `WARNING`.
         * 
         * Ginagamit kapag may mga babala ukol sa sistema, tulad ng mga mahihinang signal o mababang baterya.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.warning("Babalang mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. int → String)
         * masid.warning("Mababang antas ng baterya: " + String(batteryLevel) + "%.")
         * ```
         */
        void warning(const String& message);

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `NOTICE`.
         * 
         * Ginagamit ito para sa mga impormasyon ukol sa mga normal na operasyon ng sistema, ngunit may kahalagahan sa isang operasyon o transisyon.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.notice("Pansining mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. int → String)
         * masid.notice("Lumilipat ang sistema sa moda ng matipid-koryente: " + String(powerMode))
         * ```
         */
        void notice(const String& message);

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `INFO`.
         * 
         * Ginagamit ito upang magtala ng mga mensaheng nagpapabatid ng
         * mahahalagang impormasyon hinggil sa kasalukuyang operasyon ng sistema.
         * 
         * @param[in] message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.info("Nagsimula na ang operasyon!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. float → String)
         * masid.info("Matatag na temperatura: " + String(temp) + "°C.")
         * ```
         */
        void info(const String& message);

        /** 
         * 
         * @brief Nagpapadala ng mensahe sa log na may severity na `DEBUG`.
         * 
         * Ginagamit para sa debugging na impormasyon na makakatulong sa pagsusuri ng code at pagpapatakbo ng sistema sa mga partikular na bahagi.
         * 
         * @param message Ang mensaheng ilalathala sa log.
         * 
         * #### Mga Halimbawa ng Paggamit:
         * 
         * ```
         * // Direktang Paggamit ng String Literal
         * masid.info("Dalisapang mensahe!")
         * 
         * // Pilit na Pagbuo ng String mula sa Ibang Uri ng Datos (hal. float → String)
         * masid.debug("Pagbasa sa sensor: " + String(sensorValue) + " sa " + String(millis()) + "ms.")
         * ```
         */
        void debug(const String& message);

    private: 
        Stream* _stream;                /** Pointer sa stream output */
        const char* _appName;           /** Pangalan ng application */
        Severity _minLevel;             /** Minimum na severity level */
        TimestampFunc _timestampFunc;   /** Function pointer para sa timestamp (kung meron) */
        const char* _tag;

        size_t _logCount = 0;           /** Bilang ng mga log entry */

        /**
         * @brief Kunin ang label ng severity bilang 4-character abbreviation.
         * 
         * @param severity Ang enum value ng severity.
         * @return `const char*` Ang katumbas na label string.
         */
        const char* _severityLabel(Severity severity);

        /**
         * @brief Mag-log ng mensahe na may tinukoy na severity.
         * 
         * @param severity Ang kalubhaan ng mensahe.
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void _log(Severity severity, const char* message);
};