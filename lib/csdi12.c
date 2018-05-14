#include "csdi12.h"

void setState(SDI12_STATES state)
{
      switch (state)
  {
    case HOLDING:
    {
      pinMode(_dataPin,INPUT);      // added to make output work after pinMode to OUTPUT (don't know why, but works)
      pinMode(_dataPin,OUTPUT);     // Pin mode = output
      digitalWrite(_dataPin,LOW);   // Pin state = low
      setPinInterrupts(false);      // Interrupts disabled on data pin
      break;
    }
    case TRANSMITTING:
    {
      pinMode(_dataPin,INPUT);   // added to make output work after pinMode to OUTPUT (don't know why, but works)
      pinMode(_dataPin,OUTPUT);  // Pin mode = output
      setPinInterrupts(false);   // Interrupts disabled on data pin
      break;
    }
    case LISTENING:
    {
      digitalWrite(_dataPin,LOW);   // Pin state = low
      pinMode(_dataPin,INPUT);      // Pin mode = input
      interrupts();                 // Enable general interrupts
      setPinInterrupts(true);       // Enable Rx interrupts on data pin
      rxState = WAITING_FOR_START_BIT;
      break;
    }
    default:  // DISABLED or ENABLED
    {
      digitalWrite(_dataPin,LOW);   // Pin state = low
      pinMode(_dataPin,INPUT);      // Pin mode = input
      setPinInterrupts(false);      // Interrupts disabled on data pin
      break;
    }
  }
}