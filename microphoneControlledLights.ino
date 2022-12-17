 #include <FastLED.h>

FASTLED_USING_NAMESPACE


#define NUM_LEDS    290
#define NUM_MODE 6
CRGB leds[NUM_LEDS];

int hue = 0;
int mode = 0;
int points[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20};
int hall[20] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void smooth () {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(round(hue/5), 255, 190);
  }
}

void backNForth () {
  for (int i = 0; i < 20; i++) {
    leds[points[i]] = CHSV(hue+i*5, 255, round((i) * 255.0/20.0));
  }
}

void purple() {
  
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(200, 255, 190);
  }
}

void doRainbow() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(i+hue, 255, 190);
  }
}

void black () {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(23,255,0);  
  }
}

void epelipsi () {
  int col = random(360);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(col, 255, 255);
  }
}

int (*functions[])() = {smooth, backNForth, purple, doRainbow, epelipsi, black};

void setup() {
  Serial.begin(9600);
  delay(3000);
  FastLED.addLeds<WS2812B, 3, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(96);
}

void loop() {
  int recv = Serial.read();
  if (recv == 49) {
    black();
    mode += 1;
    mode = mode % NUM_MODE;
  }

  functions[mode]();

  FastLED.show();

  FastLED.delay(1000/60);

  hue += 5;
  for (int i = 0; i < 20; i++) {
    points[i] += hall[i];
    if (points[i] >= NUM_LEDS-1) {
      hall[i] = 0 - hall[i];
    } else if (points[i] <= 0) {
      hall[i] = 0 - hall[i];
    }
    
  }
  
  Serial.println(hue);

}
