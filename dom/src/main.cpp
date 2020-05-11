#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
#include "Sensors.h"
#include "Radio_nRF.h"

SENSORS sensor;
RADIO radioNRF;
bool uspjeh;
SensorData dataToSend;
StateType state = READ_SERIAL;

void setup()
{
  Serial.begin(9600);
  sensor.DHT_init();
  sensor.BH1750_init();
  /* ######################
  ovdje pozovite funkciju koja instancira radio modul
  #########################
  */
 radioNRF.nRF_init();
}

void loop()
{

  switch (state)
  {
  case READ_SERIAL:

    state = READ_SENSORS;
    break;
  case READ_SENSORS:
    dataToSend.temp = sensor.readTemp();
    dataToSend.lightLevel = sensor.readLight();
    state = RADIO_TX;
    break;
  case RADIO_TX:
    /*#######################
    ovdje pozovite funkciju "RF_send" za slanje podataka preko radio kanala te rezultat pohranite u bool varijablu
    #########################
    */
   
   uspjeh=radioNRF.RF_send(dataToSend);
    state = RADIO_RX;

    break;
  case RADIO_RX:
    /*#######################
    ovdje pozovite funkciju "RF_receive" koja ispisuje poruku je li kom preko radija bila uspješna
    #########################
    */
  radioNRF.RF_receive(uspjeh);
    state = SLEEP_STATE;

    break;

  case SLEEP_STATE:

    delay(50);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    delay(50);

    state = READ_SERIAL;
    break;
  }
}
