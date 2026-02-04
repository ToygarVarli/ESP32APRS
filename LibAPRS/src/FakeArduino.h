#pragma once
#ifndef FakeArduino_h
#define FakeArduino_h

#include <Arduino.h>

#ifdef ARDUINO_ARCH_ESP32
    // ESP32 için ek tanımlar
    #include <stdint.h>
    #include <stdbool.h>
    
    // AVR uyumluluk makroları
    #ifndef _BV
        #define _BV(bit) (1 << (bit))
    #endif
    
    #ifndef BV
        #define BV(bit) _BV(bit)
    #endif
    
    // PROGMEM ESP32'de gerekli değil ama uyumluluk için tanımla
    #ifndef PROGMEM
        #define PROGMEM
    #endif
    
    #ifndef pgm_read_byte
        #define pgm_read_byte(addr) (*(const uint8_t *)(addr))
    #endif
    
    #ifndef pgm_read_word
        #define pgm_read_word(addr) (*(const uint16_t *)(addr))
    #endif
    
#else
    // AVR için gerekli include'lar
    #include <avr/pgmspace.h>
    #include <avr/interrupt.h>
    
    #ifndef _BV
        #define _BV(bit) (1 << (bit))
    #endif
    
    #ifndef BV
        #define BV(bit) _BV(bit)
    #endif
#endif

#endif // FakeArduino_h