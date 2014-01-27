#include <DCMotor.h>
#include <IRremote.h>

// left_motor
DCMotor left_motor(M0_EN, M0_D0, M0_D1);
DCMotor right_motor(M1_EN, M1_D0, M1_D1);

// IR receiver
IRrecv irReceiver(A4);
int Received, LastValue;

void setup()
{
  left_motor.setClockwise(false);
  delay(1000);
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void move_robot(int left_ammount, int right_ammount) {
  int lf, rf, lb, rb;
  
  left_motor.setSpeed(left_ammount);
  right_motor.setSpeed(right_ammount);

  if (left_ammount > right_ammount) {
    lf = HIGH; rf = LOW;
    lb = HIGH; rb = LOW;
  } else if (left_ammount < right_ammount) {
    lf = LOW;  rf = HIGH;
    lb = LOW;  rb = HIGH;
  } else if (left_ammount > 0 && right_ammount > 0) {
    lf = HIGH; rf = HIGH;
    lb = LOW;  rb = LOW;
  } else if (left_ammount < 0 && right_ammount < 0) {
    lf = LOW;  rf = LOW;
    lb = HIGH; rb = HIGH;
  } else if (left_ammount == 0 && right_ammount == 0) {
    lf = LOW; rf = LOW;
    lb = LOW; rb = LOW;
  }
  
  digitalWrite(A0, lf);
  digitalWrite(A1, rf);
  digitalWrite(A2, lb);
  digitalWrite(A3, rb);
}
  
void loop()
{
  Received = irReceiver.getIRRemoteCode();
  if (Received != LastValue) {
    Serial.println(Received);
    // Something different received from IR, show it
    if (Received) {
      
      if(Received == 2) {
        move_robot(100,100);
      } else if (Received == 8) {
        move_robot(-100,-100);
      } else if (Received == 5) {
        move_robot(0,0);
      } else if (Received == 4) {
        move_robot(-100,100);
      } else if (Received == 6) {
        move_robot(100,-100);
      } else if (Received == 1) {
        move_robot(50, 100);
      } else if (Received == 3) {
        move_robot(100, 50);
      } else if (Received == 7) {
        move_robot(-50,-100);
      } else if (Received == 9) {
        move_robot(-100,-50);
      }
    }
    LastValue = Received;
  }
}

