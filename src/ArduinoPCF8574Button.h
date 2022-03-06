//
// Created by KingS on 2022/3/5.
//

#ifndef __ARDUINO_PCF8574_BUTTON_H
#define __ARDUINO_PCF8574_BUTTON_H

#include <functional>
#include <ArduinoPCF8574.h>

#ifndef __ARDUINO_PCF8574_BUTTON_CLICK_MIN_MILLIS_
#define __ARDUINO_PCF8574_BUTTON_CLICK_MIN_MILLIS_  130     // 点击一次最小间隔（主要为了去抖动）, 小于这个间隔的将被忽略
#endif

#ifndef __ARDUINO_PCF8574_BUTTON_LONG_CLICK_MILLS_
#define  __ARDUINO_PCF8574_BUTTON_LONG_CLICK_MILLS_ 1500    // 长按时间间隔
#endif

class ArduinoPCF8574Button {
public:
    explicit ArduinoPCF8574Button(ArduinoPCF8574::JUMP jump);

public:
    void setup();

    void loop();

    ArduinoPCF8574Button setOnClickListener(unsigned short index, const std::function<void()> &listener);

    ArduinoPCF8574Button setOnLongClickListener(unsigned short index, const std::function<void()> &listener);


private:
    enum ButtonStateEnum {
        PRESSED, RELEASED
    };

private:
    ArduinoPCF8574::JUMP mJump;


private:
    /**
     * loop函数上次执行的时间
     * @since 1.0.0
     */
    volatile unsigned long mLoopLatestMillis = 0;

    /**
     * 按钮点击回调
     * @since 1.0.0
     */
    std::function<void()> mButtonOnClickListener[8] = {
            nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr
    };

    /**
     * 按钮长按回调
     * @since 1.0.0
     */
    std::function<void()> mButtonOnLongClickListener[8] = {
            nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr
    };

    /**
     * 当前按钮的状态，分别对应P0~P7
     * @since 1.0.0
     */
    ButtonStateEnum mButtonState[8] = {
            ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED,
            ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED, ButtonStateEnum::RELEASED
    };

    /**
     * 当前按钮被下的时间，分别对应P0~P7
     * @since 1.0.0
     */
    unsigned long mButtonPressedMillis[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    /**
     * 当前GPIO是否当作一个按钮
     * @since 1.0.0
     */
    bool mButtonGpio[8] = {false, false, false, false, false, false, false, false};

};


#endif //__ARDUINO_PCF8574_BUTTON_H
