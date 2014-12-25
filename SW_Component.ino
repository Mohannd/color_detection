#include <Wire.h>
#include "Adafruit_TCS34725.h"

//Linking Vibration Names to Numbers for Easier Mapping

//Finger One
#define v1 2
#define v2 3
#define v3 5



Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  //Serial begin, between Arduino and PC For Serial Monitor
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // Vibration Definition Pins
  pinMode(v1, OUTPUT);
  pinMode(v2, OUTPUT);
  pinMode(v3, OUTPUT);
}

void loop() {
  
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(50);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  
  

  // Convert the Reading from Sensor To RGB Format
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  

  Serial.print("\tR:\t"); Serial.print((int)r);
  Serial.print("\tG:\t"); Serial.print((int)g);
  Serial.print("\tB:\t"); Serial.print((int)b);
  
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  vibration((int)r,(int)g,(int)b,v1,v2,v3);
  
  
}

void vibration(int r,int g, int b,int pin1,int pin2, int pin3)
{
  analogWrite(pin1, (int)r);
  analogWrite(pin2, (int)g);
  analogWrite(pin3, (int)b);
  
}  
  
