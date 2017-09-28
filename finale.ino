#include<Servo.h>
Servo motor;
int pos=0;
int lightpin = 0;
int lightpin1 = 3;

void setup()
{
motor.attach(9);
}

void loop()
{
  delay(10);
  int lightlevel=analogRead(lightpin);
  delay(10);
  int lightlevel1=analogRead(lightpin1);
  delay(10);
  if (lightlevel >= lightlevel1 && lightlevel1<=lightlevel)
  {
    motor.write(0);
  delay(10);
  }
else if (lightlevel < lightlevel1 && lightlevel1> lightlevel)
{
  motor.write(180);
delay(10);
}
}

