// Include LibAPRS
#include <LibAPRS.h>
#include "esp_system.h"
// You must define what reference voltage the ADC
// of your device is running at. If you bought a
// MicroModem from unsigned.io, it will be running
// at 3.3v if the "hw rev" is greater than 2.0.
// This is the most common. If you build your own
// modem, you should know this value yourself :)
#define ADC_REFERENCE REF_3V3
// OR
//#define ADC_REFERENCE REF_5V

// You can also define whether your modem will be
// running with an open squelch radio:
#define OPEN_SQUELCH false

// You always need to include this function. It will
// get called by the library every time a packet is
// received, so you can process incoming packets.
//
// If you are only interested in transmitting, you
// should just leave this function empty.
// 
// IMPORTANT! This function is called from within an
// interrupt. That means that you should only do things
// here that are FAST. Don't print out info directly
// from this function, instead set a flag and print it
// from your main loop, like this:

boolean gotPacket = false;
AX25Msg incomingPacket;
uint8_t *packetData;
extern "C" void aprs_msg_callback(struct AX25Msg *msg) {
  // If we already have a packet waiting to be
  // processed, we must drop the new one.
  if (!gotPacket) {
    // Set flag to indicate we got a packet
    gotPacket = true;

    // The memory referenced as *msg is volatile
    // and we need to copy all the data to a
    // local variable for later processing.
    memcpy(&incomingPacket, msg, sizeof(AX25Msg));

    // We need to allocate a new buffer for the
    // data payload of the packet. First we check
    // if there is enough free RAM.
    if (freeMemoryE() > msg->len) {
      packetData = (uint8_t*)malloc(msg->len);
      memcpy(packetData, msg->info, msg->len);
      incomingPacket.info = packetData;
    } else {
      // We did not have enough free RAM to receive
      // this packet, so we drop it.
      gotPacket = false;
    }
  }
}

uint32_t freeMemoryE() {
  return ESP.getFreeHeap();   // byte cinsinden boş heap
}

void setup() {
  // Set up serial port
  Serial.begin(115200);
  
  APRS_init(ADC_REFERENCE, OPEN_SQUELCH);
  APRS_setCallsign("NOCALL", 1);
  
  // Manuel ADC kalibrasyon (isteğe bağlı)
  // 1.63V / 3.3V * 4095 = ~2020
  APRS_setADCCenter(1875);
    APRS_setSquelchThreshold(400); // Gürültüden yüksek

  // Veya otomatik kalibrasyon (radyo sessizken çalıştır)
  // APRS_calibrateADC();
  
  APRS_printSettings();
  Serial.print(F("Free RAM:     ")); Serial.println(freeMemoryE());
}

void locationUpdateExample() {
  // Let's first set our latitude and longtitude.
  // These should be in NMEA format!
  APRS_setLat("5530.80N");
  APRS_setLon("01143.89E");
  
  // We can optionally set power/height/gain/directivity
  // information. These functions accept ranges
  // from 0 to 10, directivity 0 to 9.
  // See this site for a calculator:
  // http://www.aprsfl.net/phgr.php
  // LibAPRS will only add PHG info if all four variables
  // are defined!
  APRS_setPower(2);
  APRS_setHeight(4);
  APRS_setGain(7);
  APRS_setDirectivity(0);
  
  // We'll define a comment string
  char *comment = "LibAPRS location update";
    
  // And send the update
  APRS_sendLoc(comment, strlen(comment));
  
}

void messageExample() {
  // We first need to set the message recipient
  APRS_setMessageDestination("AA3BBB", 0);
  
  // And define a string to send
  char *message = "Hi there! This is a message.";
  APRS_sendMsg(message, strlen(message));
  
}

// Here's a function to process incoming packets
// Remember to call this function often, so you
// won't miss any packets due to one already
// waiting to be processed
void processPacket() {
  if (gotPacket) {
    gotPacket = false;
    
    Serial.print(F("Received APRS packet. SRC: "));
    Serial.print(incomingPacket.src.call);
    Serial.print(F("-"));
    Serial.print(incomingPacket.src.ssid);
    Serial.print(F(". DST: "));
    Serial.print(incomingPacket.dst.call);
    Serial.print(F("-"));
    Serial.print(incomingPacket.dst.ssid);
    Serial.print(F(". Data: "));

    for (int i = 0; i < incomingPacket.len; i++) {
      Serial.write(incomingPacket.info[i]);
    }
    Serial.println("");

    // Remeber to free memory for our buffer!
    free(packetData);

    // You can print out the amount of free
    // RAM to check you don't have any memory
    // leaks
    // Serial.print(F("Free RAM: ")); Serial.println(freeMemory());
  }
}

boolean whichExample = false;
void loop() {
  
 /* delay(1000);
  if (whichExample) {
    locationUpdateExample();
  } else {
    messageExample();
  }
  whichExample ^= true;*/
//Serial.println(analogRead(36));
  // APRS_poll() MUST be called frequently for the modem to decode packets!
  // This is the main function that processes incoming audio samples
  APRS_poll();
  
  processPacket();
}
