void HeatingLogic()
{
  if (Blynk.connected()) {
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
  else {     //not connected
    Serial.println("Not Connected. Scheduling wont work for now.");
    if (scheduled == 1){
      HeatOff();
    }
    else {
      Serial.println("It's offline, but it works on manual.");
      TempCompare();  
    }
  }
}


void TempCompare()
{
  referenceTemp = temp;
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
