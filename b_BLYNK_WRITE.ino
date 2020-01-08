// Processing the data from the widgets when it gets received

BLYNK_WRITE(setModeVPin)   // ON 1 = scheduled   - OFF 0 = manual(check temperature allways)
{ 
  //restoring int value
  scheduled = param.asInt();
  Serial.println();
  Serial.print("scheduled=");
  Serial.println(scheduled);
  Serial.println();
  EEPROM.write(scheduledaddress, scheduled);
  EEPROM.commit();
  yield();
}

BLYNK_WRITE(tempSetVPin)
{
  //restoring the value as it is updated on the server
  tempset = param.asFloat();
  EEPROM.write(tempsetaddress, tempset);
  EEPROM.commit();
  Serial.println("tempset updated");
  yield();
}


BLYNK_WRITE(geofenceSwitchVPin)
{
  //restoring the value as it is updated on the server
  GPSAutoOff = param.asInt();
  if (GPSAutoOff == 1)
  {
    Serial.println("Geofence is Activated!");
    ledGPSAutoOff.on();
  }
  else
  {
    Serial.println("Geofence is Deactivated!");  
    ledGPSAutoOff.off();
  }
  yield();
  EEPROM.write(GPSAutoOffaddress, GPSAutoOff);
  EEPROM.commit();
}


BLYNK_WRITE(locationVPin)
{
  //restoring the value as it is updated on the server
  GPSTrigger = param.asInt();
  if (GPSTrigger == 1)
  {
    Serial.println("In the radius!");
    ledGPSTrigger.on();
  }
  else
  {
    Serial.println("Outside the radius!");  
    ledGPSTrigger.off();
  }
  yield();
}


BLYNK_WRITE(timeInterval1VPin) {    // time interval setup for Monday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime1 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour1 = t.getStartHour();  
    StartMinute1 = t.getStartMinute();
  }
  else
  {
    StartTime1 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime1 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour1 = t.getStopHour();  
    StopMinute1 = t.getStopMinute(); 
  }

  else
  {
    StopTime1 = 0;
  }
  EEPROM.write(StartHour1Address, StartHour1);
  EEPROM.write(StartMinute1Address, StartMinute1);
  EEPROM.write(StopHour1Address, StopHour1);  
  EEPROM.write(StopMinute1Address, StopMinute1);   
  EEPROM.commit();
  
}

BLYNK_WRITE(timeInterval2VPin) {    // time interval setup for Tuesday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime2 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour2 = t.getStartHour();  
    StartMinute2 = t.getStartMinute();
  }
  else
  {
    StartTime2 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime2 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour2 = t.getStopHour();  
    StopMinute2 = t.getStopMinute(); 
  }

  else
  {
    StopTime2 = 0;
  }

  EEPROM.write(StartHour2Address, StartHour2);
  EEPROM.write(StartMinute2Address, StartMinute2);
  EEPROM.write(StopHour2Address, StopHour2);  
  EEPROM.write(StopMinute2Address, StopMinute2);   
  EEPROM.commit();
}

BLYNK_WRITE(timeInterval3VPin) {    // time interval setup for Wednesday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime3 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour3 = t.getStartHour();  
    StartMinute3 = t.getStartMinute();
  }
  else
  {
    StartTime3 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime3 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour3 = t.getStopHour();  
    StopMinute3 = t.getStopMinute(); 
  }

  else
  {
    StopTime3 = 0;
  }

  EEPROM.write(StartHour3Address, StartHour3);
  EEPROM.write(StartMinute3Address, StartMinute3);
  EEPROM.write(StopHour3Address, StopHour3);  
  EEPROM.write(StopMinute3Address, StopMinute3);   
  EEPROM.commit();
}

BLYNK_WRITE(timeInterval4VPin) {    // time interval setup for Thursday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime4 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour4 = t.getStartHour();  
    StartMinute4 = t.getStartMinute();
  }
  else
  {
    StartTime4 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime4 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour4 = t.getStopHour();  
    StopMinute4 = t.getStopMinute(); 
  }

  else
  {
    StopTime4 = 0;
  }
  EEPROM.write(StartHour4Address, StartHour4);
  EEPROM.write(StartMinute4Address, StartMinute4);
  EEPROM.write(StopHour4Address, StopHour4);  
  EEPROM.write(StopMinute4Address, StopMinute4);   
  EEPROM.commit();
}

