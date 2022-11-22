/*
  DHCP-based IP printer

  This sketch uses the DHCP extensions to the Ethernet library
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

 */

#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoUniqueID.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0x2C 
};

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  Ethernet.init(11);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  SerialUSB.begin(9600);
  delay(3000);
  mac[4] = UniqueID8[6];
  mac[5] = UniqueID8[7];
  SerialUSB.print("Mac: ");
  for (size_t i = 0; i < 6; i++)
  {
    if (mac[i] < 0x10)
      SerialUSB.print("0");
    SerialUSB.print(mac[i], HEX);
    SerialUSB.print(" ");
  }
  SerialUSB.println();
  // start the Ethernet connection:
  SerialUSB.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    SerialUSB.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      SerialUSB.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      SerialUSB.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  SerialUSB.print("Mac: ");
  for (size_t i = 0; i < 6; i++)
  {
    if (mac[i] < 0x10)
      SerialUSB.print("0");
    SerialUSB.print(mac[i], HEX);
    SerialUSB.print(" ");
  }
  SerialUSB.println();
  // print your local IP address:
  SerialUSB.print("My IP address: ");
  SerialUSB.println(Ethernet.localIP());
}

void loop() {
  switch (Ethernet.maintain()) {
    case 1:
      //renewed fail
      SerialUSB.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      SerialUSB.println("Renewed success");
      //print your local IP address:
      SerialUSB.print("My IP address: ");
      SerialUSB.println(Ethernet.localIP());
      break;

    case 3:
      //rebind fail
      SerialUSB.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      SerialUSB.println("Rebind success");
      //print your local IP address:
      SerialUSB.print("My IP address: ");
      SerialUSB.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      break;
  }
}
