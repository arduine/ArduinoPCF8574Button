//
// Created by KingS on 2022/3/5.
//

#include "ArduinoPCF8574Button.h"

ArduinoPCF8574Button::ArduinoPCF8574Button(ArduinoPCF8574::JUMP jump) : mJump(jump) {
}

void ArduinoPCF8574Button::setup() {
    ArduinoPCF8574::setup();

    auto gpio = ArduinoPCF8574::read(mJump);
    if (mButtonGpio[0]) gpio.P0 = true;
    if (mButtonGpio[1]) gpio.P1 = true;
    if (mButtonGpio[2]) gpio.P2 = true;
    if (mButtonGpio[3]) gpio.P3 = true;
    if (mButtonGpio[4]) gpio.P4 = true;
    if (mButtonGpio[5]) gpio.P5 = true;
    if (mButtonGpio[6]) gpio.P6 = true;
    if (mButtonGpio[7]) gpio.P7 = true;
    ArduinoPCF8574::write(mJump, gpio);
}

void ArduinoPCF8574Button::loop() {
    const unsigned long _millis = millis();
    if (_millis - mLoopLatestMillis <= __ARDUINO_PCF8574_BUTTON_CLICK_MIN_MILLIS_)
        return;
    mLoopLatestMillis = _millis;

    auto gpio = ArduinoPCF8574::read(mJump);
    if (mButtonGpio[0]) gpio.P0 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P0) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P0);
    if (mButtonGpio[1]) gpio.P1 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P1) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P1);
    if (mButtonGpio[2]) gpio.P2 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P2) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P2);
    if (mButtonGpio[3]) gpio.P3 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P3) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P3);
    if (mButtonGpio[4]) gpio.P4 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P4) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P4);
    if (mButtonGpio[5]) gpio.P5 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P5) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P5);
    if (mButtonGpio[6]) gpio.P6 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P6) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P6);
    if (mButtonGpio[7]) gpio.P7 ? onButtonReleased(_millis, ArduinoPCF8574::PIN::P7) : onButtonPressed(_millis, ArduinoPCF8574::PIN::P7);
}

ArduinoPCF8574Button ArduinoPCF8574Button::setOnClickListener(const ArduinoPCF8574::PIN &pin, const ArduinoButtonListener &listener) {
    if (pin < 0 || pin > 7)
        return *this;
    mButtonGpio[pin]            = true;
    mButtonOnClickListener[pin] = listener;
    return *this;
}

ArduinoPCF8574Button ArduinoPCF8574Button::setOnLongClickListener(const ArduinoPCF8574::PIN &pin, const ArduinoButtonListener &listener) {
    if (pin < 0 || pin > 7)
        return *this;
    mButtonGpio[pin]                = true;
    mButtonOnLongClickListener[pin] = listener;
    return *this;
}

void ArduinoPCF8574Button::onButtonReleased(const unsigned long _millis, const ArduinoPCF8574::PIN &pin) {
    if (mButtonState[pin] == ButtonStateEnum::RELEASED)
        return;
    mButtonState[pin] = ButtonStateEnum::RELEASED;
    if (_millis - mButtonPressedMillis[pin] >= __ARDUINO_PCF8574_BUTTON_LONG_CLICK_MILLS_) {
        if (mButtonOnLongClickListener[pin] != nullptr)
            mButtonOnLongClickListener[pin]();
    } else if (mButtonOnClickListener[pin] != nullptr) {
        mButtonOnClickListener[pin]();
    }
}

void ArduinoPCF8574Button::onButtonPressed(const unsigned long _millis, const ArduinoPCF8574::PIN &pin) {
    if (mButtonState[pin] == ButtonStateEnum::PRESSED)
        return;
    mButtonState[pin]         = ButtonStateEnum::PRESSED;
    mButtonPressedMillis[pin] = _millis;
}

