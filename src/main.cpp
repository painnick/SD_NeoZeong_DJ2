#include <Arduino.h>

#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems

#include "esp_log.h"

#include <effectPwm.h>
#include <effectDigital.h>

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

bool seqFingerB[] = {true, false, false, false, false, false, false, false};
bool seqSoulderG[] = {true, false, false, false};
bool seqSkirtO[] = {true, false, false, false, false, false, false, false, false, false, false};
bool seqTableR[] = {true, false, false, false, false, false, false, false, false};

EffectPwm effectShouldB(PIN_SHOULDER_B, CH_SHOULDER_B);
EffectPwm effectArmFitB(PIN_ARMFIT_B, CH_ARMFIT_B, 100, 2);
EffectDigital effectFingerB(PIN_FINGER_B, seqFingerB, sizeof(seqFingerB), 100);
EffectDigital effectSoulderG(PIN_SHOULDER_G, seqSoulderG, sizeof(seqSoulderG), 300);
EffectDigital effectWaistG(PIN_WAIST_G, seqSoulderG, sizeof(seqSoulderG), 300);
EffectDigital effectSkirtO(PIN_SKIRT_O, seqSkirtO, sizeof(seqSkirtO), 100);
EffectDigital effectTableR(PIN_TABLE_R, seqTableR, sizeof(seqTableR), 100);

void setup() {
  ESP_LOGI(MAIN_TAG, "Setup!");

  pinMode(PIN_SKIRT_R, OUTPUT);
  digitalWrite(PIN_SKIRT_R, LOW);
}

void loop() {
  unsigned long now = millis();

  effectShouldB.loop(now);
  effectArmFitB.loop(now);
  effectFingerB.loop(now);
  effectSoulderG.loop(now);
  effectWaistG.loop(now);
  effectSkirtO.loop(now);
  effectTableR.loop(now);

  // fade(CH_ARMFIT_B, 8, 25);
  
  // flickr(PIN_FINGER_B, 500, 6);

  // fade(CH_SHOULDER_G, 8, 25);
  // fade(CH_WAIST_G, 8, 25);
  // fade(CH_SKIRT_O, 8, 25);

  // flickr(PIN_SKIRT_R, 500, 5);

  // fade(CH_SKIRT_B, 8, 25);
  // fade(CH_TABLE_R, 8, 25);
  // fade(CH_BELLY_O, 8, 25);

  // delay(10);
}
