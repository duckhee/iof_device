/* =================================== Raspberry SDI-12 ======================= (James Coppock)
This SDI-12 library was originally authored by Kevin M. Smith for an Arduino based logger. It
has been modified by James Coppock for a Raspberry Pi based logger which according to the
attribution and licences section below is allowed. New SDI12 member functions have been written
for this Raspberry Pi implementation including:
- CRCheck()
- LFCheck()
- advanceBufferHead()
- overflowStatus()
- parityErrorStatus()
Modifications were done to the following member functions.
- setState() - setstate defines the state of four pins in this implementation. The
original implementation only defined the state of one data pin which
is possible because the Arduino digital pins are 5 volt which is
compatible with SDI-12.
- receiveChar() - Added a parity check
- writeChar() - Included an algorithm to add a parity bit.
Some of the section heading comments are the original authors and some are written by myself. I
have written the name of the author of the section heading comment in brackets at the top right
hand corner of major section heading. If the section heading comments are both my work and
Kevin’s my words and those of Kevin's are enclosed in brackets with either initials 'JMC:' or
'KMS:' at the beginning.
Where in function comments are my own or parts of the SDI12 class have been modified or new
functions included they are identified through out using my initials. Program modifications are
followed by a comment with my initial (JMC) at the beginning of the comment.
*/
/*================================= Arduino SDI-12 =============================== (Kevin Smith)
Arduino library for SDI-12 communications to a wide variety of environmental sensors. This
library provides a general software solution, without requiring any additional hardware.
============================= Original Attribution & License ===================== (Kevin Smith)
Copyright (C) 2013 Stroud Water Research Centre Available at
https://github.com/StroudCenter/Arduino-SDI-12
Authored initially in August 2013 by:
 Kevin M. Smith (http://ethosengineering.org)
 Inquiries: SDI12@ethosengineering.org
based on the SoftwareSerial library (formerly NewSoftSerial), authored by:
 ladyada (http://ladyada.net)
 Mikal Hart (http://www.arduiniana.org)
 Paul Stoffregen (http://www.pjrc.com)
 Garrett Mace (http://www.macetech.com)
 Brett Hagman (http://www.roguerobotics.com/)
This library is free software; you can redistribute it and/or modify it under the terms of the
GNU Lesser General Public License as published by the Free Software Foundation; either version
2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
the GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License along with this
library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301 USA
==================================== Code Organization ========================= (Kevin Smith)
0. Includes, Defines, & Variable Declarations
1. Buffer Setup
2. Data Line States, Overview of Interrupts
3. Constructor, Destructor, SDI12.begin(), and SDI12.end()
4. Waking up, and talking to, the sensors.
5. Reading from the SDI-12 object. available(), peek(), read(), flush()
6. Interrupt Service Routine (getting the data into the buffer)
*/
/* ===== 0. Includes, Defines, and Variable Declarations ======= (Kevin Smith and James Coppock)
(KMS:
 0.1 - Include the header file for this library.
 0.2 - defines the size of the buffer
 0.3 - defines value for DISABLED state
 0.4 - defines value for ENABLED state
 0.5 - defines value for DISABLED state
 0.6 - defines value for TRANSMITTING state
 0.7 - defines value for LISTENING state
)
(JMC: 0.8 - defines value for ENABLEINTERRUPT state.)
(KMS: 0.9 - Specifies the delay for transmitting bits. (JMC: 1200 Baud equates to 833us but
with system calls the actual time was measured using an oscilloscope to be
805us.)
)
(JMC: 0.10 to 0.13 are new reference variables.
 0.10 - a reference to the pin that connects to the SN74HCT240 output enable pin. This
pin puts the TX data pin on the output of the SN74HCT240 in a high impedance
state.)
 0.11 - a reference to the TX data pin. This pin is connected to an input of the
SN74HCT240.)
 0.12 - a reference to the pin that connects to one of the SN74HCT240 output enable
pin. This pin puts the output of the SN74HCT240 connected to the RX data pin of
the Pi in a high impedance state.)
0.13 - a reference to the RX data pin. This pin is connected to an output of the
SN74HCT240.)
)
(KMS: 0.14 - holds the buffer overflow status.)
(JMC: 0.15 - a new reference variable which holds the parity error status.
)
*/

#include <sdi12.h>

#define _BUFFER_SIZE 75 // 0.2 - max buffer size
#define DISABLED 0 // 0.3 value for DISABLED state
#define ENABLED 1 // 0.4 value for ENABLED state
#define HOLDING 2 // 0.5 value for DISABLED state
#define TRANSMITTING 3 // 0.6 value for TRANSMITTING state
#define LISTENING 4 // 0.7 value for LISTENING state
#define INTERRUPTENABLE 5 // (JMC: 0.8 value for ENABLEINTERRUPT state)
#define SPACING 805 // 0.9 bit timing in microseconds

uint8_t _txEnable;
uint8_t _txDataPin;
uint8_t _rxEnable;
uint8_t _rxDataPin;

bool _bufferOverflow;
bool _parityError;

typedef struct {
    char Buffer[_BUFFER_SIZE];
    int TailPointer;
    int HeadPointer;
}Queue;
  // For the various SDI12 states
  typedef enum SDI12_STATES
  {
    DISABLED = 0,
    ENABLED = 1,
    HOLDING = 2,
    TRANSMITTING = 3,
    LISTENING = 4
  } SDI12_STATES;

