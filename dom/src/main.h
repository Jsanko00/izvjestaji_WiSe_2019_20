#ifndef main_h
#define main_h

// Payload that child sends to the parent
struct SensorData
{
    float temp;
    uint16_t lightLevel;
};

typedef enum
{
    READ_SERIAL,
    READ_SENSORS,
    SLEEP_STATE,
    RADIO_TX,
    RADIO_RX,
    NUM_STATES
} StateType;

#endif