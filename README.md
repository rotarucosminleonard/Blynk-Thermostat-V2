# Blynk-Thermostat-V2
A smarter version of a thermostat that can work and be fully programmed online or offline.

The hardware used:
- ESP32 Dev Board
- I2C BME680
- I2C MCP23017
- I2C RTC DS13017z
- SPI ST7735
- 433 Mhz transmitter 
- 433 Mhz Relay Module

+ The ESP32 works using the Blynk Platform and it displays the data on ST7735 using the UCGLIB. 
+ The IO pins are extended using the I2c MCP23017 giving the chance to add enough buttons. It uses the Adafruit Library: https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
+ The offline time kept by an external I2C RTC DS13017z using a library that does not conflict with the Online RTC used by Blynk: https://github.com/Seeed-Studio/RTC_DS1307

ESP32 (install board)- https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

Libraries required:
- Blynk: http://help.blynk.cc/en/articles/512105-how-to-install-blynk-library-for-arduino-ide
- Ucglib: https://github.com/olikraus/ucglib
- Adafruit Unified Sensor: https://github.com/adafruit/Adafruit_Sensor
- Adafruit BME680 - https://github.com/adafruit/Adafruit_BME680 ( also recommended BME280) 
- Adafruit MCp23017 - https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
