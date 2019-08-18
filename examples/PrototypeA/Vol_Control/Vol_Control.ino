/***Vol_Control***/
// A simple volume control sketch - scales and writes pot data to Serial bus

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
  delay(300); // arbitrary delay to prevent message flooding
}
