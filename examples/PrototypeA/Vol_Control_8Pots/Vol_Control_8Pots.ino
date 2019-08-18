/***Vol_Control_8Pots***/
// Volume Control sketch for 8 potentiometers, scales all values and prints to Serial bus using println()

// Pot Analog Inputs
int pot[8] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Initialise number of pots, pot values and starting range variable
int NUM_POTS = 8;
int potVal[8] = {0,0,0,0,0,0,0,0};

int start = 101;

void setup() {
  Serial.begin(115200); // begin Serial comm. Baudrate = 115200 bits per second
}

void loop() {
  // Get readings from all pots via for loop
  for(int i = 0; i < NUM_POTS; i++){
    potVal[i] = analogRead(pot[i]);
    potVal[i] = map(potVal[i],0,1023,start,start+99);
    start = start+100; // Incremement for each iteration
  }

  // Print all values to Serial, could also include in previous loop
  for(int j = 0; j < NUM_POTS; j++){
    Serial.println(potVal[j]);
  }

  // Delay and reset starting range variable to start the loop again
  delay(500);
  start = 101;
}
