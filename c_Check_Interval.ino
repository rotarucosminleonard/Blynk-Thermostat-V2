void checkInterval()
{
    Serial.println();
    Serial.println("Printing the time before checking the itnerval:");
    Serial.println(String(Hour) + ":" + String(Minute) + ":" + String(second()));
    Serial.println();
    
    //String currentDate = String(day()) + " " + month() + " " + year();
    //Interval = String( String(StartHour) + ":" + String(StartMinute) + " - " + String(StopHour) + ":" + String(StopMinute));
//    Serial.print("Current time: " + String(currentTime));
//    Serial.println();
  
  /*
  *23:10 - 23:40
  *2:00 - 2:40
  *2:50 - 2:20
  
  22:10 - 2:00
  10:10 - 2:00
  3:00 - 1:00 
  
  *10:10 - 12:10
  *10:10 - 22:10
    
  */

  // 23:10 - 23:40 && 2:00 - 2:40
  if (Hour == StartHour && StartHour == StopHour && StartMinute < StopMinute) // Less than 1H
  {
    if (Minute >= StartMinute && Minute < StopMinute)
    {
      interval = 1;
      Serial.println("100");
    }
    else
    {
      interval = 0;
      Serial.println("101");
    }
  }
  
  
  // 12:50 - 12:10  12:11
  if (Hour == StartHour && StartHour == StopHour && StartMinute > StopMinute) // 24H - some Minutes
  {
    if (Hour != StartHour)
    {
      interval = 1;
      Serial.println("102");
    }
    else if (Hour == StartHour)
    {
      if (Minute < StartMinute && Minute > StopMinute) 
      {
        interval = 1;
        Serial.println("103");
      }
      else 
      {
        interval = 0;
        Serial.println("104");
      }
    }
  }
  
  // 10:10 - 12:10 && 10:10 - 22:10 - sameday
  if (StartHour < StopHour )
  {
    if (Hour == StartHour)
    {
      if (Minute < StartMinute)
      {
        interval = 0;
        Serial.println("105");
      }
      else if (Minute >= StartMinute)
      {
        interval = 1;
        Serial.println("106");
      }
    }
    
    if (Hour == StopHour)
    {
      if (Minute > StopMinute)
      {
        interval = 0;
        Serial.println("107");
      }
      else if (Minute <= StopMinute)
      {
        interval = 1;
        Serial.println("108");
      }
    }
    
    if (Hour > StartHour && Hour < StopHour)
    {
      interval = 1;
      Serial.println("109");
    }
  }
  
  
  // 22:10 - 2:00 && 10:10 - 2:00 && 3:00 - 1:00  - next day
  if (StartHour > StopHour)
  {
    if (Hour == StartHour)
    {
      if (Minute < StartMinute)
      {
        interval = 0;
        Serial.println("110");
      }
      else if (Minute >= StartMinute)
      {
        interval = 1;
        Serial.println("111");
      }
    }
    
    if (Hour == StopHour)
    {
      if (Minute > StopMinute)
      {
        interval = 0;
        Serial.println("112");
      }
      else if (Minute <= StopMinute)
      {
        interval = 1;
        Serial.println("113");
      }
    }   
    
    //23:10 22:10 - 2:00 && 10:10 - 2:00 && 3:00 - 1:00  - next day
    if (Hour > StartHour)
    {
      interval = 1;
      Serial.println("114");
    }
    // 1:00 // 22:10 - 2:00 && 10:10 - 2:00 && 3:00 - 1:00  - next day
    else if (Hour < StartHour)
    {
      if (Hour > StopHour)
      {
        interval = 0;
        Serial.println("115");
      }
      else if (Hour < StopHour)
      {
        interval = 1;
        Serial.println("116");
      }
    }
  }
  yield();
  if(Blynk.connected()){
    if (interval == 1){
      ledInterval.on();
    }
    else {
      ledInterval.off();
    }
  }
}

BLYNK_WRITE(timeInterval1VPin) {    // time interval setup !
  TimeInputParam t(param);
  // Process start time

  if (t.hasStartTime())
  {
    StartTime = 1;
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
    StartHour = t.getStartHour();  
    StartMinute = t.getStartMinute();
  }
  else if (t.isStartSunrise())
  {
    Serial.println("Start at sunrise");
  }
  else if (t.isStartSunset())
  {
    Serial.println("Start at sunset");
  }
  else
  {
    StartTime = 0;
  }

  // Process stop time

  if (t.hasStopTime())
  {
    StopTime = 1;
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute() + ":" +
                   t.getStopSecond());
    StopHour = t.getStopHour();  
    StopMinute = t.getStopMinute(); 
  }
  else if (t.isStopSunrise())
  {
    Serial.println("Stop at sunrise");
  }
  else if (t.isStopSunset())
  {
    Serial.println("Stop at sunset");
  }
  else
  {
    StopTime = 0;
  }

  // Process timezone
  // Timezone is already added to start/stop time
//
//  Serial.println(String("Time zone: ") + t.getTZ());
//
//  // Get timezone offset (in seconds)
//  Serial.println(String("Time zone offset: ") + t.getTZ_Offset());

  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)

  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      //Serial.println(String("Day ") + i + " is selected");
    }
      if (i == 1 && t.isWeekdaySelected(i) )
      {
        Mo = 1;
      }
      else if (i == 1 && !t.isWeekdaySelected(i) ){
        Mo = 0;
      }
      if (i == 2 && t.isWeekdaySelected(i))
      {
        Tu = 1;
      }
      else if (i == 2 && !t.isWeekdaySelected(i)){
        Tu = 0;
      }
      if (i == 3 && t.isWeekdaySelected(i))
      {
        We = 1;
      }
      else if (i == 3 && !t.isWeekdaySelected(i)){
        We = 0;
      }
      if (i == 4 && t.isWeekdaySelected(i))
      {
        Th = 1;
      }
      else if (i == 4 && !t.isWeekdaySelected(i)){
        Th = 0;
      }
      if (i == 5 && t.isWeekdaySelected(i))
      {
        Fr = 1;
      }
      else if(i == 5 && !t.isWeekdaySelected(i)){
        Fr = 0;
      }
      if (i == 6 && t.isWeekdaySelected(i))
      {
        Sa = 1;
      }
      else if(i == 6 && !t.isWeekdaySelected(i)){
        Sa = 0;
      }
      if (i == 7 && t.isWeekdaySelected(i))
      {
        Su = 1;
      }
      else if (i == 7 && !t.isWeekdaySelected(i)){
        Su = 0;
      }
  }
  // If there is no scheduled day selected, then all are scheduled because days scheduling can be deactivate through the widget
//  Serial.println(String(Mo) + " , " + String(Tu) + " , " + String(We) + " , " + String(Th) + " , " + String(Fr) + " , " + String(Sa) + " , " + String(Su) );
//  Serial.println();
}
