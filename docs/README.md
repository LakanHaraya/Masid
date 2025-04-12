# 📖 `MuntingMasid/` Unreleased

📜 *Malapamantayan:* **LNDH-0061** *(Aktibo)*  
📅 *Petsa ng Paglalathala:* **2025-04-12**  
🔢 *Bersiyon:* **Unreleased** *(Balangkas)*  
🛠️ *Huling Rebisyon:* **2025-04-12**  
👨‍💻 *May-akda:* **Lakan Haraya Dima**  

Ang **MuntingMasid** ay isang magaan at modular na aklatan para sa pag-log
ng mensahe ayon sa antas ng kalubhaan (*severity level*), gaya ng `DEBUG`,
`INFO`, `ERROR`, atbp., batay sa lohika ng syslog sa [RFC 5424:2009](https://datatracker.ietf.org/doc/html/rfc5424). 

Ginagamit nito ang anumang `Stream` object (gaya ng `Serial`, `SoftwareSerial`, `File`, atbp.) bilang output ng log, na maaaring ikahon gamit ang timestamp at pangalan ng aplikasyon.

> Bahagi ito ng *Proyektong LundayHangin* ngunit maaari ring gamitin sa
> anumang embedded system o Arduino-based na proyekto na nangangailangan ng
> malinaw at sistematikong pag-log ng mga pangyayari.

---

## Mga Tampok

- Magaan at walang dependency bukod sa `Arduino.h`
- Paggamit ng `enum Severity` para sa antas ng kalubhaan ng mensahe
- Customizable na timestamp function
- Maaari lamang i-log ang mga mensaheng naaayon sa itinakdang minimum severity
- Lokal na pag-format ng log messages gaya ng: 
    ``` sh
    TIMESTAMP [SEVERITY] [APP-NAME] Brief message...
    ```
- Suportado ang iba't ibang pinagmumulan ng `Stream`, kabilang ang `Serial`, `SoftwareSerial`, at `File` (kung suportado)

---

## Karagdagang Dokumentasyon

- [INSTALLATION.md](../docs/INSTALLATION.md)
- [API_REFERENCE.md](../docs/API_REFERENCE.md)
- [CHANGELOG](../docs/CHANGELOG)

---

## Mga Halimbawa

Tingnan ang [`examples/`](../examples/) folder para sa mga sumusunod na sketch

> ### Testing
> 1. I-upload ang isa sa mga halimbawa sa iyong board.
> 2. Suriin kung gumagana ang heartbeat tulad ng inaasahan.

---

## Lisensiya

Ang **MuntingMasid** ay inilabas sa ilalim ng [MIT License](LICENSE)