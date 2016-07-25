#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

char auth[] = ""; // Your blynk project auth key
char ssid[] = ""; // Your wifi ssid
char pass[] = ""; // Your wifi password

#define PIN D1 // pin attach to the neopixel DIN
#define NUM_LEDS 8 // number of leds (adafruit neopixel stick)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  strip.begin();
  strip.show();
}

BLYNK_WRITE(V1)
{
  int buttonValue = param.asInt();
  if (buttonValue == 1)
  {
    FadeInOut(0x00, 0xff, 0x00);
  }
  else
  {
    strip.clear();
    strip.show();
  }
}

void loop() {
  Blynk.run();
}

void FadeInOut(byte red, byte green, byte blue) {
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    strip.show();
    delay(3);
  }

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    strip.show();
    delay(3);
  }
}



void setPixel(int Pixel, byte red, byte green, byte blue) {
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  strip.show();
}

