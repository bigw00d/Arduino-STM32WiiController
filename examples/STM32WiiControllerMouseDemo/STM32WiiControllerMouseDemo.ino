#include <USBComposite.h>
#include "STM32WiiController.h"

USBHID HID;
HIDKeyboard Keyboard(HID);
HIDMouse mouse(HID);

STM32WiiController wiicon;

//I2C1(use this):
//SDA  PB7 (23)
//SCL PB6 (22)
//
//I2C2:
//SDA PB11 (27)
//SCL PB10 (26)

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
