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

const int temp_readings = 10;
const int humd_readings = 10;
const int atm_readings = 10;
/*
These constant ints are used to determine size of arrays
*/

int temp_average[temp_readings];
int humidity_average[humd_readings];
int atm_average[atm_readings];
/*
These are the readings from the sensor input
*/

int sensor_index; // the index of the current sensor input
// totals for sensor input index
int temp_total = 0;
int humd_total = 0;
int atm_total = 0;
//average for data
int tempave;
int humdave;
int atmave;

int photocellPin = A0;
int comfort_level;
int temp_point;
int humidity_point;
int pressure_point;
String photocellReading;
char Lightvalue[5];
char Tempvalue[5];
char Humvalue[5];
char Atmvalue[5];
double P,T;

void setup() {
  
  Serial.begin(9600);//start serial screen
  Serial.print("Serial Monitor Start!");
  
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
  
  for (int temp_reading = 0; temp_reading < temp_readings; temp_reading++)
  temp_average[temp_reading] = 0;
  for (int humd_reading = 0; humd_reading < humd_readings; humd_reading++)
  humidity_average[humd_readings] = 0;
  for (int atm_reading = 0; atm_reading < atm_readings; atm_reading++)
  atm_average[atm_readings] = 0;
  
}

void loop() {
  
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
  
  screen.text(Lightvalue, 135, 116);
  
  //print data in the serial screen
  Serial.print(" Temp: ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print("Humidity: ");
  Serial.print(Humvalue);
  Serial.print(" ");
  Serial.print("Pressure: ");
  Serial.print(p0);
  Serial.print(" ");
  Serial.println();
  
  
  delay(100);
  
  //reprint text but in white so it can refresh
  screen.stroke(255,255,255);
  screen.text(Lightvalue, 135, 116);
  screen.text(Humvalue, 142, 5);
  screen.text(Tempvalue, 35, 50);
  
  //This is to calculate the average of the sensor inputs
  
  //remove the last value in the array in order to add a new one
  temp_total = temp_total - temp_average[temp_readings];
  humd_total = humd_total - humidity_average[humd_readings];
  atm_total = atm_total - atm_average[atm_readings];
  //read from sensors
  temp_average[temp_readings] = temp;
  humidity_average[humd_readings] = humd;
  //atm_average[atm_readings] = 
  //add reading to total
  temp_total = temp_total + temp_average[temp_readings];
  humd_total = humd_total + humidity_average[humd_readings];
  //atm_total
  //move to next position in array
  sensor_index = sensor_index + 1;
  //if at end of index, reset to 0
  if (sensor_index >= 10){
    sensor_index = 0;
  }
  //calculate average of sensor inputs
  tempave = temp_total / temp_readings;
  humdave = humd_total / humd_readings;
  //atmave = atm_total / atm_readings;
  
  
  //add new value in
  
  
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
  
  screen.rect(screen.height()* 0.95, screen.height()* 0.20, 30, 40);
  
  
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
  
  screen.circle(135, 90, screen.height()* 0.15);

  // This is to visually display temperature values
  screen.stroke(0,0,0);
  if (temp > 35){
    screen.fill(255,0,0);
  }
  else if (temp > 30 && temp < 35){
    screen.fill(255,125,0);
  }
  else if (temp > 25 && temp < 30){
    screen.fill(255,200,0);
  }
  else if (temp > 20 && temp < 25){
    screen.fill(100,255,100);
  }   
  screen.circle(50, 90, screen.height() * 0.15);
  
  // comfort level works on a scale of 0-20, 0 being the ideal and 20 the least ideal

  //predict weather comfortness with averages with data
  //temp conditions
  if (tempave > 35){
    temp_point = 7;
  }
  else if (temp > 30 && temp < 35){
    temp_point = 5;
  }
  else if (temp > 25 && temp < 30){
    temp_point = 3;  
  }
  else if (temp > 20 && temp < 25){
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
    screen.fill(150,255,150);
  }
  else {
    screen.fill(150,150,255);
  }
  screen.circle(90, 90, screen.height() * 0.10);
}


//60-120 Very bright
//120-200 Bright
//200-250 Dim
//250-320 Very Dim
//320-340 Dark
//340+ Pitch Blackness
