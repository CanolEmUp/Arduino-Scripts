#include <Servo.h>
Servo myservo;
Servo myservo2;
int lightpin = 13;
int lightpin2 = 11;

void setup()
{
  myservo.attach(12);
  myservo2.attach(10);
}

void loop()
{
  int lightlevel = analogRead(lightpin);
  lightlevel = map(lightlevel, 0, 900, 0, 90);
  delay(100);
  lightlevel = constrain(lightlevel , 0, 90);
  myservo.write(lightlevel);
  delay(15);
}

