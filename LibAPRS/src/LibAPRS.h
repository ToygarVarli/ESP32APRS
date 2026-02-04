// #include "FakeArduino.h"
#include <stdint.h>
#include <stdbool.h>

#include "FIFO.h"
#include "CRC-CCIT.h"
#include "HDLC.h"
#include "AFSK.h"
#include "AX25.h"


#ifdef __cplusplus
extern "C"
{
#endif

void APRS_init(int reference, bool open_squelch);
void APRS_poll(void);

void APRS_setCallsign(char *call, int ssid);
void APRS_setDestination(char *call, int ssid);
void APRS_setMessageDestination(char *call, int ssid);
void APRS_setPath1(char *call, int ssid);
void APRS_setPath2(char *call, int ssid);

void APRS_setPreamble(unsigned long pre);
void APRS_setTail(unsigned long tail);
void APRS_useAlternateSymbolTable(bool use);
void APRS_setSymbol(char sym);

void APRS_setLat(char *lat);
void APRS_setLon(char *lon);
void APRS_setPower(int s);
void APRS_setHeight(int s);
void APRS_setGain(int s);
void APRS_setDirectivity(int s);

void APRS_sendPkt(void *_buffer, size_t length);
void APRS_sendLoc(void *_buffer, size_t length);
void APRS_sendMsg(void *_buffer, size_t length);
void APRS_msgRetry();

void APRS_printSettings();

// ESP32 için ADC kalibrasyon fonksiyonları
#ifdef ARDUINO_ARCH_ESP32
void APRS_setADCCenter(int center);      // Sessizlik ADC değeri (varsayılan 2020)
void APRS_setADCRange(int range);        // Sinyal ADC aralığı (varsayılan 1240)
void APRS_setSquelchThreshold(int thresh); // Squelch eşiği (varsayılan 200)
void APRS_calibrateADC(void);            // Otomatik kalibrasyon (5 sn sessizlik ölç)
#endif

//int freeMemory();


#ifdef __cplusplus
}
#endif