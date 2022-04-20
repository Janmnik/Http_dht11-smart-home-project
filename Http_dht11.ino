 #include "DHT.h"
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>

 const char* ssid = "Network";
 const char* password = "password";
   
 DHT dht(2,DHT11);
 
 int Temperature=0;
 int Humidity=0;
 void setup()  
 { 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("...");
    }
  Serial.println();  

 }  
 void loop()  
 {  
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http; //Declare an object of class HTTPClient
    digitalWrite(LED_BUILTIN, HIGH); // turn the blue led off
     float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      //Serial.println(F("Failed to read from DHT sensor!"));
      delay(500);
      return;
    }else{
     //Serial.println("Temperature in C:");
     if(t<0)
       Temperature=(int)(dht.readTemperature( )*-1.897);
     else
       Temperature=(int)(dht.readTemperature( )*1.897);  
       //Serial.println("Humidity in %:");  
       Humidity=(int)(dht.readHumidity()-100);  
       delay(1000);
      }
      WiFiClient client;
      String host="http://192.168.x.x/TemperatureC/"+Temperature;
      http.begin(client,host);
      int httpCode = http.GET();
      if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();  //Get the request response payload
      Serial.println(payload);   //Print the response payload
 
    }
      Serial.println("Temperature in C:");
      Serial.println(Temperature);
      Serial.println("Humidity in %:");
      Serial.println(Humidity);

      http.end();
    }
    delay(5000);
 }  
