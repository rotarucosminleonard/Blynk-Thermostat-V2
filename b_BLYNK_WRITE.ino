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
