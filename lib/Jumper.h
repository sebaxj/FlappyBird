#ifndef _Jumper_h
#define _Jumper_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

class Jumper {
  public:
    Jumper();
    int getHeight();
    void setHeight(int newHeight);
    
    float getVel();
    void setVel(float newVel);

    float getGrav();
    void setGrav(float newGrav);

    bool validHeight(int check);

    void jump(float thrust);

    int getX();

  private:
    double vy;
    double gy;
    int height;
    int x;
};

#endif
