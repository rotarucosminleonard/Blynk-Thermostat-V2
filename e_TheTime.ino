void OfflineTime()
{
  //The offline time gets used for the interval checks and it gets updated when the mcu gets connected to the server
  Serial.println(" ");
  Serial.print("Offline RTC:  ");
  OfflineRTC.getTime();
  Serial.print(OfflineRTC.hour, DEC);
  Serial.print(":");
  Serial.print(OfflineRTC.minute, DEC);
  Serial.print(":");
  Serial.print(OfflineRTC.second, DEC);
  Serial.print("  ");
  Serial.print(OfflineRTC.month, DEC);
  Serial.print("/");
  Serial.print(OfflineRTC.dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(OfflineRTC.year+2000, DEC);
  Serial.print(" ");

  switch (OfflineRTC.dayOfWeek)// Friendly printout the weekday
  {
    case MON:
      Serial.print("MON");
      today = 2;
      yesterday = 1; // Sunday
      tomorrow = 3;  //Tuesday
      break;
    case TUE:
      Serial.print("TUE");
      today = 3;
      yesterday = 2; //Monday
      tomorrow = 4;  //Wednesday
      break;
    case WED:
      Serial.print("WED");
      today = 4;
      yesterday = 3; //Tuesday
      tomorrow = 5;  //Thursday
      break;
    case THU:
      Serial.print("THU");
      today = 5;
      yesterday = 4; // Wed
      tomorrow = 6;  // Fri
      break;
    case FRI:
      Serial.print("FRI");
      today = 6;
      yesterday = 5; // Thu
      tomorrow = 7;  // Sat
      break;
    case SAT:
      Serial.print("SAT");
      today = 7;
      yesterday = 6; // Fri
      tomorrow = 1; // Sun
      break;
    case SUN:
      Serial.print("SUN");
      today = 1;
      yesterday = 7; // Sat
      tomorrow = 2; // Monday
      break;
  }
  
  
  // These are required for Interval Check 
  Hour = OfflineRTC.hour;
  Minute = OfflineRTC.minute;
}

void OnlineTime()
{
  if(Blynk.connected()){
    //Blynk.sendInternal("rtc", "sync");
    onlinetimechk = 1;
    // You can call hour(), minute(), ... at any time
    // Please see Time library examples for details

//    Serial.println("Weekday: " + String(weekday()));
    Serial.println(" ");
    Serial.print("Online RTC:   ");
    OfflineRTC.getTime();
    Serial.print(String(hour()));
    Serial.print(":");
    Serial.print(String(minute()));
    Serial.print(":");
    Serial.print(String(second()));
    Serial.print("  ");
    Serial.print(String(month()));
    Serial.print("/");
    Serial.print(String(day()));
    Serial.print("/");
    Serial.print(String(year()));
    Serial.print(" ");

    switch (weekday())// Friendly printout the weekday
    {
      case 2:
        Serial.print("MON");
        break;
      case 3:
        Serial.print("TUE");
        break;
      case 4:
        Serial.print("WED");
        break;
      case 5:
        Serial.print("THU");
        break;
      case 6:
        Serial.print("FRI");
        break;
      case 7:
        Serial.print("SAT");
        break;
      case 1:
        Serial.print("SUN");
        break; 
    }
    Serial.println(" ");    
  } 
  else {
    onlinetimechk = 0;
    Serial.println("Not yet connected for syncing the local time. Leave it untouched."); 
  }
}

void syncTheTime()
{
  if (onlinetimechk == 1) {
    OfflineRTC.fillByYMD(year(),month(),day());//Jan 19,2013
      OfflineRTC.fillByHMS(hour(),minute(),second());//15:28 30"
      switch (weekday())// Friendly printout the weekday
        {
          case 2:
            OfflineRTC.fillDayOfWeek(MON);
            break;
          case 3:
            OfflineRTC.fillDayOfWeek(TUE);
            break;
          case 4:
            OfflineRTC.fillDayOfWeek(WED);
            break;
          case 5:
            OfflineRTC.fillDayOfWeek(THU);
            break;
          case 6:
            OfflineRTC.fillDayOfWeek(FRI);
            break;
          case 7:
            OfflineRTC.fillDayOfWeek(SAT);
            break;
          case 1:
            OfflineRTC.fillDayOfWeek(SUN);
            break;
        }
      OfflineRTC.setTime();//write time to the RTC chip    
      Serial.println("Time Sync done!");
  }
  else {
    Serial.println("Time not sicronised, Keep the local RTC untouched.");
  }
  
}
