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

BLYNK_WRITE(V2)
{
  int buttonValue = param.asInt();
  if (buttonValue == 1)
  {
    Strobe(0x00, 0xff, 0x00, 10, 50, 800);
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


void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    strip.show();
    delay(FlashDelay);
    setAll(0, 0, 0);
    strip.show();
    delay(FlashDelay);
  }

  delay(EndPause);
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

