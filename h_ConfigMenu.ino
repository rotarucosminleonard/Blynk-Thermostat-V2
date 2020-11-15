void ConfigMenu() {

  int cursorpos;
  switch(cursorpos){
    case 1:
    //cursor position 1
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 24);
    ucg.print(">"); 

    case 2:
    //cursor position 2
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 38);
    ucg.print(">"); 

    case 3:
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
    //cursor position 3
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 52);
    ucg.print(">");  

    case 4:
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
     //cursor position 4
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 66);
    ucg.print(">");  

    case 5:
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
    //cursor position 5
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 80);
    ucg.print(">"); 

    case 6:
    ucg.setColor(0, 0, 0);  // Set color (0,R,G,B)
    ucg.drawBox(0, 10, 10, 100);  // Start from top-left pixel (x,y,wigth,height)
    //cursor position 6
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(2, 94);
    ucg.print(">");              
  }       
  
  // menu == 1
    ucg.clearScreen();
    ucg.setColor(255, 255, 255); 
    ucg.setPrintPos(10, 10);
    ucg.print("Settings :");
    ucg.setPrintPos(15, 24); //160/128
    ucg.print(" Set Time and Date");
    ucg.setPrintPos(15, 38); //160/128
    ucg.print(" Scheduling:"); if (scheduled == 1 ){ ucg.print("    Enabled");} else { ucg.print("   Disabled");};
    ucg.setPrintPos(15, 52); //160/128
    ucg.print(" Set the time intervals");
    ucg.setPrintPos(15, 66); //160/128
    ucg.print(" Geofence:"); if (GPSAutoOff == 1 ){ ucg.print("    Enabled");} else { ucg.print("   Disabled");}
    ucg.setPrintPos(15, 80); //160/128
    ucg.print(" Ref. Temp.:");    
    ucg.setPrintPos(15, 94); //160/128
    ucg.print(" Save & Exit!");




  
}
