void keyboard()
{

  leftKey = mcp.digitalRead(LEFTpin);
  upKey = mcp.digitalRead(UPpin);
  downKey = mcp.digitalRead(DOWNpin);
  rightKey = mcp.digitalRead(RIGHTpin);
  okKey = mcp.digitalRead(OKpin);
  cancelKey = mcp.digitalRead(CANCELpin);


  upKey = mcp.digitalRead(UPpin);
  if (upKey != prevUpState) {
    if (upKey == LOW) {
      if (menu == 0) {
        tempset=tempset+0.5;
        EEPROM.write(tempsetaddress, tempset);
        EEPROM.commit();
        if(Blynk.connected())
        {
          Blynk.virtualWrite(tempSetVPin, tempset);    
        }
        Serial.println("Increased tempset: ");
        Serial.println(tempset);
        delay(50);  
        mainDisplay();  
      }
      else {
        cursorpos ++;
        delay(50);        
      }

    }
    prevUpState = upKey;
  }


  downKey = mcp.digitalRead(DOWNpin);
  if (downKey != prevDownState) {
    if (downKey == LOW) {
      if (menu == 0) {
        tempset=tempset-0.5;
        EEPROM.write(tempsetaddress, tempset);
        EEPROM.commit();
        if(Blynk.connected())
        {
          Blynk.virtualWrite(tempSetVPin, tempset);  
        }
        Serial.println("Decreased tempset: ");  
        Serial.println(tempset);
        delay(50);    
        mainDisplay();      
      }
      else {
        cursorpos --;
        delay(50);      
      }

    }
    prevDownState = downKey;
  }


  leftKey = mcp.digitalRead(LEFTpin);
  if (leftKey != prevLeftState) {
    if (leftKey == LOW) {
      if (menu == 0){
        if (scheduled == 1){
          scheduled = 0;
          EEPROM.write(scheduledaddress, scheduled);
          EEPROM.commit();            
        }
        else {
          scheduled = 1;
          EEPROM.write(scheduledaddress, scheduled);
          EEPROM.commit();     
        }
      }
      else {
        value--;        
      }

    }
    prevLeftState = leftKey;
  }

  rightKey = mcp.digitalRead(RIGHTpin);
  if (rightKey != prevRightState) {
    if (rightKey == LOW) {
      if (menu == 0){
        if (scheduled == 1){
          scheduled = 0;
          EEPROM.write(scheduledaddress, scheduled);
          EEPROM.commit();            
        }
        else {
          scheduled = 1;
          EEPROM.write(scheduledaddress, scheduled);
          EEPROM.commit();     
        }
      }
      else {
        value++;        
      }
    }
    prevRightState = rightKey;
  }



  okKey = mcp.digitalRead(OKpin);
  if (okKey != prevOkState) {
    if (okKey == LOW) {
      if (menu == 0){
        menu = 1;        
      }
      else {
        // save function
        //selectt=1;
      }

    }
    prevOkState = okKey;
    mainDisplay();
  }

  cancelKey = mcp.digitalRead(CANCELpin);
  if (cancelKey != prevCancelState) {
    if (cancelKey == LOW) {
      if (menu >= 0){
        // back up a menu  
        menu = menu-1;
      }
    ucg.clearScreen();
    mainDisplay();
    }
    prevCancelState = cancelKey;

  }
  
}
