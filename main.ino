#include "setup.h"
#include "wait.h"
#include "home.h"
#include "getBox.h"
#include "putBox.h"


#define finGet 3 
#define finReturn 4 
#define cylinder 5 

#define homePosition A4 
#define cylinderPosition A5 

#define pulse 8 
#define direction  9 
#define enable 10 

#define bitZeroLayer 11 
#define bitOneLayer 12 
#define bitTwoAction 13 

void setup() {
  pinMode(bitZeroLayer, INPUT);
  pinMode(bitOneLayer, INPUT);
  pinMode(bitTwoAction, INPUT);
  pinMode(finGet, OUTPUT);
  pinMode(finReturn, OUTPUT);
  pinMode(cylinder, OUTPUT);
  pinMode(homePosition, INPUT);
  pinMode(cylinderPosition, INPUT);
  pinMode(pulse, OUTPUT);
  pinMode(direction, OUTPUT);
  pinMode(enable, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int firstFloor = 64; // Floor 1 = 125mm (135mm)
  int secondFloor = 117;  // Floor 2 = 245mm (255mm)
  int thirdFloor = 190; // Floor 3 = 365mm (375mm)
  digitalWrite(finReturn, HIGH);
  digitalWrite(finGet, HIGH);
  digitalWrite(cylinder, HIGH);

  // 0, 1, 0 - Get the box on the first floor
  if(digitalRead(!bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(!bitTwoAction)){
    getBox(firstFloor, cylinder, cylinderPosition, direction, pulse);
    delay(1000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }
  // 1, 0, 0 - Get the box on the second floor
  if(digitalRead(bitZeroLayer) && digitalRead(!bitOneLayer) && digitalRead(!bitTwoAction)){
    Serial.println(digitalRead(homePosition));
    getBox(secondFloor, cylinder, cylinderPosition, direction, pulse);
    delay(10000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }
  // 1, 1, 0 - Get the box on the third floor
  if(digitalRead(bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(!bitTwoAction)){
    getBox(thirdFloor, cylinder, cylinderPosition, direction, pulse);
    delay(10000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }

  // 0, 1, 1 - Return the box to the first floor
  if(digitalRead(!bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(bitTwoAction)){
    returnBox(firstFloor, cylinder, cylinderPosition, direction, pulse);
  }
  // 1, 0, 1 - Return the box to the second floor
  if(digitalRead(bitZeroLayer) && digitalRead(!bitOneLayer) && digitalRead(bitTwoAction)){
    returnBox(secondFloor, cylinder, cylinderPosition, direction, pulse);
  }
  // 1, 1, 1 - Return the box to the third floor
  if(digitalRead(bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(bitTwoAction)){
    returnBox(thirdFloor, cylinder, cylinderPosition, direction, pulse);
  }
  waitDelay();
}