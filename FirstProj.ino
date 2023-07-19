int trigPin = 9;    // TRIG pin
int echoPin = 8; // ECHO pin
int ledpin = 7; //LED pin
float threshold = 112.00;
int buzzpin = 6;

float duration_us, distance_cm;

void setup() {
  // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  // config the LED
  pinMode(ledpin,OUTPUT);
  pinMode(buzzpin,OUTPUT);
}
//print fucntion using pass by reference
void print(float* distance_cm){
  Serial.print("distance: ");
  Serial.print(*distance_cm);
  Serial.println(" cm");
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  
  if(distance_cm < threshold){
    digitalWrite(buzzpin,HIGH);
    digitalWrite(ledpin,HIGH);
    delay(1000);
  }
  else{
    digitalWrite(buzzpin,LOW);
    digitalWrite(ledpin,LOW);
  }

  //call to print
  print(&distance_cm);

  delay(500);
}

