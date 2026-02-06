# ESP32 APRS Projesi

Bu proje, ESP32 mikrodenetleyici kullanarak APRS (Automatic Packet Reporting System) uygulamaları geliştirmenizi sağlayan bir Arduino IDE tabanlı çözümdür.

## Proje Hakkında

ESP32 APRS, LibAPRS kütüphanesinin ESP32 uyumlu bir sürümüdür. Bu proje, ESP32 mikrodenetleyicilerde tam AFSK modülasyon/demodülasyonu, AX.25 paket işlemesi ve APRS iletişimini gerçekleştirmenize olanak tanır.

### Ana Özellikler

- 🛰️ AX.25 APRS paketleri gönderme ve alma
- 📡 Yazılım tabanlı tam modülasyon ve demodülasyon
- 📍 Kolay konumlandırma güncellemeleri ve mesajları gönderme
- 🔧 Ham radyosu kontrolü ve konfigürasyonu
- 💾 Kaynakta sembol ayarı desteği
- ⚡ Açık squelch (squelch kapalı) çalışma modu
- 🎯 I2S çevresel kullanarak optimize edilmiş ADC/DAC işlemesi

## Proje Yapısı

```
ESP32APRS/
├── aprses.ino              # Ana Arduino sketch dosyası (ANA PROJE)
└── LibAPRS/                # LibAPRS kütüphanesi (ESP32 uyumlu fork)
    ├── src/                # Kütüphane kaynak dosyaları
    │   ├── LibAPRS.h       # Ana kütüphane başlık dosyası
    │   ├── LibAPRS.cpp     # Ana kütüphane uygulaması
    │   ├── AX25.h/cpp      # AX.25 protokol uygulaması
    │   ├── AFSK.h/cpp      # AFSK modülasyon/demodülasyonu
    │   ├── HDLC.h          # HDLC çerçeveleme
    │   ├── CRC-CCIT.h/c    # CRC hesaplaması
    │   └── constants.h     # Sabitler
    ├── library.properties  # Kütüphane bilgileri
    └── README.md          # LibAPRS belgeleri
```

## Gereksinimler

### Donanım

- **ESP32 Mikrodenetleyici** - AI-Thinker ESP32 veya uyumlu bir variant
- **MicroModem Uyumlu Modem** - İnternet bağlantısı için (opsiyonel)
- **USB-to-Serial Adaptörü** - Programlama ve seri haberleşme için
- **3.3V referans voltajlı ADC** - ESP32 ADC (varsayılan)

### Yazılım

- Arduino IDE (v1.8.0 veya daha yeni)
- ESP32 Board Support Package (BSP)
- LibAPRS kütüphanesi (bu projede dahil)

## Kurulum

### 1. Arduino IDE'yi Hazırlayın

