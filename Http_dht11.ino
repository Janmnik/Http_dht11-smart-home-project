 #include <DHT.h>
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>


 const char* ssid = "SSID";
 const char* password = "PASS";
   
 DHT dht(2,DHT11);

 unsigned  int Temperature=0;
 unsigned  int Humidity=0;
 unsigned long lastTime=0;
 unsigned long timerDelay=5000;
 
 void setup()  
 { 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("...");
    }
  Serial.println();  
 }  
 void loop()  
 {  
  digitalWrite(LED_BUILTIN, HIGH); // turn the blue led off
 if(( millis()-lastTime )> timerDelay){
  if (WiFi.status() == WL_CONNECTED){
  WiFiClient client;  
  HTTPClient http; 
  
     float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
     delay(500);
    }else{
     //Serial.println("Temperature in C:");
     if(t>0 || h<110)
     {
         Temperature=(int)(t);//*1.897);  
         //Serial.println("Humidity in %:");  
         Humidity=(int)(h);//-100);  
     }else{http.end();}
      }
      String TempString = String(Temperature);
      String HumString = String(Humidity);
      String host="http://192.168.0.20:5108/HomeCondition/Temperature/Add?temperatureC="+TempString;
      if( t!=0 || h!=0 || h<100 ){
      http.begin(client, host);
      
      int httpCode = http.GET();
      if (httpCode > 0) { //Check the returning code
      String payload = http.getString();  //Get the request response payload
      Serial.println("Code "+payload);   //Print the response payload
      

    }else{
      Serial.println("Code "+(String)http.errorToString(httpCode).c_str());
      }
      }
      Serial.println("Temperature in C:");
      Serial.println(Temperature);
      Serial.println("Humidity in %:");
      Serial.println(Humidity);
      http.end();
     
      
  }else {
      Serial.println("WiFi Disconnected");     
      }
      lastTime = millis();
 }
 }

