/*Avant de compiler le code veiller télécharger dans le gestionnaire de carte la version 2.0.17 de l’esp32 , 
si vous avez une version supérieur veiller la désinstaller d’abord*/ 

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <Adafruit_NeoPixel.h>

// NEOPIXEL 
#define PIN 18
#define NUMPIXELS 1

Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// MOTEURS 
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

// ULTRASON 
#define TRIG_PIN 14
#define ECHO_PIN 12

// CAPTEURS IR 
#define FRONT_PIN 34
#define BACK_PIN 35

// LED 
#define LED1 4
#define LED2 5
#define LED3 22
#define LED4 23

// BUZZER 
#define BUZZER 32

// PARAMETRES 
#define DISTANCE_SECURITE_1 5
#define DISTANCE_SECURITE_2 3

// ETATS 
int mode = 0; // 0 Manuel, 1 Semi-auto, 2 Auto
bool lastSelect = false;

bool ledAvant = false;
bool lastTriangle = false;

// PROTOTYPES 
void Manuel();
void Semiauto();
void Auto();

void avancer();
void reculer();
void tournerDroite();
void tournerGauche();
void stopRobot();

float lireDistance();
void bip(int duree);
void updatePhares();

void setup() {

  Dabble.begin("PathFinder");

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

  pixel.begin();
  pixel.setBrightness(255);

  pixel.setPixelColor(0, pixel.Color(255,0,0));
  pixel.show();

  randomSeed(micros());

  stopRobot();

  bip(100); delay(100);
  bip(100); delay(100);
  bip(250);

  delay(1500);
}

void loop() {

  Dabble.processInput();

  bool presentSelect = GamePad.isSelectPressed();
  bool presentTriangle = GamePad.isTrianglePressed();

  // PHARES 
  if (presentTriangle && !lastTriangle) {
    ledAvant = !ledAvant;
  }
  lastTriangle = presentTriangle;
  updatePhares();

  //  MODE 
  if (presentSelect && !lastSelect) {

    mode++;
    if (mode > 2) mode = 0;

    if (mode == 0) {
      pixel.setPixelColor(0, pixel.Color(255,0,0));
      bip(100);
    }
    else if (mode == 1) {
      pixel.setPixelColor(0, pixel.Color(0,0,255));
      bip(100); bip(100);
    }
    else {
      pixel.setPixelColor(0, pixel.Color(0,255,0));
      bip(100); bip(100); bip(100);
    }

    pixel.show();
    delay(200);
  }

  lastSelect = presentSelect;

  if (mode == 0) Manuel();
  else if (mode == 1) Semiauto();
  else Auto();

  digitalWrite(BUZZER, GamePad.isCrossPressed());
}

void updatePhares() {
  digitalWrite(LED1, ledAvant);
  digitalWrite(LED2, ledAvant);
}

void avancer() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void reculer() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}

void tournerDroite() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void tournerGauche() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

// ULTRASON 
float lireDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duree = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duree == 0) return 999;

  return duree * 0.0343 / 2.0;
}

void bip(int duree) {
  digitalWrite(BUZZER, HIGH);
  delay(duree);
  digitalWrite(BUZZER, LOW);
  delay(60);
}

void Manuel() {

  if (GamePad.isUpPressed()) avancer();
  else if (GamePad.isDownPressed()) reculer();
  else if (GamePad.isLeftPressed()) tournerGauche();
  else if (GamePad.isRightPressed()) tournerDroite();
  else stopRobot();
}

void Semiauto() {

  float d = lireDistance();

  if (d < DISTANCE_SECURITE_2) {
    stopRobot();
    delay(200);
    reculer();
    delay(400);
    stopRobot();
    return;
  }

  if (GamePad.isUpPressed()) avancer();
  else if (GamePad.isDownPressed()) reculer();
  else if (GamePad.isLeftPressed()) tournerGauche();
  else if (GamePad.isRightPressed()) tournerDroite();
  else stopRobot();
}

void Auto() {

  float d = lireDistance();

  if (d < DISTANCE_SECURITE_1) {

    stopRobot();
    delay(200);
    reculer();
    delay(400);

    if (random(0,2) == 0) tournerGauche();
    else tournerDroite();

    delay(500);
    stopRobot();
  }
  else {
    avancer();
  }
}