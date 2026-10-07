#include <Adafruit_NeoPixel.h>

#define PIN 6          // Broche DIN
#define NUMPIXELS 1    // Nombre de LEDs

Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();
  pixel.setBrightness(255); // Luminosité (0 à 255)
}

void loop() {

  // Rouge
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();
  delay(1000);

  // Vert
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  pixel.show();
  delay(1000);

  // Bleu
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));
  pixel.show();
  delay(1000);

  // Blanc
  pixel.setPixelColor(0, pixel.Color(255, 255, 255));
  pixel.show();
  delay(1000);

  // Éteindre
  pixel.clear();
  pixel.show();
  delay(1000);
}