
#ifndef mainGPS_h
#define mainGPS_h
#include<Arduino.h>

struct location{
double sirina;
double duzina;

};

location lab={43.511529,16.469366};
location osoba;
//byte msg;
int udaljenost(location osoba,location lab);

#endif