1. [Arduino IDE](https://www.arduino.cc/en/software) indirin ve kurun
2. Tools → Board Manager'ı açın
3. "ESP32" araması yapın
4. Espressif Systems tarafından sağlanan "esp32" paketini yükleyin

### 2. LibAPRS Kütüphanesini Kurun

1. Bu repoyu klonlayın veya ZIP olarak indirin
2. `LibAPRS` klasörünü Arduino libraries dizinine kopyalayın:
   - **Windows:** `Documents\Arduino\libraries\`
   - **macOS:** `~/Documents/Arduino/libraries/`
   - **Linux:** `~/Arduino/libraries/`

### 3. Kurulumu Doğrulayın

1. Arduino IDE'ni yeniden başlatın
2. File → Open → `aprses.ino` dosyasını açın
3. Derlenme hatası olmadığını kontrol edin

## Hızlı Başlangıç

### Ana Proje: aprses.ino

Ana proje dosyası `aprses.ino`'da bulunmaktadır. Bu dosya:
- ADC referans voltajının tanımlanması
- Squelch ayarlarını içerir
- Paket alındığında çağrılacak callback fonksiyonları içerir
- Setup ve loop fonksiyonlarını içerir

Dosyayı Arduino IDE'de açarak, ESP32'niz için derleme ve yükleme yapabilirsiniz.

### Temel Yapı Örneği

```cpp
#include <LibAPRS.h>

// ADC referans voltajını ayarlayın
#define ADC_REFERENCE REF_3V3
#define OPEN_SQUELCH false

// Paket alındığında çağrılacak callback fonksiyonu
extern "C" void aprs_msg_callback(struct AX25Msg *msg) {
  // Paket işleme kodu buraya gelir
}

void setup() {
  Serial.begin(115200);
  
  // LibAPRS'yi başlat
  // Detaylar için aprses.ino dosyasını inceleyin
}

void loop() {
  // Ana program döngüsü
}
```

### Yapılandırma Seçenekleri

#### ADC Referans Voltajı
```cpp
#define ADC_REFERENCE REF_3V3   // 3.3V için
// VEYA
#define ADC_REFERENCE REF_5V    // 5V için
```

#### Squelch Ayarı
```cpp
#define OPEN_SQUELCH false  // Squelch kapalı (varsayılan)
// VEYA
#define OPEN_SQUELCH true   // Squelch açık
```

## ESP32'ye Özel Bilgiler

Bu proje LibAPRS'nin ESP32 uyumlu bir sürümüdür. Temel fark:

- **I2S Çevre:** ESP32'nin ADC, 9600 Hz hızında verimli bir şekilde çalışamadığından, bu sürüm I2S çevresini ADC ve DAC'ı sürümlemek için kullanır
- **ADC Hızı Sınırı:** ESP32'nin `adc1_get_raw()` / `adc2_get_raw()` metotları yaklaşık 6000 Hz'de çalışabilir, ancak LibAPRS 9600 Hz gerektirir
- **API Uyumluluğu:** API çoğunlukla aynı kalmıştır, fakat doğrudan ADC yazmıyorsanız veri göndermek için `finish_transmission()` çağırmanız gerekebilir

## Dosya Açıklamaları

### Ana Dosya: aprses.ino
Ana Arduino sketch dosyası. Proje için gerekli:
- ADC referans voltajı tanımı
- Squelch ayarları
- Paket callback fonksiyonları
- Setup ve loop fonksiyonları

### LibAPRS Kaynağı

| Dosya | Açıklama |
|-------|----------|
| `LibAPRS.h/cpp` | Ana kütüphane arabirimi ve uygulaması |
| `AX25.h/cpp` | AX.25 protokol işlemesi |
| `AFSK.h/cpp` | AFSK modülasyon ve demodülasyonu |
| `HDLC.h` | HDLC çerçeveleme protokolü |
| `CRC-CCIT.h/c` | Döngüsel Artıklılık Kontrolü (CRC) |
| `FakeArduino.h/cpp` | Simülasyon ve test için Arduino öykünmesi |

## Ana Proje Dosyası

### aprses.ino

Ana proje dosyası detaylı kodlar ve açıklamalar içerir:
- ADC konfigürasyonu
- Paket gönderme
- Paket alma ve işleme
- Konumlandırma güncellemeleri
- Seri haberleşme ayarları

Dosyanın tamamını açarak tüm işlevleri keşfedebilirsiniz.

## Kaynaklar

- [LibAPRS Orijinal Projesi](https://github.com/markqvist/LibAPRS)
- [MicroModem Projesi](https://github.com/markqvist/MicroModem)
- [APRS Nedir?](http://www.aprs.org/)
- [ESP32 Belgeleri](https://docs.espressif.com/projects/esp-idf/)

## Sorun Giderme

### Problem: Kütüphane bulunamıyor
**Çözüm:** LibAPRS klasörünü doğru şekilde Arduino libraries dizinine kopyaladığınızı kontrol edin ve Arduino IDE'yi yeniden başlatın.

### Problem: ADC hızı yeterli değil
**Çözüm:** Bu proje ESP32 I2S çevresini kullanarak bu sorunu çözer. ADC_REFERENCE tanımının doğru olduğundan emin olun.

### Problem: Paketler alınamıyor
**Çözüm:** 
- Modem donanımının düzgün bağlandığını kontrol edin
- OPEN_SQUELCH ayarını kontrol edin
- Seri haberleşme hızını (115200) doğrulayın
- Callback fonksiyonunun doğru şekilde tanımlandığını kontrol edin

## Katkıda Bulunma

Bu proje LibAPRS'nin bir fork'udur. Katkılar ve geliştirmeler için:
1. Bu repoyu fork'layın
2. Özellik dalı oluşturun (`git checkout -b feature/AmazingFeature`)
3. Değişikliklerinizi commit'leyin (`git commit -m 'Add some AmazingFeature'`)
4. Dalı push'layın (`git push origin feature/AmazingFeature`)
5. Pull Request açın

## Lisans

Bu proje LibAPRS'nin ESP32 uyumlu fork'udur. LibAPRS orijinal kütüphane lisansını korur. Detaylı lisans bilgisi için `LibAPRS/LICENSE` dosyasını inceleyin.

## Yazar ve Katkıda Bulunanlar

- **LibAPRS Orijinal:** [Mark Qvist](http://unsigned.io/)
- **ESP32 Fork:** (Bu projede belirtilmemiş)

## İletişim ve Destek

Sorularınız veya sorunlarınız için:
1. GitHub issues'ı kontrol edin
2. LibAPRS projesi yöneticisine ulaşın
3. Kod örneğini çalışan örnek ile karşılaştırın

---

**Son Güncelleme:** Şubat 2026

**Uyarı:** Bu kütüphane aktif olarak geliştirilmektedir. Hataları bekleyebilirsiniz. Bulduğunuz hataları lütfen raporlayın.
