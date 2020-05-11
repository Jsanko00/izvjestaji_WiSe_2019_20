#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

SENSORS::SENSORS() {}
SENSORS::~SENSORS() {}

void SENSORS::DHT_init()
{
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void SENSORS::BH1750_init()
{
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  Serial.println(F("BH1750 Test"));
}

float SENSORS::readTemp()
{
  delay(2000);

  float t;
  t = dht.readTemperature();

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F(" *C "));
  return t;
}

uint16_t SENSORS::readLight()
{
  uint16_t lux;
  lux = lightMeter.readLightLevel();
  Serial.print(F("Light: "));
  Serial.print(lux);
  Serial.println(F(" lx"));
  return lux;
}