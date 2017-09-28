#include <Servo.h>

Servo servo1;

int sensorPin = A0;            // select the input pin for the ldr
int ledPin = 13;  
unsigned int sensorValue = 0;
int servoPin = 9;
int pos = 0;

void setup()
{
  //Start Serial port
  Serial.begin(9600);        // start serial for output - for testing
  servo1.attach(9);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // For DEBUGGING - Print out our data, uncomment the lines below
  Serial.print("Cell = ");     // print the value (0 to 1024)
  Serial.println(analogRead(sensorPin));                   // print carriage return  

  pos = analogRead(sensorPin);
  pos = constrain (pos, 0, 1023);

  int servoPos = map(pos, 0, 1023, 255, 0);
  int servoDegree = map(servoPos, 255, 0, 0, 179);

  servo1.write(servoDegree);
  Serial.print("Servo Degree = ");
  Serial.println(servoDegree);


  int val = analogRead(sensorPin);
  val = constrain (val, 0, 1023);

  int ledLevel = map(val, 0, 1023, 255, 0);
  analogWrite (ledPin, ledLevel);  

  delay(50);  
}   

