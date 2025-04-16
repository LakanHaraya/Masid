#pragma once

#include <Arduino.h>

/**
 * @brief Mga antas ng kalubhaan para sa pag-log ng mensahe.
 */
enum Severity {
    EMERGENCY,  /** KAGIPITAN: Hindi na maaaring maaaring magpatuloy ang sistema. */
    ALERT,      /** ALERTO: Agarang aksiyon ay kinakailangan. */
    CRITICAL,   /** KRITIKAL: Malubhang kondisyon ng sistema. */
    ERROR,      /** KAMALIAN: Pangkalahatang pagkakamali. */
    WARNING,    /** BABALA: Posibleng isyu o anomalya. */
    NOTICE,     /** PANSIN: Karaniwan ngunit mahalagang kondisyon. */
    INFO,       /** IMPORMASYON: Karaniwang operasyon ng sistema. */
    DEBUG       /** DALISAP: Detalyado para sa debugging. */
};

/**
 * @brief Uri ng function pointer para sa timestamp function.
 * 
 * Ginagamit upang magbigay ng timestamp string para sa bawat log entry.
 */
typedef const char* (*TimestampFunc)();

/**
 * @class MuntingMasid
 * @brief Isang magaan na logger na gumagamit ng syslog-style severity levels.
 * 
 * Maaaring ikumpigura upang mag-log lamang ng mga mensaheng mas mataas o
 * katumbas ng itinalagang minimum na kalubhaan (severity).
 */
class MuntingMasid {
    public:
        /**
         * @brief Konstruktor ng MuntingMasid.
         * 
         * @param stream Ang output stream kung saan ilalathala ang mga log (hal. `Serial`).
         * @param appName Pangalan ng application o component na naglalabas ng log.
         * @param minLevel Minimum na severity level na ilalabas sa output. Default ay `DEBUG`.
         * @param tsFunc Opsiyonal na timestamp function na magbabalik ng string (hal. oras).
         */
        MuntingMasid(Stream &stream, const char* appName, Severity minLevel = DEBUG, TimestampFunc tsFunc = nullptr);

        /**
         * @brief Itakda ng pinakamababang severity level na ilalabas sa output.
         * 
         * @param level Bagong minimum severity level.
         */
        void setMinimumSeverity(Severity level);
        
        /**
         * @brief Itakda ang opsiyonal na tag para sa mga log
         * 
         * @param tag Ang string na magiging tag prefix ng bawat log entry.
         */
        void setTag(const char* tag);

        void showTimestamp(bool enabled);
        void showSeverityLabel(bool enabled);
        void showAppName(bool enabled);
        void showTag(bool enabled);

        /** 
         * @brief Pinaikling log function para sa `EMERGENCY`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void emergency(const char* message);  

        /** 
         * @brief Pinaikling log function para sa `ALERT`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void alert(const char* message);

        /** 
         * @brief Pinaikling log function para sa `CRITICAL`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void critical(const char* message);

        /** 
         * @brief Pinaikling log function para sa `ERROR`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void error(const char* message);

        /** 
         * @brief Pinaikling log function para sa `WARNING`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void warning(const char* message);

        /** 
         * @brief Pinaikling log function para sa `NOTICE`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void notice(const char* message);

        /** 
         * @brief Pinaikling log function para sa `INFO`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void info(const char* message);

        /** 
         * @brief Pinaikling log function para sa `DEBUG`
         * 
         * @param message Ang mismong mensahe na ilalabas sa output.
         */
        void debug(const char* message);

    private: 
        Stream* _stream;                /** Pointer sa stream output */
        const char* _appName;           /** Pangalan ng application */
        Severity _minLevel;             /** Minimum na severity level */
        TimestampFunc _timestampFunc;   /** Function pointer para sa timestamp (kung meron) */
        const char* _tag;
        bool _showTimestamp = true;            /** Flag para sa pagpapakita ng timestamp */
        bool _showSeverityLabel = true;        /** Flag para sa pagpapakita ng severity level */
        bool _showAppName = true;              /** Flag para sa pagpapakita ng app name */
        bool _showTag = true;                  /** Flag para sa pagpapakita ng tag */

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