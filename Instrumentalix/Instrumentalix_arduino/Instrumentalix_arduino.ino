#include <Ping.h>
#include "Arduino.h"
#include <pitches.h>

PingSensor ping(A4); //ping sensor input.
const int LEDS_NUM = 4; //how many leds
const int MAX_DELAY = 300; //maximum value of the delay between buzzes
const int MIN_DELAY = 50; //minimum value of the delay between buzzes

const int BUZZ_DELAY = 30; //duration of a single buzz in miliseconds

//fiddle around with the values so that they work for you

//1 is pretty close
//42 might actually be 42cm
const int MIN_PING_VAL = 1; //min val returned by the ping sensor
const int MAX_PING_VAL = 42; //max val returned by the ping sensor

//350 is the val for my room at night with 2 lights in the room
//900 is for my phone's assistive light pretty close to the sensor
const int MIN_LIGHT_VAL = 350; //min val returned by the light sensor
const int MAX_LIGHT_VAL = 900; //max val returned by the light sensor

const int NOTE_LOWEST = 31;
const int NOTE_HIGHEST = 4178;

//array with the leds
int leds[LEDS_NUM] = {A0, A1, A2, A3};

void setup()
{
  int i;
  //set output mode on speaker and leds
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
  for (i=0; i<sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  delay(1000);
}


void loop()
{
  //get ping sensor value and light value
  int ping_val = ping.measureCM(),
      light_val = analogRead(A5),
      i,
      open_leds_num,
      delay_sec;
      
  open_leds_num = min(LEDS_NUM, max(0, round(map(ping_val, MIN_PING_VAL, MAX_PING_VAL, 0, LEDS_NUM))));
  delay_sec = min(MAX_DELAY, max(MIN_DELAY, round(map(light_val, MIN_LIGHT_VAL, MAX_LIGHT_VAL, MIN_DELAY, MAX_DELAY))));

  toneDelay(SPEAKER, map(ping_val, 1, 162, NOTE_LOWEST, NOTE_HIGHEST), BUZZ_DELAY);
  
  for (i=0; i<open_leds_num; i++) {
    digitalWrite(leds[i], HIGH);
  }
  for (i=open_leds_num; i<sizeof(leds); i++) {
    digitalWrite(leds[i], LOW);
  }
  
  //wait according to light value
  delay(delay_sec);
  Serial.println(delay_sec, DEC);
}


