/*
******************************************************************************
* @file: Index Code.html
* @author: tungvtt1609
* @version: V1.0.0
* @date: 25-02-2022
* @brief: This file is the main file of the project
******************************************************************************
*Com3
*/

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//----------------------------------------

SoftwareSerial mySerial(D4, D5); //RX, TX
// D4 RX - PA9
// D5 TX - PA10
// (Send and Receive)


#include "Index.h" //--> Our HTML webpage contents with javascripts

#define ON_Board_LED 0 //--> Defining an On Board LED (GPIO0 = D3), used for indicators when the process of connecting to a wifi router and when there is a client request.

//----------------------------------------SSID and Password of your WiFi router
const char *ssid = "mixao";          //--> Your wifi name
const char *password = "987654321"; //--> Your wifi password
//----------------------------------------

ESP8266WebServer server(80); //--> Server on port 80
String Data_In, DHT_Temp, DHT_Hum;

void receiveFromStm32(){//Read from  STM module and send to serial monitor
   if(mySerial.available() > 0){
          Data_In = mySerial.readString();
          Serial.println(Data_In);
          
          if (Data_In[0] == 't')
          {
            Serial.println( " " );
            Serial.println(Data_In);
            DHT_Temp = "";
            for(int i = 0 ; i< 4; i++){
              DHT_Temp  += Data_In[i+3];
            }
            Serial.println(DHT_Temp);
          }
          else if(Data_In[0] == 'h'){
            Serial.println( " " );
            Serial.println(Data_In);
            DHT_Hum = "";
           for(int i = 0 ; i< 4; i++){
              DHT_Hum  += Data_In[i+3];
            }
            Serial.println(DHT_Hum);
          }
    }
}

void handleRoot()
{
    String s = MAIN_page;             //--> Read HTML contents
    server.send(200, "text/html", s); //--> Send web page
}

void handleTemp()
{
    server.send(200, "text/plane", DHT_Temp);
}

void handleHum()
{
    server.send(200, "text/plane", DHT_Hum);
}
//--------------------------------------------------------------------------------void setup()
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    mySerial.begin(9600);
    delay(500);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password); //--> Connect to your WiFi router
    Serial.println("");

    //----------------------------------------Wait for connection
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
        digitalWrite(ON_Board_LED, LOW);
        delay(250);
        digitalWrite(ON_Board_LED, HIGH);
        delay(250);
        //----------------------------------------
    }
    //----------------------------------------
    digitalWrite(ON_Board_LED, HIGH);
    Serial.println("");
    Serial.print("Successfully connected to : ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    //----------------------------------------

    server.on("/", handleRoot);
    server.on("/gettemperature",handleTemp);
    server.on("/gethumidity",handleHum);
    server.begin(); //--> Start server
    Serial.println("HTTP server started");

    Serial.println();
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------void loop()
void loop()
{
    // put your main code here, to run repeatedly:
    server.handleClient(); //--> Handle client requests
    receiveFromStm32();
}
