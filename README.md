# Mazokchist

*Hello Everyone!*

What is Mazokchist you might ask? it is a small environmental monitor built around the Seeed XIAO ESP32-C6. A BME680
sensor measures temperature, humidity, pressure and gas resistance and sends
the readings over I2C to the XIAO, which displays them on a Waveshare 2.9"
e-Paper screen.

## How it works

- **BME680** — reads temperature, humidity, pressure and gas resistance, and
  sends the data to the XIAO over I2C.
- **XIAO ESP32-C6** — reads the sensor over I2C and drives the display over SPI.
- **Waveshare 2.9" e-Paper** — shows the latest readings. The screen refreshes
  once a minute.

## Bill of Materials
Electronics and mounting hardware only — PCB fabrication, wires, etc. not included.

Qty	Part	Notes
1	Seeed XIAO ESP32-C6	Main microcontroller
1	BME680 breakout module	Temp / humidity / pressure / gas sensor, I2C; soldered directly to PCB traces
1	Waveshare 2.9" e-Paper display (V2, SSD1680)	128x296, monochrome
1	JST PH 2.0mm, 8-pin, SMT header	On-board connector (J1) for the e-paper cable
1	JST PH 2.0mm, 8-pin cable/plug	Connects the e-paper display to the header above

Screws / mounting hardware

Qty	Part	Notes
4	M3 x 6mm screws	For mounting holes H1–H4
4	M3 standoffs	Optional, to space the PCB off a case or base
4	M3 nuts	Only needed if not using threaded standoffs

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
