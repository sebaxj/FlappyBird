#ifndef _Pipe_h
#define _Pipe_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

class Pipe {
  public:

    /* Initializes an obstacle */
    Pipe(int startX);
      
    /* Sets and retrieves the x velocity of an obstacle */
    void setVel(float newVx);
    float getVel();

    /* Sets and retrieves the x position of an obstacle */
    void setX(int newX);
    int getX();

    /* Creates and retrieves the coordinates of the obstacle's opening */
    void generateRandomGap();
    int getGapBase();
    int getGapRange();
    void printGap();

  private:
    /* The x velocity of the obstacle */
    float vx;
    
    /* The x position of the obstacle */
    int x;
    
    /* The size of the opening in the obstacle */
    int gapRange;
    
    /* The lowest row of the obstacle's opening */
    int gapBase;
  
};

#endif
