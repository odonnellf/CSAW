/***PrototypeB_ESP***/
// Main ESP code for Prototype B - reads serial values from Arduino and sends to Pd over WiFi
// WiFi settings set to CSAW_router by default, if changing to other network make sure to change computer IP too
// Adapted from CNMAT OSC ESP8266 Send Message example: https://github.com/CNMAT/OSC/blob/master/examples/ESP8266sendMessage/ESP8266sendMessage.ino

// Include ESP8266 and OSC libraries
// For details on installing, refer to CSAW README file
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

// TP_Link router
char ssid[] = "CSAW_router";// your network SSID (name)
char pass[] = "c5@w_123!";  // your network password

WiFiUDP Udp; // UDP instance to send and receive packets over UDP
const IPAddress outIp(192,168,1,100);// remote IP of PC running Pd and DAW
const unsigned int outPort = 8888; // remote port to receive OSC
const unsigned int localPort = 9999; // local port to listen for OSC packets (actually not used for sending)

// Initialise variables to contain value read from Serial, last Serial value and placeholder string when reading from Serial
int val;
int lastVal;
String placeString = "";


void setup() {
    Serial.begin(115200); // baud rate - 1115200 is typical for ESP

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    // Continuously try connecting to network
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
    ; // wait for serial port to connect. Needed for USB port only
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

        // The if statement after this ones ensures that repeat values aren't sent, however we don't want this to happen for push buttons (will always be same value!)
        // This if statement checks if the value is a push button value and if it is, send the message every time
        if( val == 9991 || val == 9992 || val == 9993 || val == 9994 || val == 9995 || val == 9996 || val == 9997 || val == 9998 || val == 99991 || val == 99992 || val == 99993){
            OSCMessage msg("/esp");
            msg.add(val);
            Udp.beginPacket(outIp, outPort);
            msg.send(Udp);
            Udp.endPacket();
            msg.empty();
        } else {
        // if statement checks that the value is not equal to the last value sent
        // if it is then the pot/value hasn't changed, so don't send another OSC message
        // this prevents OSC message flooding to Pure Data
          if (val != lastVal) {
            // Create a new OSC message under /test moniker
            // Add the integer value and perform UDP packet operations
            OSCMessage msg("/esp");
            msg.add(val);
            Udp.beginPacket(outIp, outPort);
            msg.send(Udp);
            Udp.endPacket();
            msg.empty();
          }
        }
        // Set the lastVal to current value for next loop cycle and reset the placeholder string
        lastVal = val;
        placeString = "";
      }
  }
}
