//pin values 
const int trigPin = 9;
const int echoPin = 8;
const int ledpin = 7;
const int buzzpin = 6;

# define THRES 112.00

void setup() {
  //begin serial port
  Serial.begin (9600);

  //config pins to respective Input/Output mode 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
}

//alarm function using pass by reference
void alarm(const float* const distance_cm){
  if(*distance_cm < THRES){
    for(int i = 0;i<100;i++){
      digitalWrite(buzzPin, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(buzzPin, LOW);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
  }
  else{
    digitalWrite(buzzPin, LOW);
    digitalWrite(ledPin, LOW);
  }
}

//print to serial monitor function using pass by reference
void print(const float* const distance_cm){
  Serial.print("distance: ");
  Serial.print(*distance_cm);
  Serial.println(" cm");
}

void loop() {
  //defining floats here saves roughly 1% of storage (3888 to 3816 bytes)
  float duration_us, distance_cm;

  //10-microsecond pulse generated to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  //calculate distance
  distance_cm = 0.017 * duration_us;
  
  //call to the alarm
  alarm(&distance_cm);

  //call to print
  print(&distance_cm);

  delay(500);
}

