int ledPin1=2;
int ledPin2=3;
int ledPin3=4;
int ledPin4=5;
int ledPin5=6;
int ledPin6=7;

void setup()
{
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
}
void loop(){
 for(int x = 0; x < 6; x += 2);
{
  int delayTime = 100;
  digitalWrite(ledPin2, HIGH);
  delay(delayTime);
  digitalWrite(ledPin4, HIGH);
  delay(delayTime);
  digitalWrite(ledPin6, HIGH);
  delay(delayTime);
  digitalWrite(ledPin1, HIGH);
  delay(delayTime);
  digitalWrite(ledPin3, HIGH);
  delay(delayTime);
  digitalWrite(ledPin5, HIGH);
  delay(delayTime);
  
  digitalWrite(ledPin6, LOW);
  delay(delayTime);
  digitalWrite(ledPin4, LOW);
  delay(delayTime);
  digitalWrite(ledPin2, LOW);
  delay(delayTime);
  digitalWrite(ledPin5, LOW);
  delay(delayTime);
  digitalWrite(ledPin3, LOW);
  delay(delayTime);
  digitalWrite(ledPin1, LOW);
  delay(delayTime);

}
}
