#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN 3
#define DHTTYPE DHT22

class SENSORS
{
public:
        SENSORS();
        ~SENSORS();
        void DHT_init();
        void BH1750_init();
        float readTemp();
        uint16_t readLight();
};

#endif