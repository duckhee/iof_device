#ifndef __CSDI12_H__
#define __CSDI12_H__

#include <stdint.h>

typedef enum __SDI12_STATES{
    DISABLE = 0,
    ENABLE = 1,
    HOLDING = 2,
    TRANSMITTING = 3,
    LISTENING = 4
} SDI12_STATES;

typedef enum __bool{
    false = 0,
    true = 1
} bool;

bool _bufferOverflow;

void begin();
void begin(uint8_t dataPin);
void end();
int TIMEOUT;
void setTimeoutValue(int value);
uint8_t getDataPin();

void forceHold();
void forceListen();
void sendCommand(String &cmd);



#endif