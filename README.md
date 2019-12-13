Warning: This is a work in progress and some of the features are not fully working or not even implemented yet.

The hardware used:
- ESP32 Dev Board
- I2C BME680 for measuring the temp,hum, pressure and air quality - can be easily replaced by the cheaper <a href = "https://www.ebay.co.uk/itm/10DOF-I2C-SPI-MPU9250-BMP280-BME280-Kompass-Barom-for-Arduino-Raspberry-Pi-UK/192137880381?ssPageName=STRK%3AMEBIDX%3AIT&var=492050506785&_trksid=p2057872.m2749.l2649"> BME280(temp,hum,pressure)</a>
- I2C MCP23017
- I2C RTC DS13017z
- SPI ST7735
- <a href ="https://www.ebay.co.uk/itm/Hot-Mini-Wireless-433Mhz-RF-Control-Remote-1527-Learning-Code-Transmitter-Module/232451380539?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649"> 433 Mhz transmitter</a>
- <a href= "https://www.ebay.co.uk/itm/DC-12V-1-Ch-433MHz-Wireless-Relay-RF-Remote-Control-Switch-Heterodyne-Receiver/292158576954?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649"> 433 Mhz Relay Module</a> + <a href = "https://www.ebay.co.uk/itm/1-2-5PCS-AC110-220V-to-DC12V-Voltage-Power-Supply-Step-Down-Converter-Module/283386093098?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649"> Power Module </a>

# Blynk-Thermostat-V2
A smarter version of a thermostat that can work and be fully programmed online or offline. It will store the required settings and inputs like temperature set, operating mode, the time and the time intervals required for scheduling in order to work offline when the connection to the server drops. It will be able to recover it when its available again. The output command for the heating device can be adjusted for the needs. I am currently using 433mhz modules from ebay for wireless transmission to the heating system and the relay for trggering it. The local time is updated from the server automatically and kept by the rtc module.

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
- Scheduling - I'm working on a new scheduling system that will allow different hour intervals for each day of the week. Heating can start 2 hours earlier before arrival, but after that, during the scheduled time it can stop the heating (if desired) when you leave the home (eg, shopping). 
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
