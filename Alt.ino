#include <SFE_BMP180.h>
#include <SPI.h>
#include <TFT.h>// Arduino TFT library
#include <Wire.h>
#include "SparkFunHTU21D.h"

#define cs   10
#define dc   8
#define rst  9
#define ALTITUDE 76.0 // Altitude of Toronto

SFE_BMP180 pressure; //create pressure sensor
HTU21D myHumidity; //create humidity sensor

TFT screen = TFT(cs, dc, rst);// Give wiring values to screen

/*
These are the ints and strings that are the data of Temperature, Humidity, Atmospheric Pressure and Lighting
*/

const int temp_num_readings = 50;
const int humd_num_readings = 50;
const int atm_num_readings = 50;
/*
These constant ints are used to determine size of arrays
*/

float temp_readings[temp_num_readings];
float humidity_readings[humd_num_readings];
float atm_readings[atm_num_readings];
/*
These are the readings from the sensor input
*/

int sensor_index; // the index of the current sensor input
// totals for sensor input index
float temp_total = 0;
float humd_total = 0;
float atm_total = 0;
//average for data
float tempave;
float humdave;
float atmave;

int timer = 0; //timer to add new data to arrays for comfort level
int photocellPin = A0;
int comfort_level;
int temp_point;
int humidity_point;
int pressure_point;
int cycles = 0; // this is the amount of cycles the arrays have been through
String photocellReading;
char Lightvalue[5];
char Tempvalue[5];
char Humvalue[5];
char Atmvalue[5];
double P,T;

void setup() {
  
  Serial.begin(9600);//start serial screen
  Serial.println("Serial Monitor Start!");
  
  myHumidity.begin(); // start humidity sensor
  pressure.begin(); // start pressure sensor
  screen.begin(); // start the screen

  // set text size
  screen.setTextSize(1);
  
  // make the background black
  screen.background(0,0,0);

  // set the text color to black
  screen.stroke(0,0,0);
  
  // print rectangle on top and bottom of screen
  screen.fill(255,255,255);
  screen.rect(0, 0, screen.height() * 1.25, 15);
  screen.rect(0, 113, screen.height() * 1.25, 15);
  
  screen.text("Temp(C): ", 35, 5);
  screen.text("Hum(%): ", 100, 5);
  screen.text("Atm(hPa): ", 35, 116);
  screen.text("Light: ", 100, 116);
  
  /*
  These loops set all the sensor inputs to 0
  */
  
  for (int temp_num_reading = 0; temp_num_reading < temp_num_readings; temp_num_reading++)
  temp_readings[temp_num_reading] = 0;
  for (int humd_num_reading = 0; humd_num_reading < humd_num_readings; humd_num_reading++)
  humidity_readings[humd_num_reading] = 0;
  for (int atm_num_reading = 0; atm_num_reading < atm_num_readings; atm_num_reading++)
  atm_readings[atm_num_reading] = 0;
  
}

