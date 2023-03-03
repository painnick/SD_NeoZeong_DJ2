#include <Arduino.h>

#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems

#include "esp_log.h"

#define MAIN_TAG "Main"


#define PIN_SHOULDER_B 33
#define PIN_ARMFIT_B 32
#define PIN_FINGER_B 27
#define PIN_SHOULDER_G 26
#define PIN_WAIST_G 25
#define PIN_SKIRT_O 23
#define PIN_SKIRT_R 22
#define PIN_SKIRT_B 21
#define PIN_TABLE_R 19
#define PIN_BELLY_O 18

#define CH_SHOULDER_B 0
#define CH_ARMFIT_B 1
// #define CH_FINGER_B 2
#define CH_SHOULDER_G 2
#define CH_WAIST_G 3
#define CH_SKIRT_O 4
// #define CH_SKIRT_R 6
#define CH_SKIRT_B 5
#define CH_TABLE_R 6
#define CH_BELLY_O 7

#define FREQ 5000
#define RESOLUTION 8

#define MIN_BRIGHT 0
#define MAX_BRIGHT 255

#define SETUP_LED(NAME) ledcSetup(CH_ ## NAME, FREQ, RESOLUTION)
#define ATTACH(NAME) ledcAttachPin(PIN_ ## NAME, CH_ ## NAME)
#define OFF(NAME) ledcWrite(CH_ ## NAME, 0)

void setup() {

  ESP_LOGI(MAIN_TAG, "Setup!");

  SETUP_LED(SHOULDER_B);
  SETUP_LED(ARMFIT_B);
  // SETUP_LED(FINGER_B);
  SETUP_LED(SHOULDER_G);
  SETUP_LED(WAIST_G);
  SETUP_LED(SKIRT_O);
  // SETUP_LED(SKIRT_R);
  SETUP_LED(SKIRT_B);
  SETUP_LED(TABLE_R);
  SETUP_LED(BELLY_O);

  pinMode(PIN_FINGER_B, OUTPUT);
  pinMode(PIN_SKIRT_R, OUTPUT);

  ATTACH(SHOULDER_B);
  ATTACH(ARMFIT_B);
  // ATTACH(FINGER_B);
  ATTACH(SHOULDER_G);
  ATTACH(WAIST_G);
  ATTACH(SKIRT_O);
  // ATTACH(SKIRT_R);
  ATTACH(SKIRT_B);
  ATTACH(TABLE_R);
  ATTACH(BELLY_O);
}

void fade(uint8_t ch, int step_bright, uint8_t step_delay_ms) {
  int bright = 0;
  for(int i = MIN_BRIGHT; i <= MAX_BRIGHT; i += step_bright) {
    bright = min(i, MAX_BRIGHT);
    ledcWrite(ch, bright);
    delay(step_delay_ms);
  }
  for(int i = MAX_BRIGHT; i >= MIN_BRIGHT; i -= step_bright) {
    bright = max(i, MIN_BRIGHT);
    ledcWrite(ch, bright);
    delay(step_delay_ms);
  }
  ledcWrite(ch, 0);
}

void flickr(uint8_t pin, uint8_t delay_ms, int times) {
  for (int i = 0; i < times; i ++) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}

void loop() {
  fade(CH_SHOULDER_B, 8, 25);
  fade(CH_ARMFIT_B, 8, 25);
  
  flickr(PIN_FINGER_B, 500, 6);

  fade(CH_SHOULDER_G, 8, 25);
  fade(CH_WAIST_G, 8, 25);
  fade(CH_SKIRT_O, 8, 25);

  flickr(PIN_SKIRT_R, 500, 5);

  fade(CH_SKIRT_B, 8, 25);
  fade(CH_TABLE_R, 8, 25);
  fade(CH_BELLY_O, 8, 25);

  delay(1000 * 3);
}
