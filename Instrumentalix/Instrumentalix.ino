#include <Ping.h>
#include "Arduino.h"
#include "pitches.h"

PingSensor ping(A4); //S1 input.
const int LEDS_NUM = 4;
int leds[LEDS_NUM] = {A0, A1, A2, A3};

void setup()
{
  int i;
  pinMode(SPEAKER, OUTPUT);
  for (i=0; i<sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  delay(1000);
}


void loop()
{
  int ping_val = ping.measureCM(),
      i,
      open_leds_num,
      delay_sec;
      
  toneDelay(SPEAKER, map(ping_val, 1, 162, NOTE_C1, NOTE_C8),50);
  //open_leds_num = min(LEDS_NUM, max(0, round(map(ping_val, 1, 42, 0, LEDS_NUM))));
  
  
  for (i=0; i<open_leds_num; i++) {
    digitalWrite(leds[i], HIGH);
  }
  for (i=open_leds_num; i<sizeof(leds); i++) {
    digitalWrite(leds[i], LOW);
  }
  
  delay(delay_sec);
}

