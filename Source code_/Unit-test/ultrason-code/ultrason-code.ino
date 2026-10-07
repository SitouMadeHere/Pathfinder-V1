
const int trigPin = 14;
const int echoPin = 12;

#define SOUND_SPEED 0.034

long duration;
float distance;

void setup() {
  Serial.begin(115200); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * SOUND_SPEED/2;
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(100);
}