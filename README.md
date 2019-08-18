# CSAW
(C)ontrol (S)urface using (A)rduino (W)ireless capabilities

Audio control surfaces are practical tools for editing and mixing in a digital audio workstation. Despite recent technological advancements, however, there is a lack of robust physical commercial controllers with seamless wireless functionality.

This project folder/repository consists of relevant files for the design and implementation of CSAW – an audio Control Surface built using the Arduino platform and Wireless capabilities.

CSAW aims to remedy limitations of mobile control applications and certain hardware controllers through devising a proof of concept control surface and software platform using sophisticated open-source applications and wireless communication protocols.

***This project is presented as part of the thesis requirements for the MSc. in Music & Technology, awarded by Cork School of Music.***


Software, Drivers & Libraries
=============================
(Installations covered in notes below)
-> Arduino IDE
-> Arduino Mega driver 
-> ESP8266 board and library for Arduino IDE
-> Purr Data - Pure Data distribution
-> CNMAT/OSC Arduino library
-> Arduino_Pd Pd abstraction library


Repository/Folder Structure:
============================
/
-> camera/ 		: various pictures of circuits, code, controller design etc.
-> daw-files/	: DAW config files and templates for CSAW
-> design/		: design diagrams and other documents
-> documents/	: main thesis submission documents
-> examples/	: example Arduino sketches and Pd patches, referenced in documentation
-> main/		: main CSAW prototype Arduino sketches and Pd patches


Install Notes
=============
- A Quick Start Guide accompanies this README with details on getting the controller working instantly (QuickStart.pdf). The steps below outline the process to replicate development, install requirements to enable code expansion on the controller and how to change the prototype build.

I. Arduino:
	1. Download the Arduino IDE and install: https://www.arduino.cc/en/main/software .
	2. Connect CSAW's Arduino component via USB. Ensure that the correct board is selected in the IDE: Tools->Board->Arduino/Genuino Mega or Mega 2560
	3. Check that the correct port is selected under: Tools->Port. If this is greyed out, check that the Arduino is fully plugged in. If it is then there may be a driver issue, as Arduino Mega is known to have certain issues, particularly with Windows 10. Follow Arduino's documentation how to resolve this: https://www.arduino.cc/en/Guide/DriverInstallation 
	4. Prototype sketches and other code can now be uploaded to Arduino.

II. ESP8266 (WiFi chip) board & library:
	1. To add the ESP8266 board manager and library, first go to: File->Preferences in the IDE.
	2. Paste the following link into the "Additional Boards Manager URLs" field and click OK: http://arduino.esp8266.com/stable/package_esp8266com_index.json
	3. Go to Tools->Board->Board Manager and search for 'ESP8266'. Select 'Install' and restart the IDE once it finishes.
	4. Sketches can now be uploaded to ESP8266 modules. Connect the module/device via USB.
	5. Select the appropriate board in the Tools->Board menu (for ESP-01 this is just 'Generic ESP8266 Module) and select the COM port.
	6. The library includes some examples to test the module works - e.g. Blink, etc.

III. Open Sound Control library:
	1. Navigate to the main OSC GitHub repo for Arduino developed by CNMAT and download as a zip file: https://github.com/CNMAT/OSC .
	2. In the Arduino IDE, go to: Sketch->Include Library->Add .ZIP Library . Select the OSC zip and click OK.
	3. Once it finishes installing, restart the IDE. Under File->Examples, there should now be some extra examples under the OSC umbrella in the 'Examples from Custom Libraries' section.

IV. Purr Data and abstractions
	1. CSAW uses the 'Purr Data' distribution of Pure Data. Download and install it from the GitHub repo at the following link: https://github.com/agraef/purr-data/releases .
	2. Download the 'Arduino_Pd' abstraction library: https://github.com/alexdrymonitis/Arduino_Pd .
	3. CSAW's Prototype A patch and examples use this library's 'serial_print.pd' patch for correctly reading values printed to Serial from Arduino. Copy this file into any directory with CSAW Pd code.

V. CSAW:
	1. Download this project repository. Refer to the folder structure above for further details.
	2. Arduino and ESP sketches can now be easily uploaded via USB.
	3. Run the appropriate Prototype patch. For PrototypeA, select the USB COM port Arduino is connected to. For PrototypeB, wait for ESP to connect to Pd.
	4. Ensure that the patch is responding to controller actions.

VI. DAW:
	(***For wireless/PrototypeB, connect to the network defined by the ESP8266 sketch and ensure the PC has the defined IP address.***)
	1. Open a supported DAW and import the config file. Alternatively, open the DAW template.
	2. This will contain all tracks, plugins/FX, OSC control surface and mappings, etc. Double-check that the port matches the settings in the Prototype Pd patch.
	3. Check once more that actions are being mapped in the Prototype patch and then click the DAW connect button.


System Requirements:
====================
- This system was developed and tested on a Dell Inspiron laptop with the following specifications:
	* Intel Core i7-8565U CPU @ 1.80GHz 1.99 GHz
	* 16.0GB installed memory (RAM)
	* Windows 10 Pro Operating System
