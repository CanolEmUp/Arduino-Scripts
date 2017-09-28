//it comes back to the original position aka 0 dumbass
#include<Servo.h>
Servo motor;
int pos=0;
int lightpin = 0;
int lightpin2 = 0; 
void setup()
{
motor.attach(9);
}

void loop()
{
  int lightlevel=analogRead(lightpin);
  int lightlevel2=analogRead(lightpin2);
  lightlevel=map(lightlevel,0,900,0,180);
  lightlevel=constrain(lightlevel,0,180);
  lightlevel2=map(lightlevel2,0,900,0,180);
  lightlevel2=constrain(lightlevel2,0,180);
  
  if (lightlevel > lightlevel2)
  {
    motor.write(lightlevel);
  delay(10);
  }
if (lightlevel < lightlevel2)
{

  motor.write(lightlevel2);
delay(10);
}
}

