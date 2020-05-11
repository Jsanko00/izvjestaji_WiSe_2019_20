#ifndef Radio_nRF_h
#define Radio_nRF_h

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

class RADIO
{
public:
    RADIO();
    ~RADIO();
    void nRF_init();
    bool RF_send(struct SensorData sensorData);
    void RF_receive(bool);
};

#endif