#ifndef __SDI12_H__
#define __SDI12_H__

#include <string>
#include <errorno.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>
#include <wiringPi.h>

class SDI12 {
private:
 static void setState(uint8_t state); // set the state of the SDI12 objects
 void wakeSensors(); // Used to wake up all sensors on the SDI12 bus
 void writeChar(uint8_t out); // sends a char out on the data line
 static inline void receiveChar(); // used by the ISR to grab a char from data line

public:
 SDI12(uint8_t txEnable, uint8_t txDataPin, uint8_t rxEnable, uint8_t rxDataPin);
  //constructor
 ~SDI12(); // destructor
 void begin(); // enable SDI-12 object
 static void end(); // disable SDI-12 object
 void forceHold(); // sets line state to HOLDING
 void sendCommand(std::string cmd); // sends the String cmd out on the data line
 bool overflowStatus(); // (JMC: returns the overflow status)
 bool parityErrorStatus(); // (JMC: returns parity error status)
 int available(); // returns the number of bytes available in buffer
 bool LFCheck(); // (JMC: Checks the last character in the buffer is a <LF>)
 bool CRCheck(); // (JMC: Checks the last character in the buffer is a <CR>)
 int peek(); // reveals next byte in buffer without consuming)
 void flush(); // resets the circular buffer head and tail, resets the Overflow and parity error status
 int read(); // returns next byte in the buffer (consumes)
 void advanceBufHead(int advance); // (JMC: advance the buffer head)
 static inline void handleInterrupt(); // intermediary ISR function
};

#endif