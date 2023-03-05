#pragma once

#include <Arduino.h>

#define LOG_TAG "EFFTECT"

class EffectDigital {
public:
    EffectDigital(uint8_t pn, bool* seq, int cnt, int stDelayMs = 25) :
        pin(pn),
        stepDelayMs(stDelayMs),
        sequence(seq),
        count(cnt),
        index(0),
        lastProcessed(0) {
        pinMode(pin, OUTPUT);
    }

    void loop(unsigned long now) {
        if (now - lastProcessed > stepDelayMs) {
            lastProcessed = now;
            process();
        }
    }

    void process() {
        int light = sequence[index] ? HIGH : LOW;
        digitalWrite(pin, light);
        // ESP_LOGI(LOG_TAG, "%d is %d", pin, light);
        index = (index + 1) % count;
    }

private:
    int pin;
    int stepDelayMs;
    bool* sequence;
    int count;

    int index;

    unsigned long lastProcessed;
};
