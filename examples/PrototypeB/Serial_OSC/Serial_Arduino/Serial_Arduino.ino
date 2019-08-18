/***Serial_Arduino***/
// A sketch for sending pot data via separate Serial communication

// SoftwareSerial library included with Arduino IDE by default
#include <SoftwareSerial.h>

// Create a serial bus communication between Arduino and ESP/NodeMCU, call it 's'
SoftwareSerial s(10, 11);
// RX is pin 10, connect to TX of ESP/NodeMCU
// Tx is pin 11, connect to RX of ESP/NodeMCU

// initialise potentiometer value and analog pin input
int pot1Val;
#define PIN1 A0

void setup(){
 s.begin(115200); // baudrate, ESP generally configured at 1115200 by default
}

void loop()
{
  // read in the pot value, scale it between 1 and 100 and print it to the serial bus 's'
  pot1Val = analogRead(PIN1);
  pot1Val = map(pot1Val, 0, 1023, 1, 100);
  s.println(pot1Val);
  //Serial.println(pot1Val); // uncomment here to check data is printing to Arduino Serial Monitor - troubleshooting
}
