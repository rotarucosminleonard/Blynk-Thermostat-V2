Warning: This is a work in progress and some of the features are not fully working or not even implemented yet.

The hardware used:
- ESP32 Dev Board
- I2C BME680 for measuring the temp,hum, pressure and air quality - can be easily replaced by the cheaper BME280(temp,hum,pressure)
- I2C MCP23017
- I2C RTC DS13017z
- SPI ST7735
- 433 Mhz transmitter 
- 433 Mhz Relay Module

# Blynk-Thermostat-V2
A smarter version of a thermostat that can work and be fully programmed online or offline. It will store the required settings and inputs like temperature set, operating mode, the time and the time intervals required for scheduling in order to work offline when the connection to the server drops. It will be able to recover it when its available again. The output command for the heating device can be adjusted for the needs. I am currently using 433mhz modules from ebay for wireless transmission. The local time is updated from the server automatically.

About the project:
+ The ESP32 works using the Blynk Platform and it displays the data on a LCD colour display (ST7735)  using the UCGLIB library. 
+ The IO pins are extended using the I2c MCP23017 giving the chance to add enough buttons and covering any future hardware improvements. 
+ The offline time kept by an external I2C RTC DS13017z using a library that does not conflict with the Online RTC used by Blynk

Working:
- Heating logic
- Storing some settings
- Timekeeping
- Connection management
- Geofence
- Wifi Signal
- Local temperature as a refference

Not working yet:
- Scheduling - I'm working on a new scheduling system that will allow different hour intervals for each day of the week.
- No hardware menu implemented at all
- Multiple temperature inputs from different sensors


ESP32 (install board)- https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

Libraries required:
- Blynk: http://help.blynk.cc/en/articles/512105-how-to-install-blynk-library-for-arduino-ide
- Ucglib: https://github.com/olikraus/ucglib
- Adafruit Unified Sensor: https://github.com/adafruit/Adafruit_Sensor
- Adafruit BME680: https://github.com/adafruit/Adafruit_BME680 ( also recommended BME280) 
- Adafruit MCp23017: https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
- Arduino Time Library: https://github.com/PaulStoffregen/Time
- Grove - RTC DS1307 : https://github.com/Seeed-Studio/RTC_DS1307
