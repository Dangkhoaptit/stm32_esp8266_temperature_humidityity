#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "TP-LINK_E902";
const char *password = "0963957246";

// const long utcOffsetInSeconds = 3600;

// Define NTP Client to get time
WiFiUDP ntpUDP;

SoftwareSerial mySerial(D4, D5); //RX, TX
// D4 RX - PA9
// D5 TX - PA10
// (Send and Receive)

//String tmp = "";

int button = D0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    Serial.println( "wifi connected" );

  pinMode(button,INPUT);
}

void loop() {

   if(mySerial.available() > 1){//Read from  STM module and send to serial monitor
          String input = mySerial.readString();
          Serial.println( "From Stm32" );
          Serial.println(input);    
        }
  int buttonState ;
  buttonState = digitalRead(button);
  if(buttonState==LOW){
       /* if(Serial.available() > 0){//Read from serial monitor and send 
          String input = Serial.readString();
          Serial.println( "From ESP" );
          Serial.println(input); 
          mySerial.println(input);    
        }*/
       
       
  }
}
