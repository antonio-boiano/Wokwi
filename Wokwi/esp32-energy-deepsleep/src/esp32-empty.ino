#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  10 //Slep for 10 seconds
RTC_DATA_ATTR int bootCount = 0;

void setup(){
  Serial.begin(115200);
  delay(2000);

  Serial.println("Enabling Wi-Fi 2sec");
  WiFi.mode(WIFI_STA);
  delay(2000);
  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  Serial.println("Disabling Wi-Fi 2sec");
  WiFi.mode(WIFI_OFF);
  delay(2000);

  Serial.println("Going to sleep now");

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ESP32 sleep every " + String(TIME_TO_SLEEP));

  Serial.flush(); 
  esp_deep_sleep_start();
  //esp_light_sleep_start();
  Serial.println("This will never be printed");
}

void loop(){
  //This is not going to be called
}