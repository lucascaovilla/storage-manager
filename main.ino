#define finGet 3 //OUTPUT - RELAY
#define finReturn 4 //OUTPUT - RELAY
#define cylinder 5 //OUTPUT - RELAY

#define homePosition A4 //INPUT - BUTTON
#define cylPosition A5 //INPUT - BUTTON

#define pulse 8 //OUTPUT - DRIVER
#define direction  9 //OUTPUT - DRIVER
#define enable 10 //OUTPUT - DRIVER

#define bitZeroLayer 11 //INPUT - RELAY
#define bitOneLayer 12 //INPUT - RELAY
#define bitTwoAction 13 //INPUT - RELAY

boolean up = HIGH;
boolean down = LOW;

void setup() {
  pinMode(bitZeroLayer, INPUT);
  pinMode(bitOneLayer, INPUT);
  pinMode(bitTwoAction, INPUT);
  pinMode(finGet, OUTPUT);
  pinMode(finReturn, OUTPUT);
  pinMode(cylinder, OUTPUT);
  pinMode(homePosition, INPUT);
  pinMode(cylPosition, INPUT);
  pinMode(pulse, OUTPUT);
  pinMode(direction, OUTPUT);
  pinMode(enable, OUTPUT);
  Serial.begin(9600);
}

void wait(){
  delay(2500);
}

void home() {
  Serial.println("Em direção à posição HOME");
  Serial.println(digitalRead(homePosition));
  digitalWrite(cylinder, HIGH);
  wait();
  digitalWrite(direction, down);
  while(!digitalRead(homePosition)){
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500);
  }
  Serial.println(digitalRead(homePosition));
  wait();
}


void getBox(int height){
  home();
  wait();
  // Move the table to the required floor
  Serial.println("Em direção ao andar selecionado");
  digitalWrite(direction, up);
  for(int x = 0; x < (400 * height); x++) {
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse,LOW); 
    delayMicroseconds(500); 
  }
  wait();
  // Extends the cylinder to reach the box
  Serial.println("Extendendo cilindro");
  digitalWrite(cylinder, LOW);
  wait();
  // Move the table 10mm upwards to grab the box
  digitalWrite(direction, up);
  Serial.println("Levantando a mesa para pegar a caixa");
  for(int x = 0; x < (400 * 5); x++) {
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500); 
  }
  wait();
  // Retrieve cylinder to regular position
  Serial.println("Recolhendo cilindro");
  while(!digitalRead(cylPosition)){
    digitalWrite(cylinder, HIGH);
    wait();
  }
  wait();
  home();
  wait();
  // Move the table 10mm upwards to put the box
  Serial.println("Levantando a mesa para entregar a caixa");
  digitalWrite(direction, up);
  for(int x = 0; x < (400 * 10); x++) {
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500); 
  }
  wait();
  // Extend cylinder to put the box in the track
  Serial.println("Extendendo cilindro");
  digitalWrite(cylinder, LOW);
  wait();
  // Return table to home position
  home();
  wait();
  // Retrieve cylinder to regular position
  Serial.println("Recolhendo cilindro");
  while(!digitalRead(cylPosition)){
    digitalWrite(cylinder, HIGH);
    wait();
  }
  wait();
  home();
  wait();
  // Return finished
  Serial.println("Retornando status para o CLP");
  digitalWrite(finGet, LOW);
  delay(1000);
  digitalWrite(finGet, HIGH);
  wait();
}

