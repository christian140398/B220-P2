#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <SPI.h>
#include "DHT.h"

//Test af loop
#define ONBOARD_LED 2

//Wifi
const char* ssid     = "Skousen";
const char* password = "Skou1234";

WiFiServer server(80);

//Deffiner tidszone
#define NTP_OFFSET  7200
#define NTP_INTERVAL 60 * 1000
#define NTP_ADDRESS  "1.dk.pool.ntp.org"
String Ur;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);


//Ledernes start tid og stop tid
String StartTid = "";
String StopTid =  "";
int Tilstand = 0;

//Pumpe
int PumpePin = 32;

//LED
int LedPin = 23;
int WifiLedOn = 22;
int WifiLedOff = 21;

//Hygrometer
int AnalogFugtPin1 = 36;
int AnalogFugtPin2 = 39;

//Print af valgte plante
String Besked = "";

//Planter
//PlanteFugt er i procent
//De tider der vælges for ledstrips skrives således "xx:xx"
//VarmePlante  er i grader
int KarseFugt = 10;
String StartTidKarse = "09:00";
String StopTidKarse = "16:00";
int VarmeKarse = 20;

int MynteFugt = 73;
String StartTidMynte = "08:00";
String StopTidMynte = "22:00";
int VarmeMynte = 15;


//SwitchCase
unsigned char Case;
int PlanteFugt;

//Temperatur
#define DHTPIN1 4
#define DHTPIN2 12
#define DHTTYPE DHT11
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
int VarmeTid;
float SetPoint; //Ønskede temp
bool HL = false;
int t1 = 0;
float DeltaT;

//Varmelement
int VarmePin = 19;


void setup()
{
  pinMode(PumpePin, OUTPUT);
  pinMode(VarmePin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(WifiLedOn, OUTPUT);
  pinMode(WifiLedOff, OUTPUT);
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(WifiLedOff, HIGH);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(WifiLedOn, HIGH);
  digitalWrite(WifiLedOff, LOW);

  dht1.begin();
  dht2.begin();
  timeClient.begin();
  server.begin();

}



void loop() {
  digitalWrite(ONBOARD_LED, HIGH);
  WiFiClient client = server.available();

  float Temp = TjekTemp();
  Klok();


  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {


          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            //Knapper og tekst sættes
            client.print("<br>");
            client.print( "Plante: " + Besked + "<br>" );

            int Fugt = TjekFugt();
            client.print("Fugtighed: ");
            client.print(Fugt);
            client.print("<br>");

            client.print("Temperatur: ");
            client.print(Temp);
            client.print("<br>");
            client.print("<br>");

            client.print("Start: <a href=\"/T\">here</a> <br>");
            client.print("Stop: <a href=\"/S\">here</a> <br>");
            client.print("Mynte: <a href=\"/M\">here</a> <br>");
            client.print("Karse: <a href=\"/K\">here</a> <br>");

            client.println();

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        //Knapperne kaldes
        if (currentLine.endsWith("GET /T")) {
          Besked = "Run";
          Case = 't';
        }
        if (currentLine.endsWith("GET /S")) {
          Besked = "Stop";
          Case = 's';
        }
        if (currentLine.endsWith("GET /M")) {
          Besked = "Mynte";
          Case = 'm';
          StartTid = StartTidMynte;
          StopTid = StopTidMynte;
          SetPoint = VarmeMynte;


        }
        if (currentLine.endsWith("GET /K")) {
          Besked = "Karse";
          Case = 'k';
          StartTid = StartTidKarse;
          StopTid = StopTidKarse;
          SetPoint = VarmeKarse;
        }
      }
    }
    client.stop();
    Serial.println(Case);
  }

  SwitchCase();

  if (Temp < (SetPoint - 1) && HL == false) {
    StyrTemp();

  }
  int t2 = millis();
  if (HL == true && (t2 - t1) > (VarmeTid * 1000)) {
    int tempDelay = (-7.375848115) * log((1.832057839) / ((4 * DeltaT) - 0.167942161)) * 1000;
    slukTemp(tempDelay);
  }

  digitalWrite(ONBOARD_LED, LOW);

  Print();

}
