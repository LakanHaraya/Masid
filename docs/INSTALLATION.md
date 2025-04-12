# `MuntingMasid/` – *Installation, Verification, and Uninstallation*

Sa seksiyong ito, ipapakita ang mga hakbang upang matagumpay na ma-install, magamit, at ma-uninstall ang MuntingMasid library.

- [Installation](#installation)  
  - [Paraan 1: Paggamit ng PlatformIO](#paraan-2-paggamit-ng-platformio)
- [Verification of Installation](#verification-of-installation)  
- [Uninstallation](#uninstallation)  
  - [PlatformIO](#platformio)  

---
## Installation

### Paraan 1: *Paggamit ng PlatformIO*

1. **I-install ang PlatformIO**  
   Kung wala ka pang PlatformIO, i-install ito mula sa [PlatformIO website](https://platformio.org/) o gamit ang Visual Studio Code.

2. **I-clone ang Repository**  
   Buksan ang terminal at i-clone ang repository gamit ang git:
   ```bash
   git clone https://github.com/LakanHaraya/MuntingMasid.git
   ```

3. **Idagdag ang Library sa PlatformIO Project**

   - Buksan ang iyong PlatformIO project.
   - Kopyahin ang buong `MuntingMasid` folder sa `lib/` directory ng iyong PlatformIO project.

4. **Gamitin ang Library sa iyong Code**

   - Sa iyong source file (.cpp o .ino), idagdag ang sumusunod na linya:

   ``` cpp
   #include <MuntingMasid.h>
   ```

5. **I-build at I-upload ang Proyekto**
Matapos idagdag ang library, i-compile at i-upload ang iyong code sa iyong board.

## Verification of Installation
Upang matiyak na tama ang pag-install ng library, subukan ang isang halimbawa mula sa [`examples/`](../examples/) folder. Maaari mong buksan ang isa sa mga halimbawa at i-upload ito sa iyong board.

## Uninstallation
Kung nais mong tanggalin ang library mula sa *PlatformIO*, sundin ang mga sumusunod:

### *PlatformIO:*
- Tanggalin ang folder ng `MuntingMasid` mula sa `lib/` directory ng iyong proyekto.

