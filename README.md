# Arduino-STM32WiiController
Arduino library that connects with a Wii controllers 

## Requirement

- STM32F103C8T6 minimum Development Board(BluePill)
- Arduino IDE (Version: 1.8.5)

## Installation
1. Download the zip file.
2. Move the zip file to your libraries directory.
3. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library.
4. Select the zip file.

## Supported Devices

- Wii Classic Pro Controller : RVL-005

##  Pin connections

|Controller  |BluePill  |Note  |
|---|---|---|
|GND  | GND ||
|5V  | 5V ||
|SDA  | PB_7 ||
|SCL  | PB_6 ||

## Examples

### Use wii classic controller as a mouse

```ESP32WiimoteDemo.ino.cpp
#include <USBComposite.h>
#include "STM32WiiController.h"

USBHID HID;
HIDKeyboard Keyboard(HID);
HIDMouse mouse(HID);

STM32WiiController wiicon;

uint16_t oldPushButton ;

void setup() {
  oldPushButton = 0;

  HID.begin(HID_KEYBOARD_MOUSE);
  Keyboard.begin();
  wiicon.init();
}

void loop() {
  wiicon.scan();
  delay(10);

  NunchukState nunchuk = wiicon.getNunchukState();

  mouse.move(nunchuk.analogLX, nunchuk.analogLY);

  uint16_t pushButton = wiicon.getButtonState();

  if (pushButton != oldPushButton)
  {
      if (pushButton & 0x4000) {
        mouse.press(MOUSE_LEFT);
      }
      else {
        mouse.release(MOUSE_LEFT);
      }

      if (pushButton & 0x1000) {
        mouse.press(MOUSE_RIGHT);
      }
      else {
        mouse.release(MOUSE_RIGHT);
      }

      if (pushButton & 0x0008) { //HOME
        Keyboard.print("HOME");
      }

      oldPushButton = pushButton;
  }

}

```

#### Button Definition
'pushButton' is expressed as OR of bits:

```
  BUTTON_A          = 0x1000
  BUTTON_B          = 0x4000
  BUTTON_HOME       = 0x0080
```

## Licence

   see [LICENSE.md](./LICENSE.md) 
   