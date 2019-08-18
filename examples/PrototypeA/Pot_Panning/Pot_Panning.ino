/***Pot_Panning***/
// A simple potentiometer panning sketch - scales and writes pot data to Serial bus
// Exact same process as Volume Control

// Specify analog input pin and initialise its value
int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200); // Baudrate determines data rate in bits per second for serial transmission
}

void loop() {
  sensorValue = analogRead(sensorPin); // read pin value
  sensorValue = map(sensorValue, 0, 1023, 0, 100); // scale it between 0 and 100
  Serial.write(sensorValue); // write the value to serial
  delay(300); // arbitrary delay value to prevent message flooding
}
