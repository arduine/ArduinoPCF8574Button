# Arduino PCF8574 Button

## 说明

一个Arduino的`PCF8574`的I/O拓展板库的输入控件，我是用按钮测试的， 这个项目依赖[ArduinoPCF8574](https://github.com/arduine/ArduinoPCF8574.git)。

> #### ⚠️ 注意：
>
> 如果想使用PCF8574作为输入，那么此接口必须为高电平，也就是将IO设置为1，否者无法读取状态。
> 

## 导入

#### PlatformIO

```ini
; Library options
lib_deps =
    https://github.com/arduine/ArduinoPCF8574Button.git#main
```

#### ArduinoIDE

```c++
// TODO
```

## 使用

1. 增加头文件导入：

```c++
#include <ArduinoPCF8574Button.h>
```

2. 初始化

```c++
// 跳线32作为输入
ArduinoPCF8574Button sArduinoPCF8574Button32(ArduinoPCF8574::J32);

void setup() {
    // 设置P0接口点击事件，参数支持P0~P7
    sArduinoPCF8574Button32.setOnClickListener(0,[] { Serial.printf("[*] pcf8574 gpio P0 click\n"); });
    
    // 设置P0的长按动作，参数支持P0~P7
    sArduinoPCF8574Button32.setOnLongClickListener(0,[] { Serial.printf("[*] pcf8574 gpio long click\n"); });
    
    // ⚠️ 此处一定要在设置回调后调用，否则你会发现点击无效
    //    这里会根据上面设置的回调接口自动设置为高电平
    sArduinoPCF8574Button32.setup();
}

void loop() {
    sArduinoPCF8574Button32.loop();
}
```

## 进阶

1. 重新定义宏`__ARDUINO_PCF8574_BUTTON_CLICK_MIN_MILLIS_`可调整去抖动的时间。默认：130ms
2. 重新定义宏`__ARDUINO_PCF8574_BUTTON_LONG_CLICK_MILLS_`可调长按触发的时间。默认：1.5s

## LICENSE

```text
                                 Apache License
                           Version 2.0, January 2004
                        http://www.apache.org/licenses/

   TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
```
