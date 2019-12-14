/*
  A smarter version of a thermostat that can work and be fully programmed online or offline. It will store the required 
settings and inputs like temperature set, operating mode, the time and the time intervals required for scheduling
in order to work offline when the connection to the server drops. It will be able to recover it when its available again. 
The output command for the heating device can be adjusted for the needs. I am currently using 433mhz modules from ebay 
for wireless transmission to the heating system and the relay for trggering it. The local time is updated from the server 
automatically and kept by the rtc module.
 */


#define NAMEandVERSION "ESP32_Thermostat V2.75"
#include "config.h" // SSID,PASS, AUTH,serveraddr

//#define BLYNK_DEBUG

#define BLYNK_TIMEOUT_MS  500  // must be BEFORE BlynkSimpleEsp8266.h doesn't work !!!
#define BLYNK_HEARTBEAT   17   // must be BEFORE BlynkSimpleEsp8266.h works OK as 17s
#define BLYNK_PRINT Serial    

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "Ucglib.h"
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#include "Adafruit_MCP23017.h"
#include <WidgetRTC.h>
#include <EEPROM.h>
//  // each byte of the EEPROM can only hold a value from 0 to 255.

#include "DS1307.h"
DS1307 OfflineRTC;//define a object of DS1307 class

#include <TimeLib.h>
BlynkTimer timer;
WidgetRTC   OnlineRTC;
WidgetTerminal terminal(V1);



#define SDA 21
#define SCL 22           /// I2C pins
Adafruit_MCP23017 mcp;

//Adafruit_BMP280 bmp;
Adafruit_BME680 bme; // I2C

#define SEALEVELPRESSURE_HPA (1013.25)

Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 25, /*cs=*/ 26, /*reset=*/ 27); 

// Hardware SPI pins used by the display:
// LED            = 3.3v
// SCK            = 18
// SDA = MOSI     = 23
// A0             = 25
// Reset          = 27
// CS             = 26

// Hardware I2C pins used by the rest of the devices:
// SCL = 22
// SDA = 21

// Pins from the IO extender
#define LED_PIN 2           
#define LEDpin 6
#define LEFTpin 4
bool prevLeftState;
#define UPpin 3
bool prevUpState;
#define DOWNpin 2
bool prevDownState;
#define RIGHTpin 1
bool prevRightState;
#define OKpin 0
bool prevOkState;
#define CANCELpin 5
bool prevCancelState;

#define RELAYoNpin 33
#define RELAYoFFpin 13

bool theLEDState;
bool leftKey;
bool upKey;
bool downKey;
bool rightKey;
bool okKey;
bool cancelKey;

// These should be generic to all devices, except the air quality 
#define onlineStatusVPin     V0   // used for hardware monitoring 
#define heartbeatVPin        V1   // used for hardware monitoring
#define wifiSignalVPin       V2   // percentage of wifi strenght
#define tempVPin             V3   // realtime temperature value
#define humVPin              V4   // realtime humidity value
#define pressureVPin         V5   // realtime pressure value
#define gassVPin             V6   // realtime gass readings value
#define airQuality           V7   // placeholder for air quality 

// LED widgets used for bynary monitoring
WidgetLED  ledHeatingStatus(V30);
WidgetLED       ledInterval(V31);
WidgetLED     ledGPSAutoOff(V32);
WidgetLED     ledGPSTrigger(V33);

// These are specific to this thermostat

#define tempSetVPin         V10
#define timeInterval1VPin   V21 // Moday
#define timeInterval2VPin   V22 // Tuesday
#define timeInterval3VPin   V23 // Wednesday
#define timeInterval4VPin   V24 // Thursday
#define timeInterval5VPin   V25 // Friday
#define timeInterval6VPin   V26 // Saturday
#define timeInterval7VPin   V27 // Sunday


#define tempSetControlVPin  V14
#define setModeVPin         V15 // manual vs scheduled interval
#define referenceTempVPin   V16
#define referenceZoneVPin   V17 // temperature from which room
#define geofenceSwitchVPin  V18 // geofence should work on manual or int
#define locationVPin        V20 // Use the mirror instead. It gets received any time it is requested.


// BME reading variables
short int delayaftergas = 0;
short int readings = 0;
bool timetomeasureGas = 0;
bool gasjustmeasured = 0;

int counter = 0;
signed short int rssi = 0;
signed short int signalQuality = 0;

// menu
int position;
bool menu;
int value;
bool save;

