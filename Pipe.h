#ifndef _Pipe_h
#define _Pipe_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

class Pipe {
  public:

    Pipe(int startX);
      
    void setVel(float newVx);
    float getVel();

    void setX(int newX);
    int getX();

    void setBase(int y);
    int getBase();
    int generateRandomBase();

    void setOpening(int y);
    int getOpening();

  private:
    float vx;
    int x;
    int base; // y-location of the base of the opening 
                // (part of the pipe, not part of the opening)
    int baseRange;
  
};

#endif
