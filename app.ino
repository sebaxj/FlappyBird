#include "Arduino.h"
#include <CapacitiveSensor.h>

const byte SEND = A4;
const byte RECEIVE = A5;
CapacitiveSensor   sensor = CapacitiveSensor(SEND, RECEIVE);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setup()                    
{

   sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);


  for (int pin = 0; pin < 8; pin++) {
    pinMode(ANODE_PINS[pin], OUTPUT);
    digitalWrite(ANODE_PINS[pin], HIGH);
    pinMode(CATHODE_PINS[pin], OUTPUT);
    digitalWrite(CATHODE_PINS[pin], HIGH);
  }

}

void loop()                    
{
    long start = millis();
    long total =  sensor.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug window spacing

    Serial.println(total);                  // print sensor output

    if (total > 1500) {
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
    } else {
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH);
    }
    delay(10);                             // arbitrary delay to limit data to serial port 
}