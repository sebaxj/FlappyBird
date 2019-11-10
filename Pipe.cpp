#include "Pipe.h"

#if (ARDUINO >= 100) 
  #include "Arduino.h"
 #else 
  #include "WProgram.h"
#endif

Pipe::Pipe(int startX) {
  this->vx = -1/1500.0;
  this->x = startX;
  this->gapRange = 3;
  generateRandomGap();
}


void Pipe::generateRandomGap() {
  int base = 0;//random(0, 6);  // the base of any obstacle will be 0-5
  this->gapBase = base;
}

int Pipe::getGapBase() {
  return this->gapBase;
}

int Pipe::getGapRange() {
  return this->gapRange;
}

void Pipe::printGap() {
  for (int i = 0; i < this->gapRange; i++) {
    Serial.print(this->gapBase + i); Serial.print(" ");
  }
}

void Pipe::setVel(float newVx) {
  this->vx = newVx;
}

float Pipe::getVel() {
  return this->vx;
}

void Pipe::setX(int newX) {
  this->x = newX;
}

int Pipe::getX() {
  return this->x;
}

