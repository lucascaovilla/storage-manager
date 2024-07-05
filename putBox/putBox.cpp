#include "putBox.h"
#include "waitDelay.h"
#include "home.h"

int putBox(int height, int cylinder, int cylinderPosition, int direction, int pulse){
    height += 10;
    home();
    waitDelay();
    // Advance the cylinder to grab the box
    digitalWrite(cylinder, LOW);
    waitDelay();
    // Move the table 10mm upwards to grab the box
    digitalWrite(direction, HIGH);
    for(int x = 0; x < (400 * 5); x++) {
        digitalWrite(pulse, HIGH); 
        delayMicroseconds(500);
        digitalWrite(pulse, LOW); 
        delayMicroseconds(500); 
    }
    waitDelay();
    // Retrieve cylinder to regular position
    while(!digitalRead(cylPosition)){
        digitalWrite(cylinder, HIGH);
        waitDelay();
    }
    waitDelay();
    // Move the table to the required floor
    digitalWrite(direction, HIGH);
    for(int x = 0; x < (400 * height); x++) {
        digitalWrite(pulse, HIGH); 
        delayMicroseconds(500);
        digitalWrite(pulse, LOW); 
        delayMicroseconds(500); 
    }
    waitDelay();
    // Advance cylinder to return the box
    digitalWrite(cylinder, LOW);
    waitDelay();
    home();
    waitDelay();
    // Retrieve cylinder to regular position
    while(!digitalRead(cylPosition)){
        digitalWrite(cylinder, HIGH);
        waitDelay();
    }
    waitDelay();
    home();
    waitDelay();
    return 0;
}
