# Dalawang Uno Boards: Serial Logging sa Magkaibang Monitor

📘 *Halimbawa ng paggamit ng MuntingMasid logging library para sa setup na may dalawang Arduino Uno boards na nagpapalitan ng log data sa pamamagitan ng USB at SoftwareSerial.*

## Layunin

Ipakita ang paggamit ng dalawang `MuntingMasid` logger:
- Isang logger (`mainLog`) na tumatakbo sa pangunahing `Serial`.
- Isang logger (`altLog`) na tumatakbo sa `SoftwareSerial`.

Ipinapasa ng `uno1` ang mga log message sa `uno2` gamit ang serial wire. Si `uno2` ay gumaganap bilang simpleng serial echo monitor.

---

## Pangkalahatang Kaayusan

### Matisil (Hardware)
- **Dalawang Arduino Uno boards**.
- **Serial wiring**:
  - `uno1 TX (pin 11)` → `uno2 RX`
  - `GND` ng parehong boards dapat naka-konekta.
- **USB connection**:
  - `uno1` → PC sa `COM5`
  - `uno2` → PC sa `COM3`=

### Lohisil (Software)

* `platformio.ini` → Ang PlatformIO configuration file [dito](platform.ini)
* `uno1_main.cpp` → Ang main file ng pangunahing board [dito](uno1_main.cpp). Nandito ang nagsisilbing tagapagpadala.
* `uno2_main.cpp` → Ang main file ng sekundaryang board [dito](uno2_main.cpp). Ito ang nagsisilbing tagapagtanggap.

---

## Gamit ang PlatformIO: Pag-upload at Serial Monitoring

🛠️ *Mga utos para sa sabayang pag-develop at pagmamanman ng dalawang Arduino Uno boards gamit ang PlatformIO sa loob ng VSCode.*

### Pag-upload ng Tatagsil (Firmware)
Gamitin ang mga sumusunod na utos para sa pag-upload sa bawat board:

* Para sa `uno1` (tagapagpadala):

    ``` bash
    pio run -e uno1 -t upload
    ```

* Para sa `uno2` (tagapagsagap):

    ``` bash
    pio run -e uno2 -t upload
    ```

### Serial Monitoring

Buksan ang dalawang terminal tabs sa VSCode para masubaybayan ang dalawang output nang sabay:

* Monitor para sa `uno1` **(COM5)**:

    ``` bash
    pio device monitor -e uno1
    ```

* Monitor para sa `uno2` **(COM3)**:

    ``` bash
    pio device monitor -e uno2
    ```

💡 *Makatutulong ito upang masubaybayan kung paano tumutugon ang `uno2` sa mga log message mula sa `uno1`, sa parehong oras na nakikita rin ang sariling logs ng `uno1` sa Serial Monitor.*

---

## Resulta

Makikita mo sa dalawang Serial Monitor (COM5 at COM3) ang magkaibang logging output.

Nakakatulong ito sa debugging ng inter-device communication, tulad ng sa mga subsystems ng Proyektong LundayHangin.
