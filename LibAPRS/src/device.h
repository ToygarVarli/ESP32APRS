#include "constants.h"

#ifndef DEVICE_CONFIGURATION
#define DEVICE_CONFIGURATION

#ifdef ARDUINO_ARCH_ESP32
    // ESP32 - AVR port tanımlarına gerek yok
    #define F_CPU 240000000
    #define FREQUENCY_CORRECTION 0
#else
    // AVR CPU settings
    #ifndef TARGET_CPU
        #define TARGET_CPU m328p
    #endif

    #ifndef F_CPU
        #define F_CPU 16000000
    #endif

    #ifndef FREQUENCY_CORRECTION
        #define FREQUENCY_CORRECTION 0
    #endif

    // Port settings
    #if TARGET_CPU == m328p
        #define DAC_PORT PORTD
        #define DAC_DDR  DDRD
        #define LED_PORT PORTB
        #define LED_DDR  DDRB
        #define ADC_PORT PORTC
        #define ADC_DDR  DDRC
    #endif
#endif

#endif


#define GPIO_AUDIO_TRIGGER GPIO_NUM_37
// Audio input pin is controlled by I2S_ADC_CHANNEL below.
// Audio output pin is ...hardcoded as GPIO 25?
#define GPIO_PTT_OUT GPIO_NUM_33
#define ESP_INTR_FLAG_DEFAULT 0


//i2s number
#define TNC_I2S_NUM           I2S_NUM_0
// AFSK demodülatör 9600 Hz bekliyor - buna uymak zorundayız
#define DESIRED_SAMPLE_RATE   (9600)
#define OVERSAMPLING          (8)
//i2s sample rate
#define TNC_I2S_SAMPLE_RATE   (DESIRED_SAMPLE_RATE * OVERSAMPLING)
#define CONFIG_AFSK_DAC_SAMPLERATE (TNC_I2S_SAMPLE_RATE)

//i2s data bits
#define TNC_I2S_SAMPLE_BITS   (I2S_BITS_PER_SAMPLE_16BIT)
// 125ms of audio should be plenty I think
#define TNC_I2S_BUFLEN        (TNC_I2S_SAMPLE_RATE / 8)

//I2S data format
#define TNC_I2S_FORMAT        (I2S_CHANNEL_FMT_ONLY_RIGHT)
#define TNC_I2S_CHANNEL_NUM   (1)

//I2S built-in ADC unit
#define I2S_ADC_UNIT              ADC_UNIT_1
// ADC1_CHANNEL_0 = GPIO36 (VP pin)
#define I2S_ADC_CHANNEL           ADC1_CHANNEL_0

// Ses algılama eşiği - ses sinyali olup olmadığını anlamak için
// Gürültü ~20 ADC, gerçek sinyal bundan çok daha yüksek olmalı
#define KEEP_RECORDING_THRESH  (400)

// Ses ADC offset - idle voltajın ADC değeri
// Ölçülen değer: ~1875
#define ADC_CENTER_VALUE       (1875)

// Otomatik kazanç - ses sinyalinin dinamik aralığı
// Peak-to-peak yaklaşık 1V = ~1240 ADC
#define ADC_SIGNAL_RANGE       (1240)

// Sürekli dinleme modu - trigger pin beklemeden sürekli ses işle
#define CONTINUOUS_RX_MODE     1