#define NAMEandVERSION "ESP32_Thermostat.h"
/*
 Basic example of esp32 + bmp280 + ST7735 + MCP2301
 */

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

BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V1);



#define SDA 21
#define SCL 22           /// I2C pins
Adafruit_MCP23017 mcp;

//Adafruit_BMP280 bmp;
Adafruit_BME680 bme; // I2C

#define SEALEVELPRESSURE_HPA (1013.25)


// Pins from the IO extender
#define LEDpin 0
#define LEFTpin 1
bool prevLeftState;
#define UPpin 2
bool prevUpState;
#define DOWNpin 3
bool prevDownState;
#define RIGHTpin 4
bool prevRightState;
#define OKpin 5
bool prevOkState;
#define CANCELpin 6
bool prevCancelState;

#define RELAYpin 33


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
#define humVPin              V4   // realtime humifity value
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
#define timeInterval1VPin   V11
#define timeInterval2VPin   V12
#define timeInterval3VPin   V13
#define tempSetControlVPin  V14
#define setModeVPin         V15 // manual vs scheduled interval
#define referenceTempVPin   V16
#define referenceZoneVPin   V17 // temperature from which room
#define geofenceSwitchVPin  V18 // geofence should work on manual or int
#define locationVPin        V19



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

// BME reading variables
short int delayaftergas = 0;
short int readings = 0;
bool timetomeasureGas = 0;
bool gasjustmeasured = 0;



int counter = 0;
signed short int rssi = 0;
signed short int signalQuality = 0;

char ssid[]            = "SSID";
char pass[]            = "PASSWORD";
char auth[]            = "AUTH";
//char server[]          = "blynk-cloud.com";
//char server[]          = IPAddress(192,168,1,3);
unsigned int port      = 1234; //use your own port of the server

bool on = 0;
bool online = 0;
bool wifi = 0;
bool server = 0;

// If you dont want to use DHCP 
IPAddress arduino_ip ( 192,  168,   1,  56);
IPAddress dns_ip     ( 192,  168,   1,   1);
IPAddress gateway_ip ( 192,  168,   1,   1);
IPAddress subnet_mask(255, 255, 255,   0);


int StartHour = 0;
int StopHour = 0;
int StartMinute = 0;
int StopMinute = 0;
int Hour = 0;
int Minute = 0;

bool Mo = 0;
bool Tu = 0;
bool We = 0;
bool Th = 0;
bool Fr = 0;
bool Sa = 0;
bool Su = 0;


bool StartTime = 0;
bool StopTime = 0;

float t = 0;
float h = 0;
float p = 0;
float g = 0;
float a = 0;

bool scheduled;
bool GPSTrigger;
bool GPSAutoOff;

float tempset = 0.0; // 
float tempdrop = 0;
float tempset2;
int tempsetaddress = 0;
int scheduledaddress = 1;
float referenceTemp = 0;

bool HEATING;
bool STOPPED;
bool interval;


void setup() {
  pinMode(RELAYpin, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(115200);
  Serial.println();

  rtc.begin();
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
  Blynk.config(auth, IPAddress(192,168,1,3), port);  // I am using the local Server

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

  CheckConnection();// It needs to run first to initiate the connection.Same function works for checking the connection!
  timer.setInterval(22000L, CheckConnection); 
  //  timer.setInterval(1000L, myTimerEvent);    
  timer.setInterval(20000L, ReadBME680);
  timer.setInterval(5000L, BlinkTheLed);  
  timer.setInterval(4000L, mainDisplay);     
  timer.setInterval(5000L,  OfflineTime);
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
  // Synchronize time on connection
  rtc.begin();
  delay(100);
  OnlineTime();
  delay(100);
  OnlineTime();
  syncTheTime();
  Blynk.virtualWrite(tempSetVPin, tempset);// update the local tempset TO server
  Blynk.syncVirtual(timeInterval1VPin);
  Blynk.syncVirtual(geofenceSwitchVPin);
  Blynk.syncVirtual(locationVPin);
  Blynk.syncVirtual(setModeVPin);
}

void PeriodicSync()
{
  if(Blynk.connected())
  {
    // Push to the server
    Blynk.virtualWrite(tempVPin, t);
    Blynk.virtualWrite(humVPin, h);
    Blynk.virtualWrite(pressureVPin, p);
    Blynk.virtualWrite(gassVPin, g);
//    Blynk.virtualWrite(tempSetVPin, tempset); //only after the local storage in the memory
    Blynk.virtualWrite(wifiSignalVPin, signalQuality);
    Blynk.virtualWrite(referenceTempVPin, referenceTemp);// reference temperature
    // Get from the server
    Blynk.syncVirtual(timeInterval1VPin);// scheduled interval 1
    Blynk.syncVirtual(timeInterval2VPin);// scheduled interval 2 
    Blynk.syncVirtual(timeInterval3VPin);// scheduled interval 3  
  }
}


void BlinkTheLed()
{
  Serial.println("The LED");
  if (theLEDState == 1) {
    // btnState is used to avoid sequential toggles
      mcp.digitalWrite(LEDpin, HIGH);
      theLEDState = 0;
    }
  else {
    mcp.digitalWrite(LEDpin, LOW);
    theLEDState = 1;
  }
}


void signalStrength()
{
  if (WiFi.status() != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
  } 
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
  rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi); // -90 the worst ~ -30 the best
  signalQuality = ((1 - ( (-30) - float(rssi) ) / 70) * 100) ;
  Serial.print("Signall Quality: ");
  Serial.println(signalQuality);
  }  
}


void ReadBME680() 
{
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  t = (bme.temperature);
  p = (bme.pressure / 100.0);
  h = (bme.humidity);
  g = (bme.gas_resistance / 1000.0);
  p = (bme.readAltitude(SEALEVELPRESSURE_HPA));
}
