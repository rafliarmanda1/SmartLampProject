const int relay_led = 5;

// LDR Sensor
//int ldrPin = A1zz;
//int dataLDR = 0;

//Ultrasonic Declar
#define echo 4
#define trig 3
long duration;
int distance;

//PIR
int pir = 6;
int pirstat = 0;

//bluetooth
char Incoming_value = 0;

void setup() {
  Serial.begin(9600);

  //  relay
  pinMode(relay_led, OUTPUT);

  // LDR
//  pinMode(ldrPin, INPUT);  

  //Ultrasonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // PIR
  pinMode(pir, INPUT);
}

void ultraSonic() {
  // PIR
  pirstat = digitalRead(pir);
    
  //  Ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 20  && pirstat == 1) {
    digitalWrite(relay_led, LOW);
    delay(5000);
  } else if (distance > 20 && pirstat == 0) {
    digitalWrite(relay_led, HIGH);
  }
}

void bluetooth() {
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(relay_led, LOW);  
    else if(Incoming_value == '0')       
      digitalWrite(relay_led, HIGH);   
  } else if(Incoming_value != '1'  && Incoming_value != '0'){
    ultraSonic();
  }
}

//void LightDR() {
//  dataLDR = digitalRead(ldrPin);
//  Serial.print("Data LDR: ");
//  Serial.println(dataLDR);
//  delay(500);
//}

void loop() {
  bluetooth();
}
