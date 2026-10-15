
#include <Arduino.h>

// ---------------- Піни ----------------

constexpr uint8_t BLUE_LED = 15;
constexpr uint8_t RED_LED = 16;

constexpr uint8_t EXTERNAL_BUTTON = 21;
constexpr uint8_t BOOT_BUTTON = 0;

// ---------------- Затримки ----------------

constexpr uint16_t FAST_SPEED = 200;
constexpr uint16_t SLOW_SPEED = 1000;

// ---------------- Режим роботи ----------------

uint8_t mode = 1; // 1 - швидкий, 2 - повільний

void setup() {
    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    pinMode(EXTERNAL_BUTTON, INPUT_PULLUP);
    pinMode(BOOT_BUTTON, INPUT_PULLUP);

    Serial.begin(115200);
}

// Керування світлодіодом
void led(uint8_t pin, bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
}

// Перевірка кнопок
void checkButtons() {
    if (digitalRead(EXTERNAL_BUTTON) == LOW) {
        if (mode != 1) {
            mode = 1;
            Serial.println("Mode 1: FAST");
        }
    }

    if (digitalRead(BOOT_BUTTON) == LOW) {
        if (mode != 2) {
            mode = 2;
            Serial.println("Mode 2: SLOW");
        }
    }
}

void waitWithButtons(uint16_t timeMs) {
    for (uint16_t i = 0; i < timeMs; i += 10) {
        checkButtons();
        delay(10);
    }
}

// Режим 1: обидва світлодіоди одночасно
void fastBlink() {
    led(BLUE_LED, true);
    led(RED_LED, true);
    waitWithButtons(FAST_SPEED);

    led(BLUE_LED, false);
    led(RED_LED, false);
    waitWithButtons(FAST_SPEED);
}

// Режим 2: світлодіоди по черзі
void slowBlink() {
    led(BLUE_LED, true);
    led(RED_LED, false);
    waitWithButtons(SLOW_SPEED);

    led(BLUE_LED, false);
    led(RED_LED, true);
    waitWithButtons(SLOW_SPEED);
}

// Головний цикл
void loop() {
    checkButtons();

    if (mode == 1) {
        fastBlink();
    } else {
        slowBlink();
    }
}
