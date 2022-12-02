/*
 this program checks to see if it can Ping the Google DNS server and if the Ping fails
 'pingIP1failmax' times in a row if will turn relay 1 OFF for 10 seconds and then back ON.  It will 
 do a simlar thing with relay 2 if it cant Ping the HassIO server IP.

*/

#include <WiFi.h>
#include <ESP32Ping.h>
//#include <ESP8266Ping.impl.h>


// Update these with values suitable for your network.

const char* ssid = "Jeune bogoss";
const char* password = "ccomment";

const IPAddress remote_ip1(192,168,150,72);

WiFiClient espClient;

void setup() {
  pinMode(5, OUTPUT);     // Initialize the GPIO5 pin as an output
  pinMode(4, OUTPUT);     // Initialize the GPIO4 pin as an output
  digitalWrite(5, LOW);   // Turn GPIO5 on (Note that LOW is the voltage level
    // but actually the Relay is on; this is because
    // it is acive low on the ESP-01)
  digitalWrite(4, LOW);
  Serial.begin(115200);
  setup_wifi();

}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() { 
  Serial.print("Pinging docker host ");
  Serial.println(remote_ip1);

  if(Ping.ping(remote_ip1)){
    Serial.println("Success!!");
    delay(600);
  }
    else {
    Serial.println("Error :(");
    }
   
  digitalWrite(5, HIGH);   // Turn GPIO5 off
  delay(10);
  digitalWrite(5, LOW);   // Turn GPIO5 on

}