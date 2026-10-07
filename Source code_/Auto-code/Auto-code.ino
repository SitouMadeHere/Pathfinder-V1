
// RELIER LES PINS ENABLE AU +5V
// Moteurs
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

// Ultrason
#define TRIG_PIN 14
#define ECHO_PIN 12

// CAPTEUR IR
#define FRONT_PIN 34 
#define BACK_PIN 35

// SIGNALISATION

#define LED1	4
#define LED2	5
#define LED3	22
#define LED4	23

// BUZZER
#define BUZZER 32

// Distance minimale avant obstacle (cm)
#define DISTANCE_SECURITE 5


// =========================
// FONCTIONS MOTEURS
// =========================

void avancer() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  digitalWrite(LED1, 1);
  digitalWrite(LED2, 1);
  digitalWrite(LED3, 0);
  digitalWrite(LED4, 0);
}

void reculer() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  digitalWrite(LED1, 0);
  digitalWrite(LED2, 0);
  digitalWrite(LED3, 1);
  digitalWrite(LED4, 1);
}

void tournerGauche() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(LED1, 0);
  digitalWrite(LED2, 1);
  digitalWrite(LED4, 1);
  digitalWrite(LED3, 0);
}

void tournerDroite() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  digitalWrite(LED1, 1);
  digitalWrite(LED2, 0);
  digitalWrite(LED3, 1);
  digitalWrite(LED4, 0);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(LED1, 0);
  digitalWrite(LED2, 0);
  digitalWrite(LED3, 0);
  digitalWrite(LED4, 0);
}


// =========================
// MESURE ULTRASON
// =========================

float lireDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duree = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duree == 0) {
    return 999;
  }

  float distance = duree * 0.0343 / 2.0;

  return distance;
}

// =========================
// BIP BUZZER
// =========================
void bip(int duree) {
  digitalWrite(BUZZER, HIGH);
  delay(duree);
  digitalWrite(BUZZER, LOW);
  delay(60);
}


void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(FRONT_PIN, INPUT);
  pinMode(BACK_PIN, INPUT);

  pinMode(BUZZER, OUTPUT);

  stopRobot();

  bip(100);
  delay(100);

  bip(100);
  delay(100);

  bip(250);

  delay(2000);

  Serial.println("Robot prêt");
}



void loop() {

  float distance = lireDistance();

  int front = digitalRead(FRONT_PIN);
  int back = digitalRead(BACK_PIN);

  Serial.print("Distance: ");
  Serial.print(distance);

  Serial.print("  front:");
  Serial.print(front);

  Serial.print("  back:");
  Serial.println(back);

  // =====================
  // ANTI-CHUTE
  // =====================

  /* 
  if (front == LOW || back == LOW) {

    Serial.println("VIDE DETECTE");

    stopRobot();
    delay(200);

    reculer();
    delay(500);

    tournerDroite();
    delay(700);

    stopRobot();
    delay(100);

    return;
  }*/

  // =====================
  // EVITEMENT OBSTACLE
  // =====================

  if (distance < DISTANCE_SECURITE) {

    Serial.println("OBSTACLE DETECTE");

    stopRobot();
    delay(200);

    reculer();
    delay(400);

    // Choix aléatoire du sens
    if (random(0, 2) == 0) {

      tournerGauche();
      delay(600);

    } else {

      tournerDroite();
      delay(600);
    }

    stopRobot();
    delay(100);
  }

  else {

    avancer();
  }

  delay(50);
}