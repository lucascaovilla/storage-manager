#include "home.h"

void home(int cylinder, int direction, int homePosition, int pulse) {
  digitalWrite(cylinder, HIGH);
  waitDelay();
  digitalWrite(direction, LOW);
  while(!digitalRead(homePosition)){
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500);
  }
  Serial.println(digitalRead(homePosition));
  waitDelay();
}
