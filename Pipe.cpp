#include "Pipe.h"

#if (ARDUINO >= 100) 
  #include "Arduino.h"
 #else 
  #include "WProgram.h"
#endif

Pipe::Pipe(int startX) {
  this->vx = -1/1500.0;
  this->x = startX;
  this->baseRange = 3;
  generateRandomBase();
}

Pipe::generateRandomBase() {
  this->base = random(0, 6);  // the base of any obstacle will be 0-5
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

void Pipe::setBase(int y) {
  this->base = y;
}

int Pipe::getBase() {
  return this->base;
}

void Pipe::setOpening(int y) {
  this->baseRange = y;
}

int Pipe::getOpening() {
  return this->baseRange;
}
