#include <WiFi.h>
#include <esp_wifi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  10 //Slep for 10 seconds
RTC_DATA_ATTR int bootCount = 0;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  delay(2000);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  Serial.println("Enabling Wi-Fi STA");
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  delay(2000);


  Serial.println("Disabling Wi-Fi");
  WiFi.mode(WIFI_OFF);
  delay(2000);

  Serial.println("Going to sleep now");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
}