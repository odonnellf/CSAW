/*---------------------------------------------------------------------------------------------
  Open Sound Control (OSC) library for the ESP8266/ESP32
  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".
  This example code is in the public domain.
--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "eircom99788041";          // your network SSID (name)
char pass[] = "f505c593d372";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,1,5);        // remote IP of your computer
const unsigned int outPort = 8888;          // remote port to receive OSC
const unsigned int localPort = 9999;        // local port to listen for OSC packets (actually not used for sending)

int val;
int lastVal;

String placeString = "";


void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

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
    ; // wait for serial port to connect. Needed for native USB port only
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

        // if statement checks that the value is not equal to the last value sent
        // if it is then the pot/value hasn't changed, so don't send another OSC message
        // this prevents OSC message flooding to Pure Data
        if (val != lastVal) {
          // Create a new OSC message under /test moniker
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
