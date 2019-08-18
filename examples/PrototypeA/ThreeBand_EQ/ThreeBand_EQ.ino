/***ThreeBand_EQ***/
// Three-band EQ control using 3 potentiometers : 3 analog pins

// Define & initialise analog pins and values 
int pot1 = A0, pot2 = A1, pot3 = A3;
int pot1val = 0, pot2val = 0, pot3val = 0;

void setup() {
  Serial.begin(115200); // baud rate
}

void loop() {
  // Read values for each pot and scale between unique number range
  pot1val = analogRead(pot1);
  pot1val = map(pot1val,0,1023,1,100);
  
  pot2val = analogRead(pot2);
  pot2val = map(pot2val,0,1023,101,200);
  
  pot3val = analogRead(pot3);
  pot3val = map(pot3val,0,1023,201,300);

  // Print all values to serial where Pd can understand via 'serial_print'
  Serial.println(pot1val);
  Serial.println(pot2val);
  Serial.println(pot3val);
}