void loop() {
  
  timer += 500;
  
  //set text colour to black
  screen.stroke(0,0,0);
  
  //create decimal values for humidity and temperature
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  float atmtemp = pressure.getTemperature(T); //Temp from pressure sensor
  float atm = pressure.getPressure(P,T); // get pressure using temperature from pressure sensor
  double p0 = pressure.sealevel(P, ALTITUDE); // determine atmospheric pressure given pressure and altitude
  
  //convert decimal values to a string
  dtostrf(temp, 5, 2, Tempvalue);
  dtostrf(humd, 5, 2, Humvalue);
  
  //convert raw reading of lighting to string
  photocellReading = String(analogRead(photocellPin));
  //convert string to char array
  photocellReading.toCharArray(Lightvalue, 5);
  
  //display text and values on top rectangle
  
  screen.text(Tempvalue, 35, 50);
  screen.text(Humvalue, 142, 5);
  //screen.text(p0, 35, 5);
  screen.text(Lightvalue, 135, 116);
  
  //print data in the serial screen
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print("Humidity: ");
  Serial.print(Humvalue);
  Serial.print(" ");
  Serial.print("Pressure: ");
  Serial.print(p0);
  Serial.print(" ");
  Serial.print("timer: ");
  Serial.print(timer);
  Serial.print(" ");
  Serial.print("Temp point: ");
  Serial.print(temp_point);
  Serial.print(" ");
  Serial.print("Hum point: ");
  Serial.print(humidity_point);
  Serial.print(" ");
  Serial.print("Temp Total: ");
  Serial.print(temp_total);
  Serial.print(" ");
  Serial.print("Hum Total: ");
  Serial.print(humd_total);
  Serial.print(" ");  
  Serial.print("Comfort Level: ");
  Serial.print(comfort_level);
  Serial.print(" ");
  Serial.print("Temp Ave.: ");
  Serial.print(tempave);
  Serial.print(" ");
  Serial.print("Humd Ave.: ");
  Serial.print(humdave);
  Serial.print(" ");
  Serial.print("Array Index: ");
  Serial.print(sensor_index);
  Serial.println();
  
  
  delay(100);
  
  //reprint text but in white so it can refresh
  screen.stroke(255,255,255);
  screen.text(Lightvalue, 135, 116);
  screen.text(Humvalue, 142, 5);
  screen.text(Tempvalue, 35, 50);
  
  //This is to calculate the average of the sensor inputs
  
  //remove the last value in the array in order to add a new one

   if (timer == 1000){
     if (cycles != 0){
    //subtract last index from total
    temp_total = temp_total - temp_readings[0];
    humd_total = humd_total - humidity_readings[0];
    atm_total = atm_total - atm_readings[0];
     }
    //read from sensors
    temp_readings[sensor_index] = temp;
    humidity_readings[sensor_index] = humd;
    //atm_readings[sensor_index] = 
    //add reading to total
    temp_total = temp_total + temp_readings[sensor_index];
    humd_total = humd_total + humidity_readings[sensor_index];
    //atm_total
    //move to next position in array
    sensor_index = sensor_index + 1;
    //if at end of index, reset to 0
    if (sensor_index >= 50){
      cycles++;
      sensor_index = 0;
    }
    //calculate average of sensor inputs
    tempave = temp_total / temp_num_readings;
    humdave = humd_total / humd_num_readings;
    //atmave = atm_total / atm_readings;
    
    //add new value in
    
    timer = 0;
   }
  // This is to visually display light values in an easier way to understand
  screen.stroke(0,0,0);
  if (analogRead(photocellPin) > 60 && analogRead(photocellPin) < 120){
    screen.fill(255,255,100);
  }
  else if (analogRead(photocellPin) > 120 && analogRead(photocellPin) < 200){
    screen.fill(255,255,0);
  }
  else if (analogRead(photocellPin) > 200 && analogRead(photocellPin) < 250){
    screen.fill(200,200,0);
  }
  else if (analogRead(photocellPin) > 250 && analogRead(photocellPin) < 320){
    screen.fill(150,150,0);
  }
  else if (analogRead(photocellPin) > 320 && analogRead(photocellPin) < 340){
    screen.fill(100,100,0);
  }
  else{
    screen.fill(0,0,0);
  }
  
  screen.rect(125, 20, 30, 40);
  
  
  //This is to visually display humidity values
  screen.stroke(0,0,0);
  if (humd > 90 && humd < 100){
    screen.fill(0,0,255);
  }
  else if (humd > 80 && humd < 90){
    screen.fill(25,25,255);
  }
  else if (humd > 70 && humd < 80){
    screen.fill(50,50,255);
  }
  else if (humd > 60 && humd < 70){
    screen.fill(75,75,255);
  }
  else if (humd > 50 && humd < 60){
    screen.fill(100,100,255);
  }  
  else if (humd > 40 && humd < 50){
    screen.fill(125,125,255);
  }
  else if (humd > 30 && humd < 40){
    screen.fill(150,150,255);
  }
  else if (humd > 20 && humd < 30){
    screen.fill(175,175,255);
  }
  else if (humd > 10 && humd < 20){
    screen.fill(200,200,255);
  }
  else {
    screen.fill(225,225,255);
  }
  
  screen.rect(125, 65, 30, 40);

  // This is to visually display temperature values
  screen.stroke(0,0,0);
  if (temp > 35){
    screen.fill(255,0,0);
  }
  else if (temp > 30 && temp < 35){
    screen.fill(255,125,0);
  }
  else if (temp > 27.5 && temp < 30){
    screen.fill(255,175,0);
  }
  else if (temp > 25 && temp < 27.5){
    screen.fill(255,200,0);
  }
  else if (temp > 22.5 && temp < 25){
    screen.fill(100,255,100);
  }
  else if (temp > 20 && temp < 22.5){
    screen.fill(50,255,50);
  }  
 
  screen.rect(35, 65, 30, 40);
  
  // comfort level works on a scale of 0-20, 0 being the ideal and 20 the least ideal

  //predict weather comfortness with averages with data
  //temp conditions
  if (tempave > 35){
    temp_point = 7;
  }
  else if (tempave > 30 && tempave < 35){
    temp_point = 5;
  }
  else if (tempave > 25 && tempave < 30){
    temp_point = 3;  
  }
  else if (tempave > 20 && tempave < 25){
   temp_point = 0;
  }
  
  //humidity conditions
  if (humdave > 90 && humdave < 100){
    humidity_point = 8;
  }
  else if (humdave > 80 && humdave < 90){
    humidity_point = 8;
  }
  else if (humdave > 70 && humdave < 80){
    humidity_point = 6;
  }
  else if (humdave > 60 && humdave < 70){
    humidity_point = 4;
  }
  else if (humdave > 50 && humdave < 60){
    humidity_point = 2;
  }  
  else if (humdave > 40 && humdave < 50){
    humidity_point = 0;
  }
  else if (humdave > 30 && humdave < 40){
    humidity_point = 0;
  }
  else if (humdave > 20 && humdave < 30){
    humidity_point = 2;
  }
  else if (humdave > 10 && humdave < 20){
    humidity_point = 4;
  }
  else {
    humidity_point = 6;
  }
  
  //calculate comfort level
  comfort_level = temp_point + humidity_point + pressure_point;
  
  screen.fill(0,0,0);
  
  if (comfort_level > 18){
    screen.fill(255,0,0);
  }
  else if (comfort_level > 15){
    screen.fill(255,100,100);
  }
  else if (comfort_level > 12){
    screen.fill(255,150,150);
  }
  else if (comfort_level > 9){
    screen.fill(255,150,0);
  }
  else if (comfort_level > 6){    
    screen.fill(255,200,0);
  }
  else if (comfort_level > 3){    
    screen.fill(125,255,125);
  }
  else {
    screen.fill(125,125,255);
  }
  screen.circle(93, 60, screen.height() * 0.18);
  
  screen.fill(0,0,0);
  screen.stroke(0,0,0);
  if (comfort_level > 6){
    screen.line(80,70,105,70);
  }
  else if (comfort_level > 3){
    screen.circle(93,70,8);
    screen.fill(125,255,125);
    screen.stroke(125,255,125);
    screen.rect(83,60,20,10);
  }
  else {
    screen.circle(93,70,8);
    screen.fill(125,125,255);
    screen.stroke(125,125,255);
    screen.rect(83,60,20,10);
  }
  screen.fill(0,0,0);
  screen.stroke(0,0,0);
  screen.circle(83,52,3);
  screen.circle(102,52,3);
  screen.stroke(0,0,255);
  screen.text("Risk of Rain:%0", 35, 20); // placeholder for precipitation since pressure sensor is broken
}


//60-120 Very bright
//120-200 Bright
//200-250 Dim
//250-320 Very Dim
//320-340 Dark
//340+ Pitch Blackness
