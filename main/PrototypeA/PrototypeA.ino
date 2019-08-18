/***PrototypeA***/
// Main Arduino Prototype A sketch for CSAW controller, using CD4051BE muxes
// Scales all pot values and responds to push buttons, printing to Serial bus using println()

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
const int mux1Input = A1; // Connect common OUT of Mux 1 to A1 (A0 used for master)
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
  Serial.begin(115200);
  
  // Set up the select pins as outputs and write HIGH values to all to initialise
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

  // Set up all analog pins to read inputs from muxes
  pinMode(mux1Input, INPUT);
  pinMode(mux2Input, INPUT);
  pinMode(mux3Input, INPUT);
  pinMode(mux4Input, INPUT);
  pinMode(mux5Input, INPUT);
  pinMode(mux6Input, INPUT);
  pinMode(mux7Input, INPUT);
  pinMode(mux8Input, INPUT);

  // Set up all button pins to read inputs
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
  
  // Loop through first seven of the eight mux pins {0,1,2,3,4,5,6}
  for (byte pin=0; pin<=6; pin++)
  {
    selectMuxPin(mux1Pins, pin); // Select one at a time
    int inputValue = analogRead(mux1Input); // Read OUT
    inputValue = map(inputValue, 0, 1023, start, start+99); // Scale it to range
    Serial.println(inputValue); // Print to serial***/
    
    selectMuxPin(mux2Pins, pin);
    inputValue = analogRead(mux2Input);
    inputValue = map(inputValue, 0, 1023, start+100, start+199);
    Serial.println(inputValue);

    selectMuxPin(mux3Pins, pin);
    inputValue = analogRead(mux3Input);
    inputValue = map(inputValue, 0, 1023, start+200, start+299);
    Serial.println(inputValue);

    selectMuxPin(mux4Pins, pin);
    inputValue = analogRead(mux4Input);
    inputValue = map(inputValue, 0, 1023, start+300, start+399);
    Serial.println(inputValue);
       
    selectMuxPin(mux5Pins, pin);
    inputValue = analogRead(mux5Input);
    inputValue = map(inputValue, 0, 1023, start+400, start+499);
    Serial.println(inputValue);

    selectMuxPin(mux6Pins, pin);
    inputValue = analogRead(mux6Input);
    inputValue = map(inputValue, 0, 1023, start+500, start+599);
    Serial.println(inputValue);

    selectMuxPin(mux7Pins, pin);
    inputValue = analogRead(mux7Input);
    inputValue = map(inputValue, 0, 1023, start+600, start+699);
    Serial.println(inputValue);

    selectMuxPin(mux8Pins, pin);
    inputValue = analogRead(mux8Input);
    inputValue = map(inputValue, 0, 1023, start+700, start+799);
    Serial.println(inputValue);
    
    start = start+1000; // Increment start by 1000 to move onto next 'row' for each channel strip
                        // Row1 = Volume, Row2 = Pan, etc.
  }

  //***PUSH BUTTONS***//

  // Read pin, change state based on previous value and debounce
  // Set new time variable and set new previous value to current pin reading
  // floats used for consistency and so as to not clash with other number ranges
  reading1 = digitalRead(mute1PIN);
  if (reading1 == LOW && previous1 == HIGH && millis() - time > debounce) { Serial.println(0.1); time = millis(); }
  previous1 = reading1;

  reading2 = digitalRead(mute2PIN);
  if (reading2 == LOW && previous2 == HIGH && millis() - time > debounce) { Serial.println(0.2); time = millis(); }
  previous2 = reading2;

  reading3 = digitalRead(mute3PIN);
  if (reading3 == LOW && previous3 == HIGH && millis() - time > debounce) { Serial.println(0.3); time = millis(); }
  previous3 = reading3;

  reading4 = digitalRead(mute4PIN);
  if (reading4 == LOW && previous4 == HIGH && millis() - time > debounce) { Serial.println(0.4); time = millis(); }
  previous4 = reading4;

  reading5 = digitalRead(mute5PIN);
  if (reading5 == LOW && previous5 == HIGH && millis() - time > debounce) { Serial.println(0.5); time = millis(); }
  previous5 = reading5;

  reading6 = digitalRead(mute6PIN);
  if (reading6 == LOW && previous6 == HIGH && millis() - time > debounce) { Serial.println(0.6); time = millis(); }
  previous6 = reading6;

  reading7 = digitalRead(mute7PIN);
  if (reading7 == LOW && previous7 == HIGH && millis() - time > debounce) { Serial.println(0.7); time = millis(); }
  previous7 = reading7;

  reading8 = digitalRead(mute8PIN);
  if (reading8 == LOW && previous8 == HIGH && millis() - time > debounce) { Serial.println(0.8); time = millis(); }
  previous8 = reading8;

  readingR = digitalRead(recPIN);
  if (readingR == LOW && previousR == HIGH && millis() - time > debounce) { Serial.println(0.91); time = millis(); }
  previousR = readingR;

  readingP = digitalRead(playPIN);
  if (readingP == LOW && previousP == HIGH && millis() - time > debounce) { Serial.println(0.92); time = millis(); }
  previousP = readingP;

  readingS = digitalRead(stopPIN);
  if (readingS == LOW && previousS == HIGH && millis() - time > debounce) { Serial.println(0.93); time = millis(); }
  previousS = readingS;

  //***MASTER & SEND***//
  
  int masterVol = analogRead(A0); // Read OUT
  masterVol = map(masterVol, 0, 1023, 0, 100); // Scale it to range
  Serial.println(masterVol);

  int sendVol = analogRead(A9);
  sendVol = map(sendVol, 0, 1023, 901, 1000);
  Serial.println(sendVol);
  
  Serial.println();
  delay(100); // Give a little bit of a delay, >100ms is noticeable latency for humans. This could probably be scaled back
  start = 101; // Reset start variable before running through mux inputs again
}

// Function sets the S0, S1, and S2 pins, given mux pin from 0 to 7
// Writes HIGH and LOW to select pins
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
