/***OnePot_Compressor***/
// One knob compressor based on Yamaha MG series - one potentiometer controls compressor ratio, threshold and 

// Define and initialise pin and value
int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200); // baud rate
}

void loop() {
  // Read value, scale between 0 and 100 and send to serial
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 100);
  Serial.println(sensorValue);
}
