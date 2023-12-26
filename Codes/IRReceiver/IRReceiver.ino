#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData[200] = {3232, 3122,  482, 314,  524, 310,  526, 310,  526, 1114,  478, 310,  526, 1112,  480, 310,  524, 310,  526, 308,  526, 310,  526, 1112,  480, 310,  526, 310,  526, 1114,  480, 1114,  480, 1114,  480, 1114,  480, 312,  524, 310,  526, 1112,  480, 1114,  480, 312,  524, 1114,  480, 310,  526, 1112,  482, 308,  526, 310,  526, 310,  526, 310,  526, 310,  526, 310,  526, 310,  528, 308,  526, 310,  526, 308,  526, 310,  526, 308,  526, 308,  526, 308,  528, 308,  526, 310,  526, 308,  526, 308,  528, 308,  528, 310,  526, 308,  526, 308,  526, 308,  528, 308,  526, 310,  526, 1112,  480, 310,  526, 1112,  480, 1112,  480, 310,  526, 310,  526, 308,  526, 308,  528, 308,  526, 308,  526, 308,  528, 308,  528, 310,  526, 308,  528, 306,  528, 310,  528, 308,  526, 308,  528, 308,  528, 308,  528, 308,  526, 308,  528, 1112,  480, 308,  526, 308,  528, 308,  528, 308,  528, 308,  528, 308,  528, 308,  528, 1112,  480, 308,  526, 308,  528, 308,  526, 308,  528, 308,  528, 308,  528, 306,  528, 308,  526, 308,  528, 1112,  480, 1114,  480, 1112,  480, 310,  526, 308,  526, 1112,  480};
// Example Samsung A/C state captured from IRrecvDumpV2.ino
uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};

void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
 
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 200, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
 
}