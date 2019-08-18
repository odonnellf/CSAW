/***Transport_switches***/
// 3 button input switches that print specific numbers to serial on press for transport functionality

// Initialise pins used, state variable, previous reading variable and current reading
int chan1PIN = 2, state1 = LOW, previous1 = HIGH, reading1;
int chan2PIN = 3, state2 = LOW, previous2 = HIGH, reading2;
int chan3PIN = 4, state3 = LOW, previous3 = HIGH, reading3;

// Time variables for debouncing (ensures only a single signal is sent)
long time = 0, debounce = 200;

void setup()
{
  Serial.begin(115200); // baud rate
  pinMode(chan1PIN, INPUT); // set digital input channels to take in input
  pinMode(chan2PIN, INPUT);
  pinMode(chan3PIN, INPUT);
}

void loop()
{
  // read pin, toggle its state and print number to serial line
  // set time variable to time Arduino is active and change previous reading variable to current state for next time button is pressed
  reading1 = digitalRead(chan1PIN);
  if (reading1 == LOW && previous1 == HIGH && millis() - time > debounce) { Serial.println(0.91); time = millis(); }
  previous1 = reading1;

  reading2 = digitalRead(chan2PIN);
  if (reading2 == LOW && previous2 == HIGH && millis() - time > debounce) { Serial.println(0.92); time = millis(); }
  previous2 = reading2;

  reading3 = digitalRead(chan3PIN);
  if (reading3 == LOW && previous3 == HIGH && millis() - time > debounce) { Serial.println(0.93); time = millis(); }
  previous3 = reading3;
}
