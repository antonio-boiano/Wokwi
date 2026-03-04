#define LED  12  // The digital pin to which a led is connected.
#define C_TIME 1000000 //Time in us
hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}
void setup() {
  //Pin Setup
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  My_timer = timerBegin(0, 80, true); //Timer initializer
  //0: hw timer number (ESP32 has 4 hw timers available
  //80: time divider. ESP32 clk 80MHz so we set evry tick to 1 us
  //true: counter shoud increment

  timerAttachInterrupt(My_timer, &onTimer, true);//Attach Interrupt

  timerAlarmWrite(My_timer, C_TIME, true);
  //C_TIME: number of microseconds after which the interrupt should occour
  //true: timer counter will reload after interrupt

  timerAlarmEnable(My_timer); //Just Enable
}
void loop() {
  delay(10);
}




