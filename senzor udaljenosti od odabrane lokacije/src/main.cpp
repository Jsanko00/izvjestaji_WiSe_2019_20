#include <MKRWAN.h>
#include <mainGPS.h>
#include <TinyGPS++.h>
#include "arduino_secrets.h" 
LoRaModem modem;

#define LPP_GPS 136 

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

bool connected;
int err_count;
int GPSBaud = 9600;
byte msg[2];


// Create a TinyGPS++ object
TinyGPSPlus gps;


// Create a software serial port called "gpsSerial"
//SoftwareSerial gpsSerial(RXPin, TXPin);
//SomeSerial gpsSerial(RXPin, TXPin);

void distance(location osoba,location lab){
  
  double sirina=(osoba.sirina-lab.sirina)*100000;
  double duzina=(osoba.duzina-lab.duzina)*100000;
  uint32_t udaljenost=sqrt(duzina*duzina+sirina*sirina);
  msg[0]=highByte(udaljenost);
  msg[1]=lowByte(udaljenost);

  Serial.println(udaljenost);

  
}



void displayInfo()
{
  if (gps.location.isValid())
  {
    osoba.duzina=gps.location.lng();
    osoba.sirina=gps.location.lat();
   
    distance(osoba,lab);

  }
  else
  {
    Serial.println("Location: Not Available");
  }
}
void setup() {
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  Serial1.begin(GPSBaud);
   modem.begin(EU868);
   delay(1000);      // apparently the murata dislike if this tempo is removed...
   connected=false;
   err_count=0;
}

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial1.available() > 0)
    if (gps.encode(Serial1.read()))
      displayInfo();
    
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }

  

   if ( !connected ) {
    int ret=modem.joinOTAA(appEui, appKey);
    if ( ret ) {
      connected=true;
      modem.minPollInterval(60);
      modem.dataRate(5);   // switch to SF7
      delay(100);          // because ... more stable
      err_count=0;
    }
  }
  if ( connected ) {

    
    int err=0;
    modem.beginPacket();
    modem.write(msg,2);
    err = modem.endPacket(true);
    if ( err <= 0 ) {
      // Confirmation not received - jam or coverage fault
      err_count++;
      if ( err_count > 50 ) {
        connected = false;

      }
      // wait for 2min for duty cycle with SF12 - 1.5s frame
     // for ( int i = 0 ; i < 120 ; i++ ) {
     //   delay(1000);
     // }
    } else {
      err_count = 0;
      // wait for 10s for duty cycle with SF7 - 55ms frame
      delay(10000);
    }
  }
}