# 📖 `Masid/` Unreleased
![Release](https://img.shields.io/github/v/release/LakanHaraya/Masid?include_prereleases)
![Malapamantayan](https://img.shields.io/badge/malapamantayan-LNDH--0061-purple)
![Last Commit](https://img.shields.io/github/last-commit/LakanHaraya/Masid?label=last%20commit&style=flat-square)
![First Commit](https://img.shields.io/badge/first%20commit-2025--04--12-FCD116)
![Language](https://img.shields.io/badge/language-Filipino%20(may%20neolohismo)-0038A8)
[![Mga Pagkilala](https://img.shields.io/badge/%F0%9F%93%9D-CHANGELOG-blue)](docs/CHANGELOG.md)

# *Magmamasid na Alalay para sa Sistemang Impormasyon at Diyagnostika*

<div align="center">

  <img src="https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg" alt="Arduino Logo" title="Arduino" width="90" style="vertical-align:middle;" loading="lazy"/>
  <img src="https://upload.wikimedia.org/wikipedia/commons/c/cd/PlatformIO_logo.svg" alt="PlatformIO Logo" title="PlatformIO" width="90" style="vertical-align:middle;" loading="lazy"/>
  <img src="https://upload.wikimedia.org/wikipedia/commons/0/0c/MIT_logo.svg" alt="MIT Logo" title="MIT License" width="90" style="vertical-align:middle;" loading="lazy"/>

  <p><em>Ginagamit sa proyektong ito ang mga sumusunod na teknolohiya at pamantayan.<br>Walang ipinahihiwatig na ugnayan o pag-eendorso</em></p>

</div>

Ang **Masid** ay isang magaan at modular na aklatan para sa paglagdas
ng mensahe (*message logging*) ayon sa antas ng kalubhaan (*severity level*), gaya ng `Masid::DEBUG`,
`Masid::INFO`, `Masid::ERROR`, atbp., batay sa lohika ng syslog sa [RFC 5424:2009](https://datatracker.ietf.org/doc/html/rfc5424). 

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
    [TIMESTAMP] [SEVERITY] [LOGNAME] (CTAG) Maikling mensahe.
    ```
    Halimbawa:
    ``` sh
    [2025-06-02T12:34:56] [IMPO] [Angkla] (INIS) Inisyalisasyon ng sistema.
    ```
    ``` sh
    [---] [MALI] [KtrlrPad] Nabigo ang komunikasyon! 
    ```

---

## Karagdagang Dokumentasyon

- [docs/INSTALLATION.md](docs/INSTALLATION.md) – Paano Mag-instal?
- [docs/API_REFERENCE.md](docs/API_REFERENCE.md) – Paano Gamitin?
- [docs/CHANGELOG.md](docs/CHANGELOG.md) – Ano ang Bago?
- [docs/ATTRIBUTIONS.md](docs/ATTRIBUTIONS.md) – Mga Pagkilala.

---

## Mga Halimbawa <img src="https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg" alt="Arduino Logo" width="20" style="vertical-align:middle;"/> <img src="https://upload.wikimedia.org/wikipedia/commons/c/cd/PlatformIO_logo.svg" alt="PlatformIO Logo" width="20" style="vertical-align:middle;"/>

Tingnan ang [`examples/`](examples/) folder para sa mga sumusunod na sketch.

1. 
2. 
3. 

> ### Testing
> 1. I-upload ang isa sa mga halimbawa sa iyong board.
> 2. Suriin kung gumagana ang heartbeat tulad ng inaasahan.

---

## Lisensiya <img src="https://upload.wikimedia.org/wikipedia/commons/0/0c/MIT_logo.svg" alt="Massachusetts Institute of Technology (MIT) Logo" width="40" style="vertical-align:middle;"/>
Ang **Tibok** ay inilabas sa ilalim ng [MIT License](LICENSE)

## Mga Pagkilala

Ang proyektong ito ay gumagamit ng ilang opisyal na logo at larawan
para sa pang-impormasyon at pang-edukasyon na layunin. Para sa
detalyadong tala ng mga pinagmulan at lisensiya ng mga ito,
mangyaring basahin ang [docs/ATTRIBUTIONS.md](docs/ATTRIBUTIONS.md).