bool on = 0;
bool online = 0;
bool wifi = 0;
bool server = 0;

//Widget Variables to Use
int StartHour = 0;
int StopHour = 0;
int StartMinute = 0;
int StopMinute = 0;
bool StartTime = 0;
bool StopTime = 0;

int Hour = 0;
int Minute = 0;

//Monday Widged Variables to use
int StartHour1 = 0;
int StopHour1 = 0;
int StartMinute1 = 0;
int StopMinute1 = 0;
bool StartTime1 = 0;
bool StopTime1 = 0;

//Tuesday Widged Variables to use
int StartHour2 = 0;
int StopHour2 = 0;
int StartMinute2 = 0;
int StopMinute2 = 0;
bool StartTime2 = 0;
bool StopTime2 = 0;

//Wednesday  Widged Variables to use
int StartHour3 = 0;
int StopHour3 = 0;
int StartMinute3 = 0;
int StopMinute3 = 0;
bool StartTime3 = 0;
bool StopTime3 = 0;

//Thursday Widged Variables to use
int StartHour4 = 0;
int StopHour4 = 0;
int StartMinute4 = 0;
int StopMinute4 = 0;
bool StartTime4 = 0;
bool StopTime4 = 0;


//Friday Widged Variables to use
int StartHour5 = 0;
int StopHour5 = 0;
int StartMinute5 = 0;
int StopMinute5 = 0;
bool StartTime5 = 0;
bool StopTime5 = 0;

//Saturday Widged Variables to use
int StartHour6 = 0;
int StopHour6 = 0;
int StartMinute6 = 0;
int StopMinute6 = 0;
bool StartTime6 = 0;
bool StopTime6 = 0;

//Sunday Widged Variables to use
int StartHour7 = 0;
int StopHour7 = 0;
int StartMinute7 = 0;
int StopMinute7 = 0;
bool StartTime7 = 0;
bool StopTime7 = 0;

bool Mo = 0;
bool Tu = 0;
bool We = 0;
bool Th = 0;
bool Fr = 0;
bool Sa = 0;
bool Su = 0;


bool onlinetimechk; // wont let the time synk unless the online time got updated

float temp = 0;
float h = 0;
float p = 0;
float g = 0;
float a = 0;

bool scheduled;
bool GPSTrigger;
bool GPSAutoOff;

float tempset = 0.0; // realtime temperature
float tempdrop = 0.6;    // temperature difference required to start the heating again
float tempset2; // temperature at the moment of starging the heating
float referenceTemp = 0;

// EEPROM adreses
int tempsetaddress = 0;
int scheduledaddress = 1;
int GPSAutoOffaddress = 2;

bool HEATING;
bool STOPPED;
bool interval;


