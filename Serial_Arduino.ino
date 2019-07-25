#include <SoftwareSerial.h>

// Create a serial bus communication between Arduino and ESP/NodeMCU, called 's'
SoftwareSerial s(10, 11);
// RX is pin 10, connect to TX of ESP/NodeMCU
// Tx is pin 11, connect to RX of ESP/NodeMCU

int pot1Val;

#define PIN1 A0

void setup(){
 s.begin(115200); // faster baudrate, ESP generally configured at 115200 by default
}

void loop()
{
  // read in the pot value, scale it between 1 and 100 and print it to the serial bus 's'
  pot1Val = analogRead(PIN1);
  pot1Val = map(pot1Val, 0, 1023, 1, 100);
  s.println(pot1Val);
  //Serial.println(pot1Val); // uncomment here to check data is printing to Arduino Serial Monitor
}
