/***PrototypeB***/
// Main Arduino Prototype B sketch for CSAW controller, using CD4051BE muxes
// Scales all pot values and responds to push buttons, printing to serial bus with ESP8266

// SoftwareSerial library included with Arduino IDE
#include <SoftwareSerial.h>
SoftwareSerial s(15, 14); // Arduino RX pin is 15, TX is 14

// Initialise values for each analog input and old values to compare with later before sending
// (if new value is 1 above or 1 below old value - i.e. regular pot jitter - then it won't be sent)
int input1Values[7], input1OldValues[7];
int input2Values[7], input2OldValues[7];
int input3Values[7], input3OldValues[7];
int input4Values[7], input4OldValues[7];
int input5Values[7], input5OldValues[7];
int input6Values[7], input6OldValues[7];
int input7Values[7], input7OldValues[7];
int input8Values[7], input8OldValues[7];
int masterVol, masterOldVol;
int sendVol, sendOldVol;

// Initialise all mux pins
const int mux1Pins[3] = {2, 3, 4}; // S0=2, S1=3, S2=4
const int mux2Pins[3] = {5, 6, 7}; // etc.
const int mux3Pins[3] = {8, 9, 10};
const int mux4Pins[3] = {11, 12, 13};
const int mux5Pins[3] = {22, 23, 24};
const int mux6Pins[3] = {26, 27, 28};
const int mux7Pins[3] = {30, 31, 32};
const int mux8Pins[3] = {34, 35, 36};

// Mux connections to Arduino analog inputs
const int mux1Input = A1; // Connect common OUT of Mux 1 to A1 (A0 is master vol and A9 is send vol)
const int mux2Input = A2; // etc.
const int mux3Input = A3;
const int mux4Input = A4;
const int mux5Input = A5;
const int mux6Input = A6;
const int mux7Input = A7;
const int mux8Input = A8;

// Button pin connections and state variables/previous reading/current reading
int mute1PIN = 41, state1 = LOW, previous1 = HIGH, reading1;
int mute2PIN = 42, state2 = LOW, previous2 = HIGH, reading2;
int mute3PIN = 43, state3 = LOW, previous3 = HIGH, reading3;
int mute4PIN = 44, state4 = LOW, previous4 = HIGH, reading4;
int mute5PIN = 45, state5 = LOW, previous5 = HIGH, reading5;
int mute6PIN = 46, state6 = LOW, previous6 = HIGH, reading6;
int mute7PIN = 47, state7 = LOW, previous7 = HIGH, reading7;
int mute8PIN = 48, state8 = LOW, previous8 = HIGH, reading8;
int recPIN = 50, stateR = LOW, previousR = HIGH, readingR;
int playPIN = 51, stateP = LOW, previousP = HIGH, readingP;
int stopPIN = 52, stateS = LOW, previousS = HIGH, readingS;

// Starting variable for pot ranges and debouncing variables for push buttons
int start = 101;
long time = 0, debounce = 200;

void setup() 
{
  // Initialize the serial port with baud rate of 115200 bits per second
  s.begin(115200);
  
  // Set up the mux pins as outputs and write HIGH to each  to initialise
  for (int i=0; i<3; i++)
  {
    pinMode(mux1Pins[i], OUTPUT);
    pinMode(mux2Pins[i], OUTPUT);
    pinMode(mux3Pins[i], OUTPUT);
    pinMode(mux4Pins[i], OUTPUT);
    pinMode(mux5Pins[i], OUTPUT);
    pinMode(mux6Pins[i], OUTPUT);
    pinMode(mux7Pins[i], OUTPUT);
    pinMode(mux8Pins[i], OUTPUT);
    digitalWrite(mux1Pins[i], HIGH);
    digitalWrite(mux2Pins[i], HIGH);
    digitalWrite(mux3Pins[i], HIGH);
    digitalWrite(mux4Pins[i], HIGH);
    digitalWrite(mux5Pins[i], HIGH);
    digitalWrite(mux6Pins[i], HIGH);
    digitalWrite(mux7Pins[i], HIGH);
    digitalWrite(mux8Pins[i], HIGH);
  }

  // Set up all analog pins to read inputs
  pinMode(mux1Input, INPUT);
  pinMode(mux2Input, INPUT);
  pinMode(mux3Input, INPUT);
  pinMode(mux4Input, INPUT);
  pinMode(mux5Input, INPUT);
  pinMode(mux6Input, INPUT);
  pinMode(mux7Input, INPUT);
  pinMode(mux8Input, INPUT);

  // Set up all digital push button pins to read inputs
  pinMode(mute1PIN, INPUT);
  pinMode(mute2PIN, INPUT);
  pinMode(mute3PIN, INPUT);
  pinMode(mute4PIN, INPUT);
  pinMode(mute5PIN, INPUT);
  pinMode(mute6PIN, INPUT);
  pinMode(mute7PIN, INPUT);
  pinMode(mute8PIN, INPUT);
  pinMode(recPIN, INPUT);
  pinMode(playPIN, INPUT);
  pinMode(stopPIN, INPUT);
}

