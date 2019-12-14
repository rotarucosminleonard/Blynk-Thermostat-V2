void mainDisplay()
{
  if (menu == 0){
    ucg.setColor(0, 255, 255, 255);    // use white as main color for the font
    ucg.setFontMode(UCG_FONT_MODE_SOLID);
    ucg.setFont(ucg_font_5x8_mr);
    if (online == 1)
    {
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setColor(0,255,0); // green
      ucg.setPrintPos(2,7);
      ucg.print("Connected    ");
      signalStrength();
      ucg.setColor(255, 255, 255); 
      ucg.setPrintPos(140, 7); //160/128
      ucg.print(signalQuality);  
      ucg.print("%");       
    }
    else if (wifi == 0)
    {
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setColor(255,0,0);
      ucg.setPrintPos(2,6);
      ucg.print("Wifi Issue");     
      ucg.setColor(255, 0, 0); 
      ucg.setPrintPos(140, 7); //160/128
      ucg.print("0%");      
    }
    else if (wifi == 1 && server == 0)
    {
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setColor(255,0,0);
      ucg.setPrintPos(2,6);
      ucg.print("Server Issue"); 
      signalStrength();
      ucg.setColor(255, 255, 255); 
      ucg.setPrintPos(140, 7); //160/128
      ucg.print(signalQuality);
      ucg.print("%");      
    }
    
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setColor(50, 180, 255);
      ucg.setPrintPos(70,6);
    if ((OfflineRTC.hour) < 10)    {
      ucg.print( "0"+ String(OfflineRTC.hour, DEC));
    }
    else {
      ucg.print(String(OfflineRTC.hour, DEC));
    }
      
    ucg.print(":");
    if ((OfflineRTC.minute) < 10)    {
      ucg.print( "0"+ String(OfflineRTC.minute, DEC));
    }
    else {
      ucg.print(String(OfflineRTC.minute, DEC));
    }
      
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setColor(255, 200, 0);
    ucg.setPrintPos(30,14);
    switch (OfflineRTC.dayOfWeek)// Friendly printout the weekday
    {
      case MON:
        ucg.print("Mon. ");
        break;
      case TUE:
        ucg.print("Tue. ");
        break;
      case WED:
        ucg.print("Wed. ");
        break;
      case THU:
        ucg.print("Thu. ");
        break;
      case FRI:
        ucg.print("Fri. ");
        break;
      case SAT:
        ucg.print("Sat. ");
        break;
      case SUN:
        ucg.print("Sun. ");
        break;
    }
      
    if ((OfflineRTC.dayOfMonth) == 1)
    {
      ucg.print(" " + String(OfflineRTC.dayOfMonth)+"st of " );   
    }
    else if ((OfflineRTC.dayOfMonth) == 2)
    {
      ucg.print(" " + String(OfflineRTC.dayOfMonth)+"nd of " );   
    }
    else if ((OfflineRTC.dayOfMonth) == 3)
    {
      ucg.print(" " + String(OfflineRTC.dayOfMonth)+"rd of " );   
    }
    else if ((OfflineRTC.dayOfMonth) > 3 )
    {
      ucg.print(" " + String(OfflineRTC.dayOfMonth)+"th of " );      
    }
      
    switch (OfflineRTC.month)// Friendly printout the month
    {
      case 1:
        ucg.print("January");
        break;
      case 2:
        ucg.print("February");
        break;
      case 3:
        ucg.print("March    ");
        break;
      case 4:
        ucg.print("April    ");
        break;
      case 5:
        ucg.print("May      ");
        break;
      case 6:
        ucg.print("June     ");
        break;
      case 7:
        ucg.print("July     ");
        break;
      case 8:
        ucg.print("August   ");
        break;
      case 9:
        ucg.print("September");
        break;
      case 10:
        ucg.print("October  ");
        break;
      case 11:
        ucg.print("November ");
        break;
      case 12:
        ucg.print("December ");
        break;
    }


    ucg.setFont(ucg_font_unifont_mr);
    ucg.setColor(100, 255, 100);
    ucg.setPrintPos(2,29);
    ucg.print("Set: "); ucg.print(tempset,1);
    ucg.setPrintPos(85,29);
    if (h > 55)
    {
      ucg.print("Too Humid!");  //  Comfort Level      
    }
    else if (h < 30)
    {
      ucg.print("Too Dry!  ");  //  Comfort Level      
    }
    else if (h > 29 && h<55)
    {
      ucg.print("Comfy!    ");  //  Comfort Level      
    }
  
    ucg.setFont(ucg_font_profont29_mr);
    ucg.setColor(255, 55, 55);
    if (temp >= 10)
    {
      ucg.setPrintPos(5,54);    
    }
    else if (temp<10)
    {
    ucg.setPrintPos(21,54);   
    }
    ucg.print(temp,1);ucg.setFont(ucg_font_unifont_mr);ucg.setPrintPos(69,43);ucg.print("o");ucg.setPrintPos(80,54);ucg.setFont(ucg_font_profont29_mr);ucg.print("C");  //  Temperature
    ucg.setFont(ucg_font_profont29_mr);
    ucg.setColor(45, 170, 255);
    
    if (h >=10)
    {
      ucg.setPrintPos(5,80);
    }
    else 
    {
      ucg.setPrintPos(21,80);
    }
    ucg.print(h,1);ucg.setPrintPos(80,80);ucg.print("%");  //  Humidity
  
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(100,41);
    ucg.setFont(ucg_font_5x8_mr);
    ucg.print("Pressure");
    ucg.setPrintPos(100,53);
    ucg.print(p + String(" hPa"));
      
    ucg.setPrintPos(100,66);
    ucg.setFont(ucg_font_5x8_mr);
    ucg.print("Gases");
    ucg.setPrintPos(100,78);
    ucg.print(g + String(" KOhms") );

    if (scheduled == 1)
    {
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setPrintPos(1,91); 
      if (interval == 1) {
        ucg.setColor(0,255,0);  
        ucg.print("Scheduling: ON ");            
      }
      else {
        ucg.setColor(255,0,0);  
        ucg.print("Scheduling: ON ");               
      }
    }
    else if (scheduled == 0)
    {
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setPrintPos(1,91);
      ucg.setColor(255, 200, 0);  
      ucg.print("Scheduling: OFF");          
    }

    if (GPSAutoOff == 1){
      if (GPSTrigger == 1) {
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(85,91);
        ucg.setColor(0,255,0);  
        ucg.print("Geofence: ON ");
      }
      else {
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(85,91);
        ucg.setColor(255,0,0);  
        ucg.print("Geofence: ON ");                   
      }
    }
    else if (GPSAutoOff == 0){
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setPrintPos(85,91);
      ucg.setColor(255, 200, 0);
      ucg.print("Geofence: OFF");    
    }

    // The days Scheduling: Yesterday
    
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(10,100);
    ucg.setColor(255,0,0);  
    ucg.print("Yesterday"); 

    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(16,109);
    ucg.setColor(255,0,0);  
    ucg.print("xx:xx");
    ucg.setPrintPos(16,117);
    ucg.setColor(255,0,0);       
    ucg.print("xx:xx");



    // The days Scheduling: Tomorrow
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(111,100);
    ucg.setColor(255,0,0);  
    ucg.print("Tomorrow"); 
    
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(121,109);
    ucg.setColor(255,0,0);  
    ucg.print("xx:xx");
    ucg.setPrintPos(121,117);
    ucg.setColor(255,0,0);       
    ucg.print("xx:xx");


// Today's interval printed on the screen
    switch (OfflineRTC.dayOfWeek)// Friendly printout the weekday
    {
      case MON:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Monday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case TUE:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Tuesday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case WED:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Wednesday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case THU:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Thursday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case FRI:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Friday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case SAT:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Saturday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
      case SUN:
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255,0,0);  
        ucg.print("Sunday"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);
        ucg.setColor(255,0,0); 
        if ((StartHour) < 10)    {
          ucg.print("0" + String(StartHour));
        }
        else {
          ucg.print(StartHour);
        }
         ucg.print(":");
        if ((StartMinute) < 10)    {
          ucg.print("0" + String(StartMinute));
        }
        else {
          ucg.print(StartMinute);
        }
        ucg.setPrintPos(68,117);
        ucg.setColor(255,0,0);       
          
        if ((StopHour) < 10)    {
          ucg.print("0" + String(StopHour));
        }
        else {
          ucg.print(StopHour);
        }
        ucg.print(":");
        if ((StopMinute) < 10)    {
          ucg.print("0" + String(StopMinute));
        }
        else {
          ucg.print(String(StopMinute));
        }
        break;
    }
  
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(1,126);  
    ucg.print("Bottom Placeholder"); 
    ucg.setPrintPos(54,126);


  }
  // menu == 1
  else {
    ucg.clearScreen();
    ucg.setColor(255, 0, 0);
    ucg.setPrintPos(10, 10);
    ucg.print("The Menu:");
    ucg.setPrintPos(15, 24); //160/128
    ucg.print(" Option 1");
    ucg.setPrintPos(15, 38); //160/128
    ucg.print(" Option 2");
    ucg.setPrintPos(15, 52); //160/128
    ucg.print(" Option 3");
    ucg.setPrintPos(15, 66); //160/128
    ucg.print(" Option 4");
    ucg.setPrintPos(10, 80); //160/128
    ucg.print(" Save & Exit!");
  }
}


// For viewing all the characters  
void fonts(){
  ucg.setColor(0, 255, 255, 255);    // use white as main color for the font
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(1,14);
  ucg.setFont(ucg_font_ncenR12_tf);
  int xx = 0;
  int y = 0;
  int i = 0;
  int newrow = 0;
  while (xx < 400) {
    // do something repetitive 200 times
    xx++;
    i++;
    if (i == 12)
    {
      i = 0;
      y=y+14;
      ucg.setPrintPos(1,y);
    }
    ucg.print((char)xx);
  }
}
