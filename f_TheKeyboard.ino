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
    prevUpState = upKey;
  }


  downKey = mcp.digitalRead(DOWNpin);
  if (downKey != prevDownState) {
    if (downKey == LOW) {
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
    prevDownState = downKey;
  }


  leftKey = mcp.digitalRead(LEFTpin);
  if (leftKey != prevLeftState) {
    if (leftKey == LOW) {
      delay(50);    
      mainDisplay();    
    }
    prevLeftState = leftKey;
  }

  rightKey = mcp.digitalRead(RIGHTpin);
  if (rightKey != prevRightState) {
    if (rightKey == LOW) {
      delay(50);    
      mainDisplay();    
    }
    prevRightState = rightKey;
  }



  okKey = mcp.digitalRead(OKpin);
  if (okKey != prevOkState) {
    if (okKey == LOW) {
      delay(50);    
      mainDisplay();    
    }
    prevOkState = okKey;
  }

  cancelKey = mcp.digitalRead(CANCELpin);
  if (cancelKey != prevCancelState) {
    if (cancelKey == LOW) {
      delay(50);    
      mainDisplay();    
    }
    prevCancelState = cancelKey;
  }
  
}
