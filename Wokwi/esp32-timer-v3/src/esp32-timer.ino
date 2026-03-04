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

  My_timer = timerBegin(1000000); 
  timerAttachInterrupt(My_timer, &onTimer);
  timerAlarm(My_timer, C_TIME, true, 0);
}
void loop() {
  delay(10);
}




