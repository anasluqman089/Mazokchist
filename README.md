# Mazokchist

*Hello Everyone!*

What is Mazokchist you might ask? it is a small environmental monitor built around the Seeed XIAO ESP32-C6. A BME680
sensor measures temperature, humidity, pressure and gas resistance and sends
the readings over I2C to the XIAO, which displays them on a Waveshare 2.9"
e-Paper screen.

Why the name is Mazokchist? It is just a msde up name no need to know the meaning.

## How it works

- **BME680** — reads temperature, humidity, pressure and gas resistance, and
  sends the data to the XIAO over I2C.
- **XIAO ESP32-C6** — reads the sensor over I2C and drives the display over SPI.
- **Waveshare 2.9" e-Paper** — shows the latest readings. The screen refreshes
  once a minute.

## Bill of Materials

| Qty | Component                                    | Category    | Price (USD) | Buy Link                                                                                              | Notes                                                             |
| --: | -------------------------------------------- | ----------- | ----------: | ----------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
|   1 | Seeed XIAO ESP32-C6                          | Electronics |       $5.20 | [Seeed Studio](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html)                     | MCU |
|   1 | BME680 Breakout Module                       | Electronics |      $13.99 | [Amazon](https://www.amazon.com/HiLetgo-Temperature-Precision-Environmental-Monitoring/dp/B0CDWXZNY7) | Enviromental Sensor |
|   1 | Waveshare 2.9 inch E-Paper Module V2 SSD1680 | Electronics |      $21.99 | [Waveshare](https://www.waveshare.com/product/displays/e-paper/2.9inch-e-paper-module.htm)            | 296×128 monochrome e-paper display |
|   1 | JST PH 2.0mm 8-Pin SMT Header                | Electronics |      ~$1.00 | —                                                                                                     | For the PCB                                                       |
|   1 | JST PH 2.0mm 8-Pin Cable                     | Electronics |      ~$2.00 | —                                                                                                     | Connecting the PCB to the display                                 |
|   4 | M3 × 20mm Screw                              | Hardware    |      ~$2.00 | —                                                                                                     | Securing the PCB                                                  |
|   4 | M3 × 6mm Screw                               | Hardware    |      ~$2.00 | —                                                                                                     | Securing the case                                                 |
|   4 | M3 Standoff                                  | Hardware    |      ~$1.00 | —                                                                                                     | PCB/display spacers                                               |
|   1 | 3D Printed Enclosure                         | Mechanical  |      ~$5.00 | —                                                                                                     | PLA or PETG enclosure                                             |

## Estimated Total

**≈ $56.18 USD**

> Prices are approximate and may vary depending on seller, quantity, shipping, taxes, and promotions.


Check the mounting hole diameter on your PCB before ordering screws — M3 is assumed here but confirm it matches your board.

## Wiring

| BME680 | XIAO pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | D4 |
| SCL | D5 |
| SDO | GND |
| CS | 3V3 |

| e-Paper (J1) | XIAO pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| DIN | D10 |
| CLK | D8 |
| CS | D3 |
| DC | D2 |
| RST | D1 |
| BUSY | D0 |

**Notice** : BME680 SDO tied to GND sets its I2C address to 0x76. BME680 CS tied to 3V3
forces the module into I2C mode.

## How to Build

### 1. Assemble the hardware and firmware
1. Fabricate the PCB from the KiCad project (or wire the parts manually on protoboard using the wiring table above).
2. Solder the XIAO ESP32-C6, the BME680 module (directly onto its PCB pads — no cable needed), and the JST PH 2.0mm 8-pin SMT header onto the board.
3. Connect the Waveshare 2.9" e-Paper display to the JST PH header using the JST PH 2.0mm cable.
4. Mount the board using the 4 mounting holes, M3 screws, standoffs and nuts.
5. Use Arduino IDE and download all the libraries
6. Upload the code
7. *Power it on!*
