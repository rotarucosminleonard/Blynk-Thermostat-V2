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
    ucg.setPrintPos(8,100);
    ucg.setColor(100, 100, 0);  
    ucg.print("Yesterday"); 

    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(16,109);


    if (yesterday == 1){ // Sunday
        if ((StartHour7) < 10)    {
          ucg.print("0" + String(StartHour7));
        }
        else {
          ucg.print(StartHour7);
        }
         ucg.print(":");
        if ((StartMinute7) < 10)    {
          ucg.print("0" + String(StartMinute7));
        }
        else {
          ucg.print(StartMinute7);
        }
        
      ucg.setPrintPos(16,117);
        
        if ((StopHour7) < 10)    {
          ucg.print("0" + String(StopHour7));
        }
        else {
          ucg.print(StopHour7);
        }
        
        ucg.print(":");

         
        if ((StopMinute7) < 10)    {
          ucg.print("0" + String(StopMinute7));
        }
        else {
          ucg.print(String(StopMinute7));
        }
    }
    else if (yesterday == 2){ //Monday
        if ((StartHour1) < 10)    {
          ucg.print("0" + String(StartHour1));
        }
        else {
          ucg.print(StartHour1);
        }
         ucg.print(":");
        if ((StartMinute1) < 10)    {
          ucg.print("0" + String(StartMinute1));
        }
        else {
          ucg.print(StartMinute1);
        }

      ucg.setPrintPos(16,117);
        
        if ((StopHour1) < 10)    {
          ucg.print("0" + String(StopHour1));
        }
        else {
          ucg.print(StopHour1);
        }
        
        ucg.print(":");
         
        if ((StopMinute1) < 10)    {
          ucg.print("0" + String(StopMinute1));
        }
        else {
          ucg.print(String(StopMinute1));
        }      
    }
  
    else if (yesterday == 3){ // Tue
        if ((StartHour2) < 10)    {
          ucg.print("0" + String(StartHour2));
        }
        else {
          ucg.print(StartHour2);
        }
         ucg.print(":");
        if ((StartMinute2) < 10)    {
          ucg.print("0" + String(StartMinute2));
        }
        else {
          ucg.print(StartMinute2);
        }
        
      ucg.setPrintPos(16,117);
        
        if ((StopHour2) < 10)    {
          ucg.print("0" + String(StopHour2));
        }
        else {
          ucg.print(StopHour2);
        }
        
        ucg.print(":");
         
        if ((StopMinute2) < 10)    {
          ucg.print("0" + String(StopMinute2));
        }
        else {
          ucg.print(String(StopMinute2));
        } 
    }
    else if (yesterday == 4){ // Wed
        if ((StartHour3) < 10)    {
          ucg.print("0" + String(StartHour3));
        }
        else {
          ucg.print(StartHour3);
        }
         ucg.print(":");
        if ((StartMinute3) < 10)    {
          ucg.print("0" + String(StartMinute3));
        }
        else {
          ucg.print(StartMinute1);
        }
        
      ucg.setPrintPos(16,117);
        
        if ((StopHour3) < 10)    {
          ucg.print("0" + String(StopHour3));
        }
        else {
          ucg.print(StopHour3);
        }
        
        ucg.print(":");
         
        if ((StopMinute3) < 10)    {
          ucg.print("0" + String(StopMinute3));
        }
        else {
          ucg.print(String(StopMinute3));
        }  
    }
    else if (yesterday == 5){ // Thu
        if ((StartHour4) < 10)    {
          ucg.print("0" + String(StartHour4));
        }
        else {
          ucg.print(StartHour4);
        }
         ucg.print(":");
        if ((StartMinute4) < 10)    {
          ucg.print("0" + String(StartMinute4));
        }
        else {
          ucg.print(StartMinute4);
        }
        
      ucg.setPrintPos(16,117);
        
        if ((StopHour4) < 10)    {
          ucg.print("0" + String(StopHour4));
        }
        else {
          ucg.print(StopHour4);
        }
        
        ucg.print(":");
         
        if ((StopMinute4) < 10)    {
          ucg.print("0" + String(StopMinute4));
        }
        else {
          ucg.print(String(StopMinute4));
        }       
    }
    else if (yesterday == 6){ // Fri
        if ((StartHour5) < 10)    {
          ucg.print("0" + String(StartHour5));
        }
        else {
          ucg.print(StartHour5);
        }
         ucg.print(":");
        if ((StartMinute5) < 10)    {
          ucg.print("0" + String(StartMinute5));
        }
        else {
          ucg.print(StartMinute5);
        }
        
      ucg.setPrintPos(16,117);  
        
        if ((StopHour5) < 10)    {
          ucg.print("0" + String(StopHour5));
        }
        else {
          ucg.print(StopHour5);
        }
        
        ucg.print(":");
         
        if ((StopMinute5) < 10)    {
          ucg.print("0" + String(StopMinute5));
        }
        else {
          ucg.print(String(StopMinute5));
        }    
    }
    else if (yesterday == 7){ // Sat
        if ((StartHour6) < 10)    {
          ucg.print("0" + String(StartHour6));
        }
        else {
          ucg.print(StartHour6);
        }
         ucg.print(":");
        if ((StartMinute6) < 10)    {
          ucg.print("0" + String(StartMinute6));
        }
        else {
          ucg.print(StartMinute6);
        }
        
      ucg.setPrintPos(16,117);
        
        if ((StopHour6) < 10)    {
          ucg.print("0" + String(StopHour6));
        }
        else {
          ucg.print(StopHour6);
        }
        
        ucg.print(":");
         
        if ((StopMinute6) < 10)    {
          ucg.print("0" + String(StopMinute6));
        }
        else {
          ucg.print(String(StopMinute6));
        }       
    }



    // The days Scheduling: Today
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(60,100);
        ucg.setColor(255, 200, 0); 
        ucg.print("  Today"); 
    
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(68,109);

    if ( today == 1){ // Sunday
        if ((StartHour7) < 10)    {
          ucg.print("0" + String(StartHour7));
        }
        else {
          ucg.print(StartHour7);
        }
         ucg.print(":");
        if ((StartMinute7) < 10)    {
          ucg.print("0" + String(StartMinute7));
        }
        else {
          ucg.print(StartMinute7);
        }
    
        ucg.setPrintPos(68,117); 
          
        if ((StopHour7) < 10)    {
          ucg.print("0" + String(StopHour7));
        }
        else {
          ucg.print(StopHour7);
        }
        
        ucg.print(":");

         
        if ((StopMinute7) < 10)    {
          ucg.print("0" + String(StopMinute7));
        }
        else {
          ucg.print(String(StopMinute7));
        }
    }
    else if (today == 2){ //Monday
        if ((StartHour1) < 10)    {
          ucg.print("0" + String(StartHour1));
        }
        else {
          ucg.print(StartHour1);
        }
         ucg.print(":");
        if ((StartMinute1) < 10)    {
          ucg.print("0" + String(StartMinute1));
        }
        else {
          ucg.print(StartMinute1);
        }
    
        ucg.setPrintPos(68,117);
         
        if ((StopHour1) < 10)    {
          ucg.print("0" + String(StopHour1));
        }
        else {
          ucg.print(StopHour1);
        }
        
        ucg.print(":");
         
        if ((StopMinute1) < 10)    {
          ucg.print("0" + String(StopMinute1));
        }
        else {
          ucg.print(String(StopMinute1));
        }      
    }
  
    else if (today == 3){ // Tue
        if ((StartHour2) < 10)    {
          ucg.print("0" + String(StartHour2));
        }
        else {
          ucg.print(StartHour2);
        }
         ucg.print(":");
        if ((StartMinute2) < 10)    {
          ucg.print("0" + String(StartMinute2));
        }
        else {
          ucg.print(StartMinute2);
        }
    
        ucg.setPrintPos(68,117);   
         
        if ((StopHour2) < 10)    {
          ucg.print("0" + String(StopHour2));
        }
        else {
          ucg.print(StopHour2);
        }
        
        ucg.print(":");
         
        if ((StopMinute2) < 10)    {
          ucg.print("0" + String(StopMinute2));
        }
        else {
          ucg.print(String(StopMinute2));
        } 
    }
    else if (today == 4){ // Wed
        if ((StartHour3) < 10)    {
          ucg.print("0" + String(StartHour3));
        }
        else {
          ucg.print(StartHour3);
        }
         ucg.print(":");
        if ((StartMinute3) < 10)    {
          ucg.print("0" + String(StartMinute3));
        }
        else {
          ucg.print(StartMinute1);
        }
    
        ucg.setPrintPos(68,117);  
         
        if ((StopHour3) < 10)    {
          ucg.print("0" + String(StopHour3));
        }
        else {
          ucg.print(StopHour3);
        }
        
        ucg.print(":");
         
        if ((StopMinute3) < 10)    {
          ucg.print("0" + String(StopMinute3));
        }
        else {
          ucg.print(String(StopMinute3));
        }  
    }
    else if (today == 5){ // Thu
        if ((StartHour4) < 10)    {
          ucg.print("0" + String(StartHour4));
        }
        else {
          ucg.print(StartHour4);
        }
         ucg.print(":");
        if ((StartMinute4) < 10)    {
          ucg.print("0" + String(StartMinute4));
        }
        else {
          ucg.print(StartMinute4);
        }
    
        ucg.setPrintPos(68,117);
         
        if ((StopHour4) < 10)    {
          ucg.print("0" + String(StopHour4));
        }
        else {
          ucg.print(StopHour4);
        }
        
        ucg.print(":");
         
        if ((StopMinute4) < 10)    {
          ucg.print("0" + String(StopMinute4));
        }
        else {
          ucg.print(String(StopMinute4));
        }       
    }
    else if (today == 6){ // Fri
        if ((StartHour5) < 10)    {
          ucg.print("0" + String(StartHour5));
        }
        else {
          ucg.print(StartHour5);
        }
         ucg.print(":");
        if ((StartMinute5) < 10)    {
          ucg.print("0" + String(StartMinute5));
        }
        else {
          ucg.print(StartMinute5);
        }
    
        ucg.setPrintPos(68,117);
         
        if ((StopHour5) < 10)    {
          ucg.print("0" + String(StopHour5));
        }
        else {
          ucg.print(StopHour5);
        }
        
        ucg.print(":");
         
        if ((StopMinute5) < 10)    {
          ucg.print("0" + String(StopMinute5));
        }
        else {
          ucg.print(String(StopMinute5));
        }    
    }
    else if (today == 7){ // Sat
        if ((StartHour6) < 10)    {
          ucg.print("0" + String(StartHour6));
        }
        else {
          ucg.print(StartHour6);
        }
         ucg.print(":");
        if ((StartMinute6) < 10)    {
          ucg.print("0" + String(StartMinute6));
        }
        else {
          ucg.print(StartMinute6);
        }
    
        ucg.setPrintPos(68,117);  
         
        if ((StopHour6) < 10)    {
          ucg.print("0" + String(StopHour6));
        }
        else {
          ucg.print(StopHour6);
        }
        
        ucg.print(":");
         
        if ((StopMinute6) < 10)    {
          ucg.print("0" + String(StopMinute6));
        }
        else {
          ucg.print(String(StopMinute6));
        }       
    }
  

 

    // The days Scheduling: Tomorrow
    
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(111,100);
    ucg.setColor(100, 100, 0); 
    ucg.print("Tomorrow"); 
    
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(121,109);
    if (tomorrow == 1){ // Sunday
        if ((StartHour7) < 10)    {
          ucg.print("0" + String(StartHour7));
        }
        else {
          ucg.print(StartHour7);
        }
         ucg.print(":");
        if ((StartMinute7) < 10)    {
          ucg.print("0" + String(StartMinute7));
        }
        else {
          ucg.print(StartMinute7);
        }
        
        ucg.setPrintPos(121,117);
        
        if ((StopHour7) < 10)    {
          ucg.print("0" + String(StopHour7));
        }
        else {
          ucg.print(StopHour7);
        }
        
        ucg.print(":");

         
        if ((StopMinute7) < 10)    {
          ucg.print("0" + String(StopMinute7));
        }
        else {
          ucg.print(String(StopMinute7));
        }
    }
    else if (tomorrow == 2){ //Monday
        if ((StartHour1) < 10)    {
          ucg.print("0" + String(StartHour1));
        }
        else {
          ucg.print(StartHour1);
        }
         ucg.print(":");
        if ((StartMinute1) < 10)    {
          ucg.print("0" + String(StartMinute1));
        }
        else {
          ucg.print(StartMinute1);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour1) < 10)    {
          ucg.print("0" + String(StopHour1));
        }
        else {
          ucg.print(StopHour1);
        }
        
        ucg.print(":");
         
        if ((StopMinute1) < 10)    {
          ucg.print("0" + String(StopMinute1));
        }
        else {
          ucg.print(String(StopMinute1));
        }      
    }
    else if (tomorrow == 3){ // Tue
        if ((StartHour2) < 10)    {
          ucg.print("0" + String(StartHour2));
        }
        else {
          ucg.print(StartHour2);
        }
         ucg.print(":");
        if ((StartMinute2) < 10)    {
          ucg.print("0" + String(StartMinute2));
        }
        else {
          ucg.print(StartMinute2);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour2) < 10)    {
          ucg.print("0" + String(StopHour2));
        }
        else {
          ucg.print(StopHour2);
        }
        
        ucg.print(":");
         
        if ((StopMinute2) < 10)    {
          ucg.print("0" + String(StopMinute2));
        }
        else {
          ucg.print(String(StopMinute2));
        } 
    }
    else if (tomorrow == 4){ // Wed
        if ((StartHour3) < 10)    {
          ucg.print("0" + String(StartHour3));
        }
        else {
          ucg.print(StartHour3);
        }
         ucg.print(":");
        if ((StartMinute3) < 10)    {
          ucg.print("0" + String(StartMinute3));
        }
        else {
          ucg.print(StartMinute1);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour3) < 10)    {
          ucg.print("0" + String(StopHour3));
        }
        else {
          ucg.print(StopHour3);
        }
        
        ucg.print(":");
         
        if ((StopMinute3) < 10)    {
          ucg.print("0" + String(StopMinute3));
        }
        else {
          ucg.print(String(StopMinute3));
        }  
    }
    else if (tomorrow == 5){ // Thu
        if ((StartHour4) < 10)    {
          ucg.print("0" + String(StartHour4));
        }
        else {
          ucg.print(StartHour4);
        }
         ucg.print(":");
        if ((StartMinute4) < 10)    {
          ucg.print("0" + String(StartMinute4));
        }
        else {
          ucg.print(StartMinute4);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour4) < 10)    {
          ucg.print("0" + String(StopHour4));
        }
        else {
          ucg.print(StopHour4);
        }
        
        ucg.print(":");
         
        if ((StopMinute4) < 10)    {
          ucg.print("0" + String(StopMinute4));
        }
        else {
          ucg.print(String(StopMinute4));
        }       
    }
    else if (tomorrow == 6){ // Fri
        if ((StartHour5) < 10)    {
          ucg.print("0" + String(StartHour5));
        }
        else {
          ucg.print(StartHour5);
        }
         ucg.print(":");
        if ((StartMinute5) < 10)    {
          ucg.print("0" + String(StartMinute5));
        }
        else {
          ucg.print(StartMinute5);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour5) < 10)    {
          ucg.print("0" + String(StopHour5));
        }
        else {
          ucg.print(StopHour5);
        }
        
        ucg.print(":");
         
        if ((StopMinute5) < 10)    {
          ucg.print("0" + String(StopMinute5));
        }
        else {
          ucg.print(String(StopMinute5));
        }    
    }
    else if (tomorrow == 7){ // Sat
        if ((StartHour6) < 10)    {
          ucg.print("0" + String(StartHour6));
        }
        else {
          ucg.print(StartHour6);
        }
         ucg.print(":");
        if ((StartMinute6) < 10)    {
          ucg.print("0" + String(StartMinute6));
        }
        else {
          ucg.print(StartMinute6);
        }

        ucg.setPrintPos(121,117);
        
        if ((StopHour6) < 10)    {
          ucg.print("0" + String(StopHour6));
        }
        else {
          ucg.print(StopHour6);
        }
        
        ucg.print(":");
         
        if ((StopMinute6) < 10)    {
          ucg.print("0" + String(StopMinute6));
        }
        else {
          ucg.print(String(StopMinute6));
        }       
    }


  
    ucg.setFont(ucg_font_5x8_mr);
    ucg.setPrintPos(1,126);  
    ucg.setColor(255, 255, 255); 
    ucg.print(NAMEandVERSION); 

  }
  // menu == 1
  else {
    ucg.clearScreen();
    ucg.setColor(255, 255, 255); 
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
