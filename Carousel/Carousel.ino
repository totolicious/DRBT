#include <DCMotor.h>
#include <IRremote.h>

// left_motor
DCMotor carousel_motor(M0_EN, M0_D0, M0_D1);

int carousel_speed;
IRrecv irReceiver(A4);
int Received, LastValue;
int leds[4] = { A0, A1, A2, A3 };

void setup() {
  carousel_motor.setClockwise(false);
  carousel_speed = 0;
  delay(1000);
  Serial.begin(9600);
  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(leds[2], OUTPUT);
  pinMode(leds[3], OUTPUT);
}

void loop() {
    Received = irReceiver.getIRRemoteCode();
    if (Received != LastValue) {
    
    // Something different received from IR, show it
    switch(Received) {
      case 2:
        add_speed(1);
        break;
      case 8:
        add_speed(-1);
        break;
    }
    LastValue = Received;
  }
  delay(100);
}

void add_speed(int s) {
  carousel_speed += s;
  if (carousel_speed > 4) {
    carousel_speed = 4;
  } else if (carousel_speed < -4) {
    carousel_speed = -4;
  }
  Serial.print("Speed added: ");
  Serial.println(s);
  Serial.print("Carousel speed: ");
  Serial.println(carousel_speed);
  Serial.println("");
  display_speed(carousel_speed);
  set_motor_speed(carousel_speed);
}

void display_speed(int carousel_speed) {
  int led_values[4] = {LOW, LOW, LOW, LOW},
      i;
  
  if (carousel_speed > 0) {
    for (i = 0; i < carousel_speed; i++) {
      led_values[i] = HIGH;
    }
  } else if (carousel_speed < 0) {
    for (i = 3; i > 3 + carousel_speed; i--) {
      led_values[i] = HIGH;
    }
  }
  
  for (i = 0; i < 4; i++) {
    digitalWrite(leds[i], led_values[i]);
  }
}

void set_motor_speed(int carousel_speed) {
  int motor_speed = 0;
  if (carousel_speed) {
    motor_speed = carousel_speed * 20;
  }
  
  if (motor_speed < 0) {
    motor_speed -= 20;
  } else if (motor_speed > 0) {
    motor_speed += 20;
  }
  
  carousel_motor.setSpeed(motor_speed);
}

