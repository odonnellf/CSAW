/***Channel_Strip***/
// Channel Strip sketch for 7 potentiometers, using a CD4051BE multiplexer
// Sketch scales all mux input values and scales & prints to Serial bus using println()

// Multiplexer select pins and analog output pin
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zInput = A0; // Connect common (Z) to A0 (analog input)

// Initialises the starting number range variable for the first potentiometer (101 to 200)
int start = 101;

void setup() 
{
  Serial.begin(115200); // Initialize the serial port
  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input
}

void loop() 
{
  // Loop through first seven of the eight pins.
  for (byte pin=0; pin<=6; pin++)
  {
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(A0); // and read Z
    inputValue = map(inputValue, 0, 1023, start, start+99);  // map the value a range
    Serial.println(inputValue); // Print numerical value to Serial where Pd will interpret it
    start = start+1000; // Next pot range on the strip is 1101 to 2000, 2101 to 3000 etc
  }
  Serial.println();
  delay(100);
  start = 101; // Reset start variable for next loop through all mux values
}

// function sets the S0, S1, and S2 pins, given the pin number from 0 to 7 (or 0 to 6 in this case)
// writes HIGH and LOW voltages to the appropriate select pins
void selectMuxPin(byte pin)
{
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
