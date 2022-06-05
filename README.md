## Http_dht11

Libraries:

Arduino_JSON
by Arduino Wersja 0.1.0

DHT sensor library
by Adafruit Wersja 1.4.2

Adafruit ESP8266
by Adafruit Wersja 1.0.1

Adres Api serwera IP: 192.168.0.20 /24 


### Response Code ###
---------------------------------------------------------------
Data: |
--- |
temp: 1-50°C |
Humidity: 20-90%DH |

Error code: |
--- |  
temp: 12°C |
Humidity: 167%DH |

OFF: |
--- |
temp: 0°C |
Humidity: 0%DH |

---------------------------------------------------------------
The temperature data is currently being transferred in the program.
The humidity data can be sent if changed variable name host.
"IP:PORT&field1="+TempString&field2="+HumString
![chart](https://github.com/SmartHomeUMG/Http_dht11/blob/main/chartThingSpeak.png)
---------------------------------------------------------------
Connection diagram
![schemat](https://github.com/SmartHomeUMG/Http_dht11/blob/main/schemat.png)




