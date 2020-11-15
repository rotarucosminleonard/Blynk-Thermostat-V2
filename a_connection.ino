void CheckConnection(){    // check every 11s if connected to Blynk server
  if(!Blynk.connected()){
    online = 0;
    yield();
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Not connected to Wifi! Connect...");
      //Blynk.connectWiFi(ssid, pass); // used with Blynk.connect() in place of Blynk.begin(auth, ssid, pass, server, port);
      //WiFi.config(arduino_ip, gateway_ip, subnet_mask);
      WiFi.begin(ssid, pass);
      delay(400); //give it some time to connect
      if (WiFi.status() != WL_CONNECTED)
      {
        Serial.println("Cannot connect to WIFI!");
        online = 0;
        wifi = 0;
        server = 0;
      }
      else
      {
        Serial.println("Connected to wifi!");
        wifi = 1;
        server = 0;
      }
    }
    
    if ( WiFi.status() == WL_CONNECTED && !Blynk.connected() )
    {
      Serial.println("Not connected to Blynk Server! Connecting..."); 
      Blynk.connect();  // // It has 3 attempts of the defined BLYNK_TIMEOUT_MS to connect to the server, otherwise it goes to the enxt line 
      if(!Blynk.connected()){
        Serial.println("Connection failed!"); 
        online = 0;
        wifi = 1;
        server = 0;
      }
      else
      {
        online = 1;
        wifi = 1;
        server = 1;
      }
    }
  }
  else{
    Serial.println("Connected to Blynk server!"); 
    online = 1;
    wifi = 1;
    server = 1; 
  }
}