void setup() {
  pinMode(RELAYoNpin, OUTPUT); 
  pinMode(RELAYoFFpin, OUTPUT); 
  digitalWrite(RELAYoNpin, HIGH);
  digitalWrite(RELAYoFFpin, HIGH);
  Serial.begin(115200);
  Serial.println();

  EEPROM.begin(512);
  tempset = EEPROM.read(tempsetaddress);
  scheduled = EEPROM.read(scheduledaddress);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  //ucg.undoRotate(); break;
  ucg.setRotate90();  //landscape,pins on the left
  //ucg.setRotate180(); break;
  //ucg.setRotate270(); break;

  WiFi.setHostname(NAMEandVERSION);
  WiFi.mode(WIFI_STA);
  WiFi.config(arduino_ip, gateway_ip, subnet_mask);
  //Blynk.config(auth, IPAddress(192,168,0,3), port);  // I am using the local Server
  Blynk.config(auth, serveraddr, port);  // I am using the local Server

  Wire.begin(SDA,SCL);
  mcp.begin();      // use default address 0
  //mcp.begin(0x20);      // use custom address
  
  OfflineRTC.begin();
//  OfflineRTC.fillByYMD(2013,1,19);//Jan 19,2013
//  OfflineRTC.fillByHMS(15,28,30);//15:28 30"
//  OfflineRTC.fillDayOfWeek(SAT);//Saturday
//  OfflineRTC.setTime();//write time to the RTC chip


  // Only used once, then disabled - Setting the clock
//   rtc.set(0, 40, 18, 2, 6, 8, 19);
  // RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  
  pinMode(LED_PIN, OUTPUT);
  mcp.pinMode(LEDpin, OUTPUT);
  mcp.pinMode(LEFTpin, INPUT);
  mcp.pinMode(UPpin, INPUT);
  mcp.pinMode(DOWNpin, INPUT);
  mcp.pinMode(RIGHTpin, INPUT);
  mcp.pinMode(OKpin, INPUT);
  mcp.pinMode(CANCELpin, INPUT);
  /* Default settings from datasheet. */
//  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
//                  Adafruit_BMP280::SAMPLING_X4,     /* Temp. oversampling */
//                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
//                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
//                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
//                  
//  Serial.println(F("BMP280 test"));
//  if (!bmp.begin(0x76)) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
//    //while (1);
//  }

  Serial.println(F("BME680 async test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_4X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  ReadBME680(); 
  CheckConnection();// It needs to run first to initiate the connection.Same function works for checking the connection!
  timer.setInterval(22000L, CheckConnection); 
  //  timer.setInterval(1000L, myTimerEvent);    
  timer.setInterval(10100L, ReadBME680);
  timer.setInterval(5000L, BlinkTheLed);  
  timer.setInterval(4000L, mainDisplay);     
  timer.setInterval(100000L,  OfflineTime);
  timer.setInterval(100000L,  OnlineTime);
  timer.setInterval(8000L, PeriodicSync);
  timer.setInterval(20000L, HeatingLogic);
}

void loop() {
  if(Blynk.connected()){
    Blynk.run();
  }
  timer.run();
  keyboard();
}


BLYNK_CONNECTED() {
  OnlineRTC.begin();
  Serial.println("Got connection to the server. Doing some sync...");
  Blynk.virtualWrite(tempSetVPin, tempset);// update the local tempset TO server
  //Blynk.syncVirtual(timeInterval1VPin);
  Blynk.syncVirtual(geofenceSwitchVPin);
  Blynk.syncVirtual(locationVPin);
  Blynk.syncVirtual(setModeVPin);
    // Synchronize time on connection
//  OfflineTime();
//  delay(100);
//  OfflineTime();
//  delay(100);
  OnlineTime();
  OfflineTime();
  syncTheTime();
  Blynk.syncVirtual(timeInterval1VPin);
  Blynk.syncVirtual(timeInterval2VPin);
  Blynk.syncVirtual(timeInterval3VPin);
  Blynk.syncVirtual(timeInterval4VPin);
  Blynk.syncVirtual(timeInterval5VPin);
  Blynk.syncVirtual(timeInterval6VPin);
  Blynk.syncVirtual(timeInterval7VPin);
}

void PeriodicSync()
{
  if(Blynk.connected())
  {
    Serial.println("Periodic Sync...");
    // Push to the server
    Blynk.virtualWrite(tempVPin, temp);
    Blynk.virtualWrite(humVPin, h);
    
    Blynk.virtualWrite(tempSetVPin, tempset);
    
    Blynk.virtualWrite(pressureVPin, p);
    Blynk.virtualWrite(gassVPin, g);
//    Blynk.virtualWrite(tempSetVPin, tempset); //only after the local storage in the memory
    Blynk.virtualWrite(wifiSignalVPin, signalQuality);
    Blynk.virtualWrite(referenceTempVPin, referenceTemp);// reference temperature
    // Get from the server
//    Blynk.syncVirtual(timeInterval1VPin);// scheduled interval 1
//    Blynk.syncVirtual(timeInterval2VPin);// scheduled interval 2 
//    Blynk.syncVirtual(timeInterval3VPin);// scheduled interval 3  
  }
}


void BlinkTheLed()
{
//  Serial.println("The LED");
  if (theLEDState == 1) {
    // btnState is used to avoid sequential toggles
      digitalWrite(LED_PIN, LOW);
      theLEDState = 0;
    }
  else {
    digitalWrite(LED_PIN, HIGH);
    theLEDState = 1;
  }
}


void signalStrength()
{
  if (WiFi.status() != WL_CONNECTED) { 
    Serial.println("No WiFi connection yet!");
  } 
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
  rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi); // -90 the worst ~ -30 the best
  signalQuality = ((1 - ( (-30) - float(rssi) ) / 70) * 100) ;
  Serial.print("Signal Quality: ");
  Serial.println(signalQuality);
  }  
}


void ReadBME680() 
{
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  temp = (bme.temperature);
  p = (bme.pressure / 100.0);
  h = (bme.humidity);
  g = (bme.gas_resistance / 1000.0);
  a = (bme.readAltitude(SEALEVELPRESSURE_HPA));
}
