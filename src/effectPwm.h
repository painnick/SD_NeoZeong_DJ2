#pragma once

#include <Arduino.h>

#define LOG_TAG "EFFTECT"

#define EFFECT_PWM_FREQ 5000
#define EFFECT_PWM_RESOLUTION 8

class EffectPwm {
public:
    EffectPwm(uint8_t pin, uint8_t ch, int stDelayMs = 25, int stBright = 8, int minB = 0, int maxB = 255) :
        channel(ch),
        stepBright(stBright),
        stepDelayMs(stDelayMs),
        currentBright(minB),
        minBright(minB),
        maxBright(maxB),
        inc(true),
        lastProcessed(0) {
        ledcSetup(ch, EFFECT_PWM_FREQ, EFFECT_PWM_RESOLUTION);
        ledcAttachPin(pin, ch);
    }

    void loop(unsigned long now) {
        if (now - lastProcessed > stepDelayMs) {
            lastProcessed = now;
            process();
        }
    }

    void process() {
        if (inc) {
            currentBright += stepBright;
        } else {
            currentBright -= stepBright;
        }

        if (currentBright > maxBright) {
            inc = false;
            currentBright = min(currentBright, maxBright);
        }
        if (currentBright < minBright) {
            inc = true;
            currentBright = max(currentBright, minBright);
        }
        ledcWrite(channel, currentBright);
    }

private:
    int channel;
    int stepBright;
    int stepDelayMs;
    int currentBright;
    int minBright, maxBright;
    bool inc;

    unsigned long lastProcessed;
};
