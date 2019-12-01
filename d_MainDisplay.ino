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
    
    /* Temporary Placeholders */
    
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
  
      if (scheduled == 1)
      {
        ucg.setFont(ucg_font_5x8_mr);
        ucg.setPrintPos(1,115);  
        ucg.print("Interval:  "); 
        ucg.setPrintPos(54,115);  
    
        // Print Scheduled Time
        if (StartTime != 0 && StopTime != 0)
        {
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
          ucg.print(" - ");
          if ((StopHour) < 10)    {
            ucg.print("0" + String(StopHour));
          }
          else {
            ucg.print(StopHour);
          }
          ucg.print(":");
          if ((StopMinute) < 10)    {
            ucg.print("0" + String(StopMinute) + "         ");
          }
          else {
            ucg.print(String(StopMinute) + "          ");
          }
        }
      }
  
      else if (StartTime == 0 && StopTime == 0)
      {
         ucg.setPrintPos(1,115);  
         ucg.print("Nothing scheduled this week!    ");
      }
      if (scheduled == 0 && GPSAutoOff == 0)
      {
        ucg.setPrintPos(1,115);  
        ucg.print("Manual Mode, Permanent!     ");
      }
      if (scheduled == 0 && GPSAutoOff == 1)
      {
        ucg.setPrintPos(1,115);  
        ucg.print("Manual Mode with Geofence!    ");
      }
  
  
      ucg.setFont(ucg_font_5x8_mr);
      ucg.setPrintPos(1,126);  
      ucg.print("Sch.Days:"); 
      ucg.setPrintPos(54,126);
      if (Mo == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Mo "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Mo "); //Scheduled days   
      }
      if (Tu == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Tu "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Tu "); //Scheduled days  
      }
      if (We == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("We "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("We "); //Scheduled days   
      }
      if (Th == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Th "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Th "); //Scheduled days  
      }
      if (Fr == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Fr "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Fr "); //Scheduled days  
      }
      if (Sa == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Sa "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Sa "); //Scheduled days   
      }
      if (Su == 1){
        ucg.setColor(0, 255, 0);
        ucg.print("Su "); //Scheduled days    
      }
      else {
        ucg.setColor(255, 0, 0);
        ucg.print("Su "); //Scheduled days  
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
      if (t >= 10)
      {
        ucg.setPrintPos(5,54);    
      }
      else if (t<10)
      {
        ucg.setPrintPos(21,54);
       
      }
      ucg.print(t,1);ucg.setFont(ucg_font_unifont_mr);ucg.setPrintPos(69,43);ucg.print("o");ucg.setPrintPos(80,54);ucg.setFont(ucg_font_profont29_mr);ucg.print("C");  //  Temperature
  
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
      ucg.setPrintPos(103,41);
      ucg.setFont(ucg_font_5x8_mr);
      ucg.print("Pressure");
      ucg.setPrintPos(103,53);
      ucg.print(p + String(" hPa"));
      
      ucg.setPrintPos(103,66);
      ucg.setFont(ucg_font_5x8_mr);
      ucg.print("Gases");
      ucg.setPrintPos(103,78);
      ucg.print(g + String(" KOhms") );
      
    
      //  ucg.setColor(255, 255, 255);
      //  ucg.setPrintPos(25, 24);
      //  tft.print("13 : 24");
      //  tft.setTextSize(1);
      //  tft.setFont();
      //  ucg.setPrintPos(22, 27);
      //  tft.print("Tue 24 Jul 2019");
      //  tft.setFont(&FreeSans18pt7b);
      //  tft.setTextSize(1);
      //  ucg.setPrintPos(10, 60);   
      //  ucg.print("23"); tft.print("o"); tft.print("C");
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
