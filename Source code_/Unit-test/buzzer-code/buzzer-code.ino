#define BUZZER 32

// Intro du jeu Mario-Bros
void bip(int duree) {
  digitalWrite(BUZZER, HIGH);
  delay(duree);
  digitalWrite(BUZZER, LOW);
  delay(60);
}

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
bip(100);
  delay(100);

  bip(100);
  delay(100);

  bip(250);  

  delay(2000);
  
}