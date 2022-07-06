#include <SoftwareSerial.h>
//#include <NTPClient.h>
#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>


SoftwareSerial mySerial(D4, D5); //RX, TX
// D4 RX - PA9
// D5 TX - PA10
// (Send and Receive)

//String tmp = "";

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop() {

   if(mySerial.available() > 0){//response data from stm to esp
          String input = mySerial.readString();
          Serial.println( "response from Stm32\n" );
          Serial.println(input);    
        }
  
   if(Serial.available() ){
        if(Serial.available() > 0){//Read from serial monitor and send 
          String a = Serial.readString();
          Serial.println( "From ESP\n" );
          Serial.println(a); 
          mySerial.println(a);    
        }
      
//    do
//      { char t = Serial.read();
//      } while (Serial.available() > 0);
      
  }
  
}
