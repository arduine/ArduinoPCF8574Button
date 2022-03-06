//
// Created by KingS on 2022/3/5.
//

#include "ArduinoPCF8574Button.h"

ArduinoPCF8574Button::ArduinoPCF8574Button(ArduinoPCF8574::JUMP jump) : mJump(jump) {
}

void ArduinoPCF8574Button::setup() {
    ArduinoPCF8574::setup();

    auto gpio = ArduinoPCF8574::GPIO();

    gpio.P0 = mButtonGpio[0];
    gpio.P1 = mButtonGpio[1];
    gpio.P2 = mButtonGpio[2];
    gpio.P3 = mButtonGpio[3];
    gpio.P4 = mButtonGpio[4];
    gpio.P5 = mButtonGpio[5];
    gpio.P6 = mButtonGpio[6];
    gpio.P7 = mButtonGpio[7];
    ArduinoPCF8574::write(mJump, gpio);
}

void ArduinoPCF8574Button::loop() {
    const unsigned long _millis = millis();
    if (_millis - mLoopLatestMillis <= __ARDUINO_PCF8574_BUTTON_CLICK_MIN_MILLIS_)
        return;
    mLoopLatestMillis = _millis;

    std::function<void()>    empty            = [] {};

    std::function<void(int)> onButtonPressed  = [&](int index) {
        if (mButtonState[index] == ButtonStateEnum::PRESSED)
            return;
        mButtonState[index]         = ButtonStateEnum::PRESSED;
        mButtonPressedMillis[index] = _millis;
    };

    std::function<void(int)> onButtonReleased = [&](int index) {
        if (mButtonState[index] == ButtonStateEnum::RELEASED)
            return;
        mButtonState[index] = ButtonStateEnum::RELEASED;
        if (_millis - mButtonPressedMillis[index] >= __ARDUINO_PCF8574_BUTTON_LONG_CLICK_MILLS_) {
            mButtonOnLongClickListener[index] != nullptr ? mButtonOnLongClickListener[index]() :
            mButtonOnClickListener[index] != nullptr ? mButtonOnClickListener[index]() : empty();
        } else if (mButtonOnClickListener[index] != nullptr) {
            mButtonOnClickListener[index]();
        }
    };

    auto gpio = ArduinoPCF8574::read(mJump);
    if (mButtonGpio[0]) gpio.P0 ? onButtonReleased(0) : onButtonPressed(0);
    if (mButtonGpio[1]) gpio.P1 ? onButtonReleased(1) : onButtonPressed(1);
    if (mButtonGpio[2]) gpio.P2 ? onButtonReleased(2) : onButtonPressed(2);
    if (mButtonGpio[3]) gpio.P3 ? onButtonReleased(3) : onButtonPressed(3);
    if (mButtonGpio[4]) gpio.P4 ? onButtonReleased(4) : onButtonPressed(4);
    if (mButtonGpio[5]) gpio.P5 ? onButtonReleased(5) : onButtonPressed(5);
    if (mButtonGpio[6]) gpio.P6 ? onButtonReleased(6) : onButtonPressed(6);
    if (mButtonGpio[7]) gpio.P7 ? onButtonReleased(7) : onButtonPressed(7);

}

ArduinoPCF8574Button ArduinoPCF8574Button::setOnClickListener(unsigned short index, const std::function<void()> &listener) {
    if (index < 0 || index > 7)
        return *this;
    mButtonGpio[index]            = true;
    mButtonOnClickListener[index] = listener;
    return *this;
}

ArduinoPCF8574Button ArduinoPCF8574Button::setOnLongClickListener(unsigned short index, const std::function<void()> &listener) {
    if (index < 0 || index > 7)
        return *this;
    mButtonGpio[index]                = true;
    mButtonOnLongClickListener[index] = listener;
    return *this;
}

