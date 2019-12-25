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
  //tempToUse();
  referenceTemp = temp;
  tempset2 = tempset-tempdrop;
  Serial.println("tempset2= "+ String(tempset2));
  Serial.println("referenceTemp= "+ String(referenceTemp));    
  // starding from
  // HEATING = 0
  // STOPPED = 0
            
  if (HEATING == 0 && STOPPED == 0){
    if (tempset2 > referenceTemp){
      HeatOn();
      //Blynk.setProperty(V5, "color", "purple");    
      Serial.println("Heating Just Started!");        
    }
    else {
      HeatOff();
      STOPPED = 1;
      Serial.println("Keep it OFF!");
    }
  }
          
  else if (HEATING == 1){
    if (referenceTemp > tempset){ // 
      HeatOff();
      STOPPED = 1;
      //Blynk.setProperty(V5, "color", "green");
      Serial.println("Temp was reached.Wait till it drops by 1C");
    }
    else {
      HeatOn();
      //STOPPED = 0; 
      Blynk.setProperty(V5, "color", "red");  
      Serial.println("Heating...");         
    }
  }    
  else if (STOPPED == 1){         
    if (referenceTemp < tempset2){ // start heating again only if the temp dropped by one deg
      HeatOn();
      //Blynk.setProperty(V5, "color", "red");                             
      Serial.println("Temp dropped by one deg.Start heating again");
    }
    else {
      HeatOff();
      Serial.println("Keep it off till it drops by one deg");              
    }
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