void returnBox(int height){
  height += 10;
  home();
  wait();
  // Advance the cylinder to grab the box
  Serial.println("Extendendo cilindro");
  digitalWrite(cylinder, LOW);
  wait();
  // Move the table 10mm upwards to grab the box
  Serial.println("Levantando a mesa para pegar a caixa");
  digitalWrite(direction, up);
  for(int x = 0; x < (400 * 5); x++) {
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500); 
  }
  wait();
  // Retrieve cylinder to regular position
  Serial.println("Recolhendo cilindro");
  while(!digitalRead(cylPosition)){
    digitalWrite(cylinder, HIGH);
    wait();
  }
  wait();
  // Move the table to the required floor
  Serial.println("Levando a caixa para o andar selecionado");
  digitalWrite(direction, up);
  for(int x = 0; x < (400 * height); x++) {
    digitalWrite(pulse, HIGH); 
    delayMicroseconds(500);
    digitalWrite(pulse, LOW); 
    delayMicroseconds(500); 
  }
  wait();
  // Advance cylinder to return the box
  Serial.println("Extendendo cilindro");
  digitalWrite(cylinder, LOW);
  wait();
  //Move the table 10mm downwards to release the box
  // Serial.println("Descendo a mesa para liberar a caixa");
  // digitalWrite(direction, down);
  // for(int x = 0; x < (400 * ); x++) {
  //   digitalWrite(pulse,HIGH); 
  //   delayMicroseconds(500);
  //   digitalWrite(pulse,LOW); 
  //   delayMicroseconds(500); 
  // }
  home();
  wait();
  // Retrieve cylinder to regular position
  Serial.println("Recolhendo o cilindro");
  while(!digitalRead(cylPosition)){
    digitalWrite(cylinder, HIGH);
    wait();
  }
  wait();
  home();
  wait();
  // Return finished
  Serial.println("Retornando status ao CLP");
  digitalWrite(finReturn, LOW);
  delay(1000);
  digitalWrite(finReturn, HIGH);
  wait();
}

void loop() {
  int firstFloor = 64; //Andar 1 = 125mm (135mm)
  int secondFloor = 117;  //Andar 2 = 245mm (255mm)
  int thirdFloor = 190; //Andar 3 = 365mm (375mm)
  digitalWrite(finReturn, HIGH);
  digitalWrite(finGet, HIGH);
  digitalWrite(cylinder, HIGH);
  // direction = High => Upwards
  // direction = Low => Downwards
  // 400 pulses = 1 revolution
  // thread step = 2mm/rev

  // digitalWrite(direction,HIGH);
  // for(int x = 0; x < (400 * revolutions); x++) {
  //   digitalWrite(pulse,LOW); 
  //   delayMicroseconds(500);
  //   digitalWrite(pulse,HIGH); 
  //   delayMicroseconds(500); 
  // }
  // delay(1000);
  

  // 0, 1, 0 - Get the box on the first floor
  if(digitalRead(!bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(!bitTwoAction)){
    Serial.println("Get the box on the first floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    getBox(firstFloor);
    Serial.println();
    delay(1000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }
  // 1, 0, 0 - Get the box on the second floor
  if(digitalRead(bitZeroLayer) && digitalRead(!bitOneLayer) && digitalRead(!bitTwoAction)){
    Serial.println(digitalRead(homePosition));
    Serial.println("Get the box on the second floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    getBox(secondFloor);
    Serial.println();
    delay(10000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }
  // 1, 1, 0 - Get the box on the third floor
  if(digitalRead(bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(!bitTwoAction)){
    Serial.println("Get the box on the third floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    getBox(thirdFloor);
    Serial.println();
    delay(10000);
    digitalWrite(finGet, LOW);
    delay(1000);
    digitalWrite(finGet, HIGH);
  }

  // 0, 1, 1 - Return the box to the first floor
  if(digitalRead(!bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(bitTwoAction)){
    //returnBox(firstFloor);
    Serial.println("Return the box to the first floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    Serial.println();
  }
  // 1, 0, 1 - Return the box to the second floor
  if(digitalRead(bitZeroLayer) && digitalRead(!bitOneLayer) && digitalRead(bitTwoAction)){
    //returnBox(secondFloor);
    Serial.println("Return the box to the second floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    Serial.println();
  }
  // 1, 1, 1 - Return the box to the third floor
  if(digitalRead(bitZeroLayer) && digitalRead(bitOneLayer) && digitalRead(bitTwoAction)){
    //returnBox(thirdFloor);
    Serial.println("Return the box to the third floor");
    Serial.print(digitalRead(bitZeroLayer));
    Serial.print(digitalRead(bitOneLayer));
    Serial.println(digitalRead(bitTwoAction));
    Serial.println();
  } 
  if(digitalRead(!bitZeroLayer) && digitalRead(!bitOneLayer) && digitalRead(!bitTwoAction)){
    Serial.println("No work");
  }

  wait();
}