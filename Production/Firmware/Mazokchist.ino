// Library

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

// Pin
#define PIN_BUSY  D0
#define PIN_RST   D1
#define PIN_DC    D2
#define PIN_CS    D3
#define PIN_SDA   D4
#define PIN_SCL   D5
#define PIN_SCK   D8
#define PIN_MISO  D9   
#define PIN_MOSI  D10

// BME680 I2C address: SDO is tied to GND on this board so the address is 0x76
#define BME680_ADDR_PRIMARY   0x76
#define BME680_ADDR_SECONDARY 0x77

// Display
// Waveshare 2.9" V2 (SSD1680, 128x296):
GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> display(
    GxEPD2_290_T94_V2(PIN_CS, PIN_DC, PIN_RST, PIN_BUSY));

// Sensor
Adafruit_BME680 bme;

// Keep this fairly long
const unsigned long UPDATE_INTERVAL_MS = 60000UL; // 60 seconds
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  delay(200);

  // I2C bus for the BME680
  Wire.begin(PIN_SDA, PIN_SCL);

  // SPI bus for the e-paper (remap ESP32 hardware SPI pins)
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);

  // Init BME680, trying both common I2C addresses
  if (!bme.begin(BME680_ADDR_PRIMARY) && !bme.begin(BME680_ADDR_SECONDARY)) {
    Serial.println("BME680 not found - check wiring/I2C address!");
    while (true) delay(1000);
  }

  // Recommended oversampling / filter settings (from Adafruit examples)
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320 degC for 150 ms

  // Init e-paper
  display.init(115200);
  display.setRotation(1);        // landscape, 296 x 128
  display.setTextColor(GxEPD_BLACK);

  updateDisplay(); // show a first reading immediately
  lastUpdate = millis();
}

void loop() {
  if (millis() - lastUpdate >= UPDATE_INTERVAL_MS) {
    lastUpdate = millis();
    updateDisplay();
  }
}

void updateDisplay() {
  if (!bme.performReading()) {
    Serial.println("Failed to read BME680");
    return;
  }

  float temperature = bme.temperature;              // deg C
  float humidity    = bme.humidity;                 // %RH
  float pressure    = bme.pressure / 100.0F;         // hPa
  float gas         = bme.gas_resistance / 1000.0F;  // kOhm

  Serial.printf("T=%.1fC  H=%.1f%%  P=%.1fhPa  Gas=%.1fkOhm\n",
                temperature, humidity, pressure, gas);

  char tempStr[16], humStr[16], presStr[16], gasStr[16];
  snprintf(tempStr, sizeof(tempStr), "%.1f C",   temperature);
  snprintf(humStr,  sizeof(humStr),  "%.1f %%",  humidity);
  snprintf(presStr, sizeof(presStr), "%.1f hPa", pressure);
  snprintf(gasStr,  sizeof(gasStr),  "%.1f kOhm", gas);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(8, 20);
    display.print("BME680 Sensor");
    display.drawFastHLine(8, 26, display.width() - 16, GxEPD_BLACK);

    display.setFont(&FreeMonoBold9pt7b);

    display.setCursor(8, 50);
    display.print("Temp:  ");
    display.print(tempStr);

    display.setCursor(8, 70);
    display.print("Hum:   ");
    display.print(humStr);

    display.setCursor(8, 90);
    display.print("Press: ");
    display.print(presStr);

    display.setCursor(8, 110);
    display.print("Gas:   ");
    display.print(gasStr);

  } while (display.nextPage());

  display.hibernate(); // low power until next update
}