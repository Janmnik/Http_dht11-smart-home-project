 #include "DHT.h"
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 #include <ArduinoJson.h>

 const char* ssid = "Network";
 const char* password = "password";
   
 DHT dht(2,DHT11);
 
 int Temperature=0;
 int Humidity=0;
 String host="http://192.168.x.x/HomeCondition/Temperature";
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
    //    postDataToServer();
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
    http.begin(client,host);
    http.addHeader("Content-Type", "aplication/json");

    StaticJsonDocument<200> doc;

    doc["Id"] = "0";
    doc["TemperatureC"] = Temperature;

    String requestBody;
    
    serializeJson(doc, requestBody);
    int httpResponseCode = http.POST(requestBody);
    if(httpResponseCode>0){
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      } else{
          Serial.printf("Error sending HTTP POST\n");
        }
 
    }
      Serial.println("Temperature in C:");
      Serial.println(Temperature);
      Serial.println("Humidity in %:");
      Serial.println(Humidity);
      delay(5000);
    }
    
 
