#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10       /* Time ESP32 will go to sleep (in seconds) */
#define THRESHOLD   40


RTC_DATA_ATTR int bootCount = 0;

touch_pad_t touchPin;
/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void print_wakeup_touchpad(){
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  #if CONFIG_IDF_TARGET_ESP32
    switch(touchPin)
    {
      case 0  : Serial.println("Touch detected on GPIO 4"); break;
      case 1  : Serial.println("Touch detected on GPIO 0"); break;
      case 2  : Serial.println("Touch detected on GPIO 2"); break;
      case 3  : Serial.println("Touch detected on GPIO 15"); break;
      case 4  : Serial.println("Touch detected on GPIO 13"); break;
      case 5  : Serial.println("Touch detected on GPIO 12"); break;
      case 6  : Serial.println("Touch detected on GPIO 14"); break;
      case 7  : Serial.println("Touch detected on GPIO 27"); break;
      case 8  : Serial.println("Touch detected on GPIO 33"); break;
      case 9  : Serial.println("Touch detected on GPIO 32"); break;
      default : Serial.println("Wakeup not by touchpad"); break;
    }
  #else
    if(touchPin < TOUCH_PAD_MAX)
    {
      Serial.printf("Touch detected on GPIO %d\n", touchPin); 
    }
    else
    {
      Serial.println("Wakeup not by touchpad");
    }
  #endif
}

void setup(){
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  delay(2000); //Take some time to open up the Serial Monitor

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  print_wakeup_touchpad();
  
  Serial.println("Enabling Wi-Fi 2sec");
  WiFi.mode(WIFI_STA);
  delay(2000);
  Serial.println("Going to sleep now");

  touchSleepWakeUpEnable(T3,THRESHOLD);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ESP32 sleep every " + String(TIME_TO_SLEEP));

  Serial.flush(); 
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void loop(){
  //This is not going to be called
}