/*
******************************************************************************
* @file: Index Code.html
* @author: tungvtt1609
* @version: V1.0.0
* @date: 25-02-2022
* @brief: This file is the main file of the project
******************************************************************************
*/

//===================================================================================Heart Rate Sensor Station Mode
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
const char *ssid = "cntt";          //--> Your wifi name
const char *password = "cntt56789"; //--> Your wifi password
//----------------------------------------

ESP8266WebServer server(80); //--> Server on port 80
String temperature;

void receiveFromStm32(){//Read from  STM module and send to serial monitor
   if(mySerial.available() > 1){
          temperature = mySerial.readString();
          Serial.println( "From Stm32" );
          Serial.println(temperature);    
    }
}

void handleRoot()
{
    String s = MAIN_page;             //--> Read HTML contents
    server.send(200, "text/html", s); //--> Send web page
}

void handleTemp()
{
    server.send(200, "text/plane", temperature);
}

//--------------------------------------------------------------------------------void setup()
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    mySerial.begin(115200);
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
