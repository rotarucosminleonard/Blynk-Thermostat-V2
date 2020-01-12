void HeatingLogic()
{
    if (scheduled == 1 ){
      Serial.println("By Time");
      Serial.println();
      checkTimeInterval();
      Serial.print("interval=");
      Serial.println(interval);
      Serial.println();
      if (interval == 1 ) {
        if (GPSAutoOff == 0){
          TempCompare();  // do the relay thing if the right time comes and the temperature thing
          Serial.println("Heating was turned ON at the right time in interval");
          //ledInterval.on();  
          yield();  
        }
        else 
        { 
          if (GPSTrigger == 1) //triggering when you leave the home
          {
            TempCompare();  
            Serial.println("Thermostat is running again because you are at home!");   
            yield();
          }
          else
          {
            if (preheating == 0)
            {
              HeatOff();
              //STOPPED = 0; 
              Serial.println("Heating was turned off because it's set on scheduled, but there is nobody at home for more than 2 hours since the StartHour Begun");
              yield();               
            }
            else {
              TempCompare();  
              Serial.println("Thermostat is running again because you are at home, or its less than 2 hours since the StartHour!");   
              yield();              
            }
          }
        }
   
      } 
      else {
        HeatOff();
        //STOPPED = 0; 
        Serial.println("Heating was turned off because the interval passed");
        yield();
      }
    }
    else if (scheduled == 0) { // Not Scheduled!
      if (GPSAutoOff == 0){
        TempCompare();  
        Serial.println("Thermostat is running non stop");   
        yield();
      }
      else 
      { // GPSAutoOff is activated.When its on manual,keep heating only if you are at home
        //ledGPSAutoOff.on();
        if (GPSTrigger == 1) //triggering when you leave the home
        {
          //ledGPSTrigger.on();
          TempCompare();  
          Serial.println("Thermostat is running again because you are at home!");   
          yield();
        }
        else
        {
          //ledGPSTrigger.off();
          HeatOff();
          //STOPPED = 0; 
          Serial.println("Heating was turned off because it's set on manual, but there is nobody at home");
          yield(); 
        }
      }  
    }    
}


void ReferenceHeatingZone()
{
  Serial.println("referenceZone = " + String(referenceZone));
  referenceTemp = temp; // Local temperature as refference by default.It will be overwritten later on the right conditions
  switch (referenceZone)
  {
      case 1: { // Item 1
        Serial.println("Local Temperature selected");
        referenceTemp = temp;
        break;
      }
      case 2: { // Item 2
        Serial.println("Multiple Rooms Mode is selected");
        boolean enabledRoomFound = false;   
        if (!EnableLocal && !EnableRoom1 && !EnableRoom2 && !EnableRoom3)
        {
          Serial.println("No rooms enabled.");
          enabledRoomFound = false;
          //referenceTemp = temp;
          //EnableLocal = 1;
        }
        else // At lest one room is enabled
        {
          if (EnableLocal == true){
            Serial.println("Local is Enabled");
            if (temp <= referenceTemp){
              referenceTemp = temp; 
              Serial.println("Local referenceTemp= " + String(referenceTemp)); 
              enabledRoomFound = true;
            }
          }
          if (EnableRoom1 == true){
            Serial.println("Room 1 is enabled");
            if (room1Status == true)
            {
              if (room1Temp <= referenceTemp){
              referenceTemp = room1Temp; 
              Serial.println("Room1 referenceTemp= " + String(room1Temp));
              enabledRoomFound = true;
              }        
            }     
          }
          if (EnableRoom2 == true){
            Serial.println("Room 2 is enabled");
            if (room2Status == true)
            {
              if (room2Temp <= referenceTemp){
              referenceTemp = room2Temp;
              Serial.println("Room2 referenceTemp= " + String(room2Temp));
              enabledRoomFound = true;
              }        
            } 
          }
          if (EnableRoom3 == true){
            Serial.println("Room 3 is enabled");
            if (room3Status == true)
            {
              if (room3Temp <= referenceTemp){
              referenceTemp = room3Temp;
              Serial.println("Room3 referenceTemp= " + String(room3Temp));
              enabledRoomFound = true;
              }        
            } 
          }
        }
        if (enabledRoomFound == false)
        { 
          //Failsafe for the situation when Local is DISABLED and no other remote Room sensors are available
          referenceTemp = temp;
          EnableLocal = 1;
          Serial.println("No remote sensors are enabled or online! Switch to Local");
        }
        break;  
      }
      case 3: { // Item 3
        Serial.println("Room1 is selected");
        if (room1Status == 1)
        {
          referenceTemp = room1Temp;          
        }
        else {
          referenceTemp = temp;
        }
        break;
      }
      case 4: { // Item 4
        Serial.println("Room2 is selected");
        if (room2Status == 1)
        {
          referenceTemp = room2Temp;          
        }
        else {
          referenceTemp = temp;
        }
        break;
      } 
      case 5: { // Item 5
        Serial.println("Room3 is selected");
        if (room3Status == 1)
        {
          referenceTemp = room3Temp;          
        }
        else {
          referenceTemp = temp;
        }
        break;
      } 
  } 
  
}

void TempCompare()
{
  ReferenceHeatingZone();
  //referenceTemp = temp;
  bottomTreshold = tempset-tempDrop;
  topThreshold = tempset-tempOvershoot;
  Serial.println("referenceTemp= "+ String(referenceTemp));  
  Serial.println("bottomTreshold= "+ String(bottomTreshold));
  Serial.println("topTreshold= "+ String(bottomTreshold));

  if (referenceTemp <= bottomTreshold){
    HeatOn(); 
    Serial.println("Heating is running!");
  }
  else if (referenceTemp >= topThreshold){
    HeatOff();
    Serial.println("Heating is Stopped!");
  }
}


void HeatOn() 
{
  digitalWrite(RELAYoNpin, LOW);
  delay(50);
  digitalWrite(RELAYoNpin, HIGH);
  delay(100);
  digitalWrite(RELAYoNpin, LOW);
  delay(50);
  digitalWrite(RELAYoNpin, HIGH);
  mcp.digitalWrite(LEDpin, LOW);
  
  if (Blynk.connected())
  {
    ledHeatingStatus.on();    
  }
  Serial.println("heatOn"); 
  HEATING = 1;
  yield();
}

void HeatOff() 
{
  //digitalWrite(RELAYpin, HIGH);
  digitalWrite(RELAYoFFpin, LOW);
  delay(50);
  digitalWrite(RELAYoFFpin, HIGH);
  delay(100);
  digitalWrite(RELAYoFFpin, LOW);
  delay(50);
  digitalWrite(RELAYoFFpin, HIGH);
  mcp.digitalWrite(LEDpin, HIGH);
  if (Blynk.connected())
  {
    ledHeatingStatus.off();
  }
  Serial.println("heatOff"); 
  HEATING = 0;
  yield();
}
