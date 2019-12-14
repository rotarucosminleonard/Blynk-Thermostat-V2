// Processing the data from the widgets when it gets received

BLYNK_WRITE(setModeVPin)   // ON 1 = scheduled   - OFF 0 = manual(check temperature allways)
{ 
  //restoring int value
  scheduled = param.asInt();
  Serial.println();
  Serial.print("scheduled=");
  Serial.println(scheduled);
  Serial.println();
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
}
