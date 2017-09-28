#include <SPI.h>
#include <TFT.h>            // Arduino TFT library

#define cs   10
#define dc   8
#define rst  9

TFT screen = TFT(cs, dc, rst);

void setup() {
  // initialize the screen
  screen.begin();

  // make the background black
  screen.background(0,0,0);

  // set the text color to white
  screen.stroke(255,255,255);

  // write text to the screen in the centre
  screen.text("Hello World!", 65, 60);
}

void loop() {
  
  screen.noStroke();
  screen.fill(random(0,255),random(0,255),random(0,255));
  screen.circle(random(30,200),random(0,200),random(1,5));
  delay(10);
}
