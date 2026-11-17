# qmk-config-cygnus-he

QMK configuration for the **Cygnus** keyboard with **magnetic Hall effect switches**.

---

## TODO
- [ ] Add detailed explanation of working
- [ ] Add wiring/build guide

---

## How to use

1. Clone the original [QMK Firmware repository](https://github.com/qmk/qmk_firmware)
2. Copy the `cygnus_he` folder into `qmk/keyboards/`
3. Build the firmware (for example):
   ```bash
   make cygnus_he:default
   ```
4. Flash the generated .bin (or .uf2) file to your board using bootloader mode
_(bootloader entry method may vary depending on your board)_
