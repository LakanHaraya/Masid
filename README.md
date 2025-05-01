# 📖 `Masid/` Unreleased
![Release](https://img.shields.io/github/v/release/LakanHaraya/Masid?include_prereleases)
![Malapamantayan](https://img.shields.io/badge/malapamantayan-LNDH--0061-purple)  
![Last Commit](https://img.shields.io/github/last-commit/LakanHaraya/Masid?label=last%20commit&style=flat-square)
![First Commit](https://img.shields.io/badge/first%20commit-2025--04--12-FCD116)  
![Language](https://img.shields.io/badge/language-Filipino%20(may%20neolohismo)-0038A8)

Ang **Masid** ay isang magaan at modular na aklatan para sa paglagdas
ng mensahe (*message logging*) ayon sa antas ng kalubhaan (*severity level*), gaya ng `DEBUG`,
`INFO`, `ERROR`, atbp., batay sa lohika ng syslog sa [RFC 5424:2009](https://datatracker.ietf.org/doc/html/rfc5424). 

Ginagamit nito ang anumang `Stream` objek (gaya ng `Serial`, `SoftwareSerial`, `File`, atbp.) bilang output ng lagdas, na maaaring ikahon gamit ang tatakna (*timestamp*) at ngalan ng aplikasyon.

> Bahagi ito ng *Proyektong LundayHangin* ngunit maaari ring gamitin sa
> anumang embedded system o Arduino-based na proyekto na nangangailangan ng
> malinaw at sistematikong paglagdatos ng mga pangyayari.

---

## Mga Tampok

- Simpleng logging interface para sa iba't ibang severity levels.
- Suporta sa customizable timestamp function at log tags.
- Kakayahang mag-log gamit ang iba't ibang `Stream` output (e.g., `Serial`, `SoftwareSerial`, `File`).
- Nagbibigay ng kontrol sa minimum na severity level (`setMinSeverity()`).
- Format ng log messages na madaling basahin at i-parse.
- Suporta sa log entry counting at reset (`getLogCount()`, `resetLogCount()`).
- Flexible na reconfiguration gamit ang `setStream()`, `setTag()`, at `setTsFunc()` methods.
- May format ng log messages gaya ng: 
    ``` sh
    TIMESTAMP [SEVERITY] [APPNAME] (TAG) Brief message...
    ```

---

## Karagdagang Dokumentasyon

- [INSTALLATION.md](docs/INSTALLATION.md)
- [API_REFERENCE.md](docs/API_REFERENCE.md)
- [CHANGELOG.md](docs/CHANGELOG.md)

---

## Mga Halimbawa

Tingnan ang [`examples/`](examples/) folder para sa mga sumusunod na sketch

> ### Testing
> 1. I-upload ang isa sa mga halimbawa sa iyong board.
> 2. Suriin kung gumagana ang heartbeat tulad ng inaasahan.

---

## Lisensiya

Ang **Masid** ay inilabas sa ilalim ng [MIT License](license.txt)