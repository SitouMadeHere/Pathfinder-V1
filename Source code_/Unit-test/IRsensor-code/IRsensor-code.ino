#define FRONT_PIN 34 
#define BACK_PIN 35

void setup() {
  Serial.begin(9600);
  pinMode(FRONT_PIN, INPUT);
  pinMode(BACK_PIN, INPUT);
}

void loop() {
  int front = digitalRead(FRONT_PIN);
  int back = digitalRead(BACK_PIN);

  if (front == 1)
    Serial.print("front obstacle | ");
  else
    Serial.print("not front obstacle | ");
  if (back == 1)
    Serial.println("back obstacle");
  else
    Serial.println("not back obstacle");
  delay(100);
}
