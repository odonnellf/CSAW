/***Serial_ESP01***/
// A sketch for receiving pot values via Serial communication from Serial_Arduino
// and sending values as a test OSC message over WiFi

// Include appropriate WiFi and OSC library files
// See the CSAW README for details on installing
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "***Network_SSID**";          // your network SSID (name)
char pass[] = "***Network_Password";        // your network password

WiFiUDP Udp;                                // UDP instance to send and receive packets over UDP
const IPAddress outIp(192,168,1,1);        // remote IP of computer running Pd and DAW
const unsigned int outPort = 8888;          // remote port to receive OSC (port Pd is listening on)
const unsigned int localPort = 9999;        // local port to listen for OSC packets (actually not used for sending)

// Initialise variables to store pot value communicated over Serial,
// as well as the last variable sent and a placeholder string when reading over Serial
int val;
int lastVal;
String placeString = "";


void setup() {
    Serial.begin(115200); // baud rate

    // Connect to WiFi network
    // Adapted from CNMAT's Arduino OSC library example for sending messages using ESP8266
    // https://github.com/CNMAT/OSC/blob/master/examples/ESP8266sendMessage/ESP8266sendMessage.ino
    
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    // Repeateddly try connecting
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif
    
    while (!Serial) {
    ; // wait for serial port to connect. USB port only
  }
}

void loop() {
  // if there is a value available from the Serial bus
  if (Serial.available()) {
      // Read in the serial data to var serialChar
      int serialChar = Serial.read();
      if (isDigit(serialChar)) {
        // saved incoming data is a byte so convert this to a char and add it to placeholder string
        placeString += (char)serialChar;
      }
      
      // if you get a newline (i.e for each new value)
      if (serialChar == '\n') {
        // convert the placeholder string, it's now an integer!
        val = placeString.toInt();

        // if statement below checks that the value is not equal to the last value sent
        // if it is then the pot/value hasn't changed, so don't send another OSC message
        // this prevents OSC message flooding to Pure Data
        if (val != lastVal) {
          // Create a new OSC message under /test heading
          // Add the integer value and perform UDP packet operations
          OSCMessage msg("/test");
          msg.add(val);
          Udp.beginPacket(outIp, outPort);
          msg.send(Udp);
          Udp.endPacket();
          msg.empty();
        }
        // Set the lastVal to current value for next loop cycle and reset the placeholder string
        lastVal = val;
        placeString = "";
      }
  }
}