BLYNK_WRITE(timeInterval5VPin) {    // time interval setup for Friday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime5 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour5 = t.getStartHour();  
    StartMinute5 = t.getStartMinute();
  }
  else
  {
    StartTime5 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime5 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour5 = t.getStopHour();  
    StopMinute5 = t.getStopMinute(); 
  }

  else
  {
    StopTime5 = 0;
  }
  
  EEPROM.write(StartHour5Address, StartHour5);
  EEPROM.write(StartMinute5Address, StartMinute5);
  EEPROM.write(StopHour5Address, StopHour5);  
  EEPROM.write(StopMinute5Address, StopMinute5);   
  EEPROM.commit();
}

BLYNK_WRITE(timeInterval6VPin) {    // time interval setup for Saturday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime6 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour6 = t.getStartHour();  
    StartMinute6 = t.getStartMinute();
  }
  else
  {
    StartTime6 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime6 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour6 = t.getStopHour();  
    StopMinute6 = t.getStopMinute(); 
  }

  else
  {
    StopTime6 = 0;
  }

  EEPROM.write(StartHour6Address, StartHour6);
  EEPROM.write(StartMinute6Address, StartMinute6);
  EEPROM.write(StopHour6Address, StopHour6);  
  EEPROM.write(StopMinute6Address, StopMinute6);   
  EEPROM.commit();
}

BLYNK_WRITE(timeInterval7VPin) {    // time interval setup for Sunday
  // Process start time
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    StartTime7 = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
    StartHour7 = t.getStartHour();  
    StartMinute7 = t.getStartMinute();
  }
  else
  {
    StartTime7 = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime7 = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute());
    StopHour7 = t.getStopHour();  
    StopMinute7 = t.getStopMinute(); 
  }

  else
  {
    StopTime7 = 0;
  }
  EEPROM.write(StartHour7Address, StartHour7);
  EEPROM.write(StartMinute7Address, StartMinute7);
  EEPROM.write(StopHour7Address, StopHour7);  
  EEPROM.write(StopMinute7Address, StopMinute7);   
  EEPROM.commit();
}

BLYNK_WRITE(referenceZoneVPin) 
{
  referenceZone = param.asInt();
  switch (referenceZone)
  {
  
      case 1: { // Item 1
        Serial.println("Local Temperature selected");
        break;
      }
      case 2: { // Item 2
        Serial.println("Multiple Rooms Mode is selected");
        break;
      }
      case 3: { // Item 3
        Serial.println("Room1 is selected");
        break;
      }
      case 4: { // Item 4
        Serial.println("Room2 is selected");
        break;
      } 
      case 5: { // Item 5
        Serial.println("Room3 is selected");
        break;
      } 
  } 
}




BLYNK_WRITE(room1Vpin)   // 
{ 
  //restoring int value
  room1Temp = param.asFloat();
  Serial.println();
  Serial.print("room1Temp= ");
  Serial.println(room1Temp);
  Serial.println();
  yield();
}

BLYNK_WRITE(room2Vpin)   // 
{ 
  //restoring int value
  room2Temp = param.asInt();
  Serial.println();
  Serial.print("room2Temp= ");
  Serial.println(room2Temp);
  Serial.println();
  yield();
}

BLYNK_WRITE(room3Vpin)   // 
{ 
  //restoring int value
  room3Temp = param.asInt();
  Serial.println();
  Serial.print("room3Temp= ");
  Serial.println(room3Temp);
  Serial.println();
  yield();
}

BLYNK_WRITE(HBroom1Vpin)   // 
{ 
  //restoring int value
  HBroom1 = param.asInt();
  Serial.println();
  Serial.print("HBroom1= ");
  Serial.println(HBroom1);
  Serial.println();
  yield();
}

BLYNK_WRITE(HBroom2Vpin)   // 
{ 
  //restoring int value
  HBroom2 = param.asInt();
  Serial.println();
  Serial.print("HBroom2= ");
  Serial.println(HBroom2);
  Serial.println();
  yield();
}

BLYNK_WRITE(HBroom3Vpin)   // 
{ 
  //restoring int value
  HBroom3 = param.asInt();
  Serial.println();
  Serial.print("HBroom2= ");
  Serial.println(HBroom3);
  Serial.println();
  yield();
}

BLYNK_WRITE(EnableLocalVpin)
{
  EnableLocal = param.asInt();
}

BLYNK_WRITE(EnableRoom1Vpin)
{
  EnableRoom1 = param.asInt();
}

BLYNK_WRITE(EnableRoom2Vpin)
{
  EnableRoom2 = param.asInt();
}

BLYNK_WRITE(EnableRoom3Vpin)
{
  EnableRoom3 = param.asInt();
}
