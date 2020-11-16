void checkTimeInterval()
{
    //Check what day it is
    
    Hour = OfflineRTC.hour;
    Minute = OfflineRTC.minute;

    switch (OfflineRTC.dayOfWeek)// Friendly printout the weekday
    {
      case MON:
        Serial.print("Using Monday scheduled interval");
        StartHour = StartHour1;
        StopHour = StopHour1;
        StartMinute = StartMinute1;
        StopMinute = StopMinute1;
        StartTime = StartTime1;
        StopTime = StopTime1;
        break;
      case TUE:
        Serial.print("Using Tuesday scheduled interval");
        StartHour = StartHour2;
        StopHour = StopHour2;
        StartMinute = StartMinute2;
        StopMinute = StopMinute2;
        StartTime = StartTime2;
        StopTime = StopTime2;   
        break;
      case WED:
        Serial.print("Using Wednesday scheduled interval");
        StartHour = StartHour3;
        StopHour = StopHour3;
        StartMinute = StartMinute3;
        StopMinute = StopMinute3;
        StartTime = StartTime3;
        StopTime = StopTime3;
        break;
      case THU:
        Serial.print("Using Thursday scheduled interval: ");
        StartHour = StartHour4;
        StopHour = StopHour4;
        StartMinute = StartMinute4;
        StopMinute = StopMinute4;
        StartTime = StartTime4;
        StopTime = StopTime4;
        break;
      case FRI:
        Serial.print("Using Friday scheduled interval: ");
        StartHour = StartHour5;
        StopHour = StopHour5;
        StartMinute = StartMinute5;
        StopMinute = StopMinute5;
        StartTime = StartTime5;
        StopTime = StopTime5;
        break;
      case SAT:
        Serial.print("Using Saturday scheduled interval: ");
        StartHour = StartHour6;
        StopHour = StopHour6;
        StartMinute = StartMinute6;
        StopMinute = StopMinute6;
        StartTime = StartTime6;
        StopTime = StopTime6;
        break;
      case SUN:
        Serial.print("Using Sundayay scheduled interval: ");
        StartHour = StartHour7;
        StopHour = StopHour7;
        StartMinute = StartMinute7;
        StopMinute = StopMinute7;
        StartTime = StartTime7;
        StopTime = StopTime7;
        break;
    }

    //With Geofence ON , the heating will work without someone else only for the forst 2 hours of the interval. Allows the heating to heat before you arrive home and to stop when you leave home during a scheduled day if the Geofence function is enabled.
    beforearrival = Hour - StartHour;
    if (beforearrival >= 2) {
      preheating = 0;
    }
    else {
      preheating = 1;
    }
    Serial.println();
    Serial.print("Printing the time before checking the interval: ");
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

    //sameday interval passed
    if (Hour > StartHour && Hour < StopHour) //
    {
      interval = 1;
      Serial.println("109");
    }
    else if (Hour > StartHour && Hour > StopHour) {
      interval = 0;
      Serial.println("110");
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
