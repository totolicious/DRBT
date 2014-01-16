#include <DCMotor.h>

DCMotor motor0(M0_EN, M0_D0, M0_D1);
DCMotor motor1(M1_EN, M1_D0, M1_D1);
int i=0;
int ammount = 1;

void setup()
{
  motor0.setClockwise(false);
}

void loop()
{
  i=i+ammount;
  motor0.setSpeed(i);
  motor1.setSpeed(-i);
  delay(50);
  Serial.println(i);
  if (i == 100) {
    ammount = -1;
  }
  if (i == -100) {
    ammount = 1;
  }

}

