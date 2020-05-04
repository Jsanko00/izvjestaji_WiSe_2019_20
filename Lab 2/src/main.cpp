#include "sensors.h"





SENSORS sen;

int freeRam ();

void setup() {
  Serial.begin(9600);
  sen.BH1750_init();
sen.DHT_init();
}

void loop() {
  sen.readTempHum();
  sen.readLight();
    Serial.print(F("Free SRAM: "));
  Serial.print(freeRam());
  Serial.print(F(" bytes"));
}


int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}