void loop() 
{
  //***POTENTIOMETERS***//
  
  // Loop through first seven of the eight mux pins
  for (byte pin=0; pin<=6; pin++)
  {
    selectMuxPin(mux1Pins, pin); // Select one at a time
    input1Values[pin] = analogRead(mux1Input); // Read OUT
    input1Values[pin] = map(input1Values[pin], 0, 1023, start, start+99); // Scale it to range
    if(input1Values[pin] < (input1OldValues[pin]-1) || input1Values[pin] > (input1OldValues[pin]+1)) { // if new pot value is more than 1 above or 1 below last value
      s.println(input1Values[pin]); // Print to serial
      input1OldValues[pin] = input1Values[pin]; // Set old value to equal current value for next loop
    }

    selectMuxPin(mux2Pins, pin);
    input2Values[pin] = analogRead(mux2Input);
    input2Values[pin] = map(input2Values[pin], 0, 1023, start+100, start+199);
    if(input2Values[pin] < (input2OldValues[pin]-1) || input2Values[pin] > (input2OldValues[pin]+1)) {
      s.println(input2Values[pin]);
      input2OldValues[pin] = input2Values[pin];
    }

    selectMuxPin(mux3Pins, pin);
    input3Values[pin] = analogRead(mux3Input);
    input3Values[pin] = map(input3Values[pin], 0, 1023, start+200, start+299);
    if(input3Values[pin] < (input3OldValues[pin]-1) || input3Values[pin] > (input3OldValues[pin]+1)) {
      s.println(input3Values[pin]);
      input3OldValues[pin] = input3Values[pin];
    }

    selectMuxPin(mux4Pins, pin);
    input4Values[pin] = analogRead(mux4Input);
    input4Values[pin] = map(input4Values[pin], 0, 1023, start+300, start+399);
    if(input4Values[pin] < (input4OldValues[pin]-1) || input4Values[pin] > (input4OldValues[pin]+1)) {
      s.println(input4Values[pin]);
      input4OldValues[pin] = input4Values[pin];
    }
       
    selectMuxPin(mux5Pins, pin);
    input5Values[pin] = analogRead(mux5Input);
    input5Values[pin] = map(input5Values[pin], 0, 1023, start+400, start+499);
    if(input5Values[pin] < (input5OldValues[pin]-1) || input5Values[pin] > (input5OldValues[pin]+1)) {
      s.println(input5Values[pin]);
      input5OldValues[pin] = input5Values[pin];
    }

    selectMuxPin(mux6Pins, pin);
    input6Values[pin] = analogRead(mux6Input);
    input6Values[pin] = map(input6Values[pin], 0, 1023, start+500, start+599);
    if(input6Values[pin] < (input6OldValues[pin]-1) || input6Values[pin] > (input6OldValues[pin]+1)) {
      s.println(input6Values[pin]);
      input6OldValues[pin] = input6Values[pin];
    }

    selectMuxPin(mux7Pins, pin);
    input7Values[pin] = analogRead(mux7Input);
    input7Values[pin] = map(input7Values[pin], 0, 1023, start+600, start+699);
    if(input7Values[pin] < (input7OldValues[pin]-1) || input7Values[pin] > (input7OldValues[pin]+1)) {
      s.println(input7Values[pin]);
      input7OldValues[pin] = input7Values[pin];
    }

    selectMuxPin(mux8Pins, pin);
    input8Values[pin] = analogRead(mux8Input);
    input8Values[pin] = map(input8Values[pin], 0, 1023, start+700, start+799);
    if(input8Values[pin] < (input8OldValues[pin]-1) || input8Values[pin] > (input8OldValues[pin]+1)) {
      s.println(input8Values[pin]);
      input8OldValues[pin] = input8Values[pin];
    }
    
    start = start+1000; // Increment start variable by 1000 for next channel 'row' (Row1 = volume, row2 = panning, etc.)
  }

  //***PUSH BUTTONS***//

  // Read pin, change state based on previous value and debounce
  // Set new time variable and set new previous value to current pin reading
  reading1 = digitalRead(mute1PIN);
  if (reading1 == LOW && previous1 == HIGH && millis() - time > debounce) { s.println(9991); time = millis(); }
  previous1 = reading1;

  reading2 = digitalRead(mute2PIN);
  if (reading2 == LOW && previous2 == HIGH && millis() - time > debounce) { s.println(9992); time = millis(); }
  previous2 = reading2;

  reading3 = digitalRead(mute3PIN);
  if (reading3 == LOW && previous3 == HIGH && millis() - time > debounce) { s.println(9993); time = millis(); }
  previous3 = reading3;

  reading4 = digitalRead(mute4PIN);
  if (reading4 == LOW && previous4 == HIGH && millis() - time > debounce) { s.println(9994); time = millis(); }
  previous4 = reading4;

  reading5 = digitalRead(mute5PIN);
  if (reading5 == LOW && previous5 == HIGH && millis() - time > debounce) { s.println(9995); time = millis(); }
  previous5 = reading5;

  reading6 = digitalRead(mute6PIN);
  if (reading6 == LOW && previous6 == HIGH && millis() - time > debounce) { s.println(9996); time = millis(); }
  previous6 = reading6;

  reading7 = digitalRead(mute7PIN);
  if (reading7 == LOW && previous7 == HIGH && millis() - time > debounce) { s.println(9997); time = millis(); }
  previous7 = reading7;

  reading8 = digitalRead(mute8PIN);
  if (reading8 == LOW && previous8 == HIGH && millis() - time > debounce) { s.println(9998); time = millis(); }
  previous8 = reading8;

  readingR = digitalRead(recPIN);
  if (readingR == LOW && previousR == HIGH && millis() - time > debounce) { s.println(99991); time = millis(); }
  previousR = readingR;

  readingP = digitalRead(playPIN);
  if (readingP == LOW && previousP == HIGH && millis() - time > debounce) { s.println(99992); time = millis(); }
  previousP = readingP;

  readingS = digitalRead(stopPIN);
  if (readingS == LOW && previousS == HIGH && millis() - time > debounce) { s.println(99993); time = millis(); }
  previousS = readingS;

  //***MASTER AND SEND VOLUMES***//
  masterVol = analogRead(A0); // Read OUT
  masterVol = map(masterVol, 0, 1023, 1, 100); // Scale it to range
  if(masterVol < (masterOldVol-1) || masterVol > (masterOldVol+1)){ // same check against old value
    s.println(masterVol);
    masterOldVol = masterVol;
  }
  
  sendVol = analogRead(A9);
  sendVol = map(sendVol, 0, 1023, 901, 1000);
  if(sendVol < (sendOldVol-1) || sendVol > (sendOldVol+1)){
    s.println(sendVol);
    sendOldVol = sendVol;
  }
    
  delay(100); // delay based on noticeable latency to humans, >100ms is noticeable, could potentially be scaled back but is a safe value
  start = 101; // reset start value before running through muxes again
}

// Function sets the S0, S1, and S2 pins, given a mux pin from 0 to 7
// writes HIGH and LOW to select pins for each input
void selectMuxPin(int muxPins[], byte pin)
{
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(muxPins[i], HIGH);
    else
      digitalWrite(muxPins[i], LOW);
  }
}
