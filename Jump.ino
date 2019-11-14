#include "Arduino.h"
#include "CapacitiveSensor.h"
#include "Jumper.h"
#include "Pipe.h"

/*******************************/
/*  Constants and global vars  */
/*******************************/
const byte SEND = A4;
const byte RECEIVE = A5;
const byte ANODES[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte CATHODES[8] = {A3, A2, A1, A0, 5, 4, 3, 2};
CapacitiveSensor sensor = CapacitiveSensor(SEND, RECEIVE);
Jumper jumper;
Pipe pipe1(7), pipe2(12);
long vy_timer;
long grav_timer;
long pipe_timer;
unsigned int lives = 3;


/*******************************/
/*          Prototypes         */
/*******************************/
void displayJumper(Jumper &jumper);
void displayPipe(Pipe &pipe1);
void updatePipe(long &pipe_timer);
void updateKinematics(long &vy_timer, long &grav_timer, Jumper& jumper);
void updateVelocity(long &grav_timer, Jumper& jumper);
void updateHeight(long &vy_timer, Jumper& jumper);
bool playerTapsPlate(int threshold);
bool collisionDetected();
void gameOver();
void spellLetter();
void display(int pattern[8][8]);

void setup() {
  sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(115200); Serial.println("Baud set");
  
  for (int pin = 0; pin < 8; pin++) {
    pinMode(ANODES[pin], OUTPUT);
    digitalWrite(ANODES[pin], HIGH);
    pinMode(CATHODES[pin], OUTPUT);
    digitalWrite(CATHODES[pin], HIGH);
  }
  Serial.println("Pins set");

  vy_timer = millis();
  grav_timer = millis();
  pipe_timer = millis();
  Serial.println("Timers set");
}

void loop() {
  if (playerTapsPlate(700)) {
    jumper.jump(1/750.0);     // adds a thrust to the main player
  }

  updatePipes(pipe_timer);

  updateKinematics(vy_timer, grav_timer, jumper);
  displayJumper(jumper);
  displayPipe(pipe1);
  displayPipe(pipe2);

  if (collisionDetected()) {
    lives--;
    if(lives == 0) {
      gameOver();
      lives = 3;
    } else {
        for (int i = 0; i < 3; i++) {
          long time = millis();
          while (millis() - time < 150) {
            displayJumper(jumper);
            displayPipe(pipe1);
            displayPipe(pipe2);
        }
      } 
    }
  }
}

/* After a time interval specified by the pipes' velocity,
 *  the pipes will move one step towards the main player. If
 *  the pipes have already moved past the player, they will
 *  wrap around to the other side of the board.
 */
void updatePipes(long &pipe_timer) {
  long inverseVelocity = (long)abs(1/pipe1.getVel());
  int interval = 5;
  if (millis() - pipe_timer >= inverseVelocity) {
    if (pipe1.getX() > 0) {
      pipe1.setX(pipe1.getX() - 1);
    } else {
      pipe1.setX(pipe2.getX() + interval - 1);
      pipe1.generateRandomGap();
    }

    if (pipe2.getX() > 0) {
      pipe2.setX(pipe2.getX() - 1);
    } else {
      pipe2.setX(pipe1.getX() + interval);
      pipe2.generateRandomGap();
    }
    pipe_timer = millis();
    
  }
}

/* Updates the velocity and height of the main player */
void updateKinematics(long &vy_timer, long &grav_timer, Jumper& jumper) {
  updateVelocity(grav_timer, jumper);
  updateHeight(vy_timer, jumper);
}

/* After a time interval specified by the gravity parameter,
 *  the main player's y-velocity will decrement by 'gravity'.
 *  If the main player is on the floor or grazing the ceiling, 
 *  their velocity will not be affected by gravity (as it is 
 *  just going to be zero).
 */
void updateVelocity(long &grav_timer, Jumper &jumper) {
  long inverseGravity = (long)abs(1/jumper.getGrav());
  if (millis() - grav_timer >= inverseGravity) {
    if (jumper.getHeight() == 7) {
      jumper.setVel(0.0);
    }
    if (jumper.getHeight() > 0) { // if jumper above ground, decrease vy further
      float newVelocity = jumper.getVel() - jumper.getGrav();
      jumper.setVel(newVelocity);
    } else if (jumper.getHeight() <= 0 && jumper.getVel() < 0) { // if jumper at ground, set vy to 0 -> shouldn't be moving up or down
      jumper.setVel(0.0);
      jumper.setHeight(0);
    }
    grav_timer = millis();
  }
}

/* After a time interval specified by the main player's
 *  velocity, the main players y-position will go up or
 *  down depending on the sign of their velocity.
 */
void updateHeight(long& vy_timer, Jumper& jumper) {
  // if velocity is 0, don't update height
  // if velocity is non-zero, then change height accordingly
  if (jumper.getVel() != 0.0) {
    long inverseSpeed = (long) abs(1/jumper.getVel());
    if (millis() - vy_timer >= inverseSpeed) { 
      if (jumper.getVel() > 0.0 && jumper.getHeight() < 7) {
        jumper.setHeight(jumper.getHeight() + 1);
      } else if (jumper.getVel() < 0.0 && jumper.getHeight() > 0) {
        jumper.setHeight(jumper.getHeight() - 1);
      }
      vy_timer = millis();
    }
  }
}

/* Detects if the layer has tapped the plate */
bool playerTapsPlate(int threshold) {
  long total = sensor.capacitiveSensor(15);
  if (total > threshold) {
      return true;
  }
  return false;
}

void displayJumper(Jumper &jumper) {
  digitalWrite(CATHODES[jumper.getX()], LOW);
  int row = 7 - jumper.getHeight();         // invert because a height of 0 will correspond 
                                            // to the top LED
  digitalWrite(ANODES[row], LOW);

  delayMicroseconds(500);

  digitalWrite(ANODES[row], HIGH);
  digitalWrite(CATHODES[jumper.getX()], HIGH);
}

void displayPipe(Pipe &pipe) {
  int col = pipe.getX(); 
  for (int row = 0; row < 8; row++) {
    digitalWrite(ANODES[row], LOW);
    if (row < pipe.getGapBase() || 
          row > pipe.getGapBase() + pipe.getGapRange() - 1) {
      digitalWrite(CATHODES[col], LOW);
    }
    delayMicroseconds(500);
    digitalWrite(CATHODES[col], HIGH);
    digitalWrite(CATHODES[col], HIGH);
    digitalWrite(ANODES[row], HIGH);
  }
}

bool collisionDetected() {
  int height = 7 - jumper.getHeight();
  if (jumper.getX() == pipe1.getX()) {
    if (height < pipe1.getGapBase() ||
          height > pipe1.getGapBase() + pipe1.getGapRange() - 1) {
            return true;
    }
  } else if (jumper.getX() == pipe2.getX()) {
      if (height < pipe2.getGapBase() ||
            height > pipe2.getGapBase() + pipe2.getGapRange() - 1) {
            return true;
      }
  }
  return false;
}

/* Display will blink 3 times, then display "Game Over" */
void gameOver() {
  for (int i = 0; i < 3; i++) {
    long time = millis();
    while (millis() - time < 150) {
      displayJumper(jumper);
      displayPipe(pipe1);
      displayPipe(pipe2);
    }
    spellLetter();
  }
}

void spellLetter() {
  int on[8][8];
  int off[8][8];
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      on[row][col] = 1;
      off[row][col] = 0;
    }
  }
  unsigned long time = millis();
  while (millis() - time < 250) {
    display(on);
  }
  time = millis();
  while (millis() - time < 250) {
    display(off);
  }
}

void display(int pattern[8][8]) {
  int maxBrightness = 15;
  for (int row = 0; row < 8; row++) {
    digitalWrite(ANODES[row], LOW);
    for (int col = 0; col < 8; col++) {
      int brightness = pattern[row][col];
      if (brightness >= 1) {
        digitalWrite(CATHODES[col], LOW);
        delayMicroseconds(brightness);
        digitalWrite(CATHODES[col], HIGH);
        delayMicroseconds(maxBrightness - brightness);
      }
    }
    digitalWrite(ANODES[row], HIGH);
  }
}
 
