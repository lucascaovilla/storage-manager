#include "getBox.h"
#include "waitDelay.h"
#include "home.h"

int getBox(int height, int cylinder, int cylinderPosition, int direction, int pulse){
    home();
    waitDelay();
    // Move the table to the required floor
    digitalWrite(direction, HIGH);
    for(int x = 0; x < (400 * height); x++) {
        digitalWrite(pulse, HIGH); 
        delayMicroseconds(500);
        digitalWrite(pulse,LOW); 
        delayMicroseconds(500); 
    }
    waitDelay();
    // Extends the cylinder to reach the box
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
    while(!digitalRead(cylinderPosition)){
        digitalWrite(cylinder, HIGH);
        waitDelay();
    }
    waitDelay();
    home();
    waitDelay();
    // Move the table 10mm upwards to put the box
    digitalWrite(direction, HIGH);
    for(int x = 0; x < (400 * 10); x++) {
        digitalWrite(pulse, HIGH); 
        delayMicroseconds(500);
        digitalWrite(pulse, LOW); 
        delayMicroseconds(500); 
    }
    waitDelay();
    // Extend cylinder to put the box in the track
    digitalWrite(cylinder, LOW);
    waitDelay();
    // Return table to home position
    home();
    waitDelay();
    // Retrieve cylinder to regular position
    while(!digitalRead(cylinderPosition)){
        digitalWrite(cylinder, HIGH);
        waitDelay();
    }
    waitDelay();
    home();
    waitDelay();
    return 0;
}