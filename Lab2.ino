int ledPin1=2;
int ledPin2=3;
int ledPin3=4;
int ledPin4=5;

void setup()
{
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
}

void loop()
{
  int delayTime = 100;
  digitalWrite(ledPin1, HIGH);
  delay(delayTime);
  digitalWrite(ledPin2, HIGH);
  delay(delayTime);
  digitalWrite(ledPin3, HIGH);
  delay(delayTime);
  digitalWrite(ledPin4, HIGH);
  delay(delayTime);

  delay(delayTime);
  digitalWrite(ledPin4, LOW);
  delay(delayTime);
  digitalWrite(ledPin3, LOW);
  delay(delayTime);
  digitalWrite(ledPin2, LOW);
  delay(delayTime);
  digitalWrite(ledPin1, LOW);
  delay(delayTime);
}


