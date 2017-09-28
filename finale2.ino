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
  int lightlevel=analogRead(lightpin);
  delay(10);
  int lightlevel1=analogRead(lightpin1);
  delay(10);
  lightlevel=map(lightlevel,0,900,0,180);
  lightlevel1=map(lightlevel1,0,900,0,180);
  if (lightlevel1 <= 90 && lightlevel1 >= 90)
  {
    motor.write(0);
  delay(10);
  }
if (lightlevel < 90 && lightlevel1>90)
{

  motor.write(180);
delay(10);
}
}

