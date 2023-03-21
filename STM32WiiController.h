// Copyright (c) 2023 Daiki Yasuda

#ifndef __STM32_WIICONTROLLER_H__
#define __STM32_WIICONTROLLER_H__

#define CONTROLLER_ADDRESS 0x52
#define STABILIZE_COUNT 10

typedef struct {
        signed char analogLX;
        signed char analogLY;
        // uint8_t xStick;
        // uint8_t yStick;
        // uint8_t xAxis;
        // uint8_t yAxis;
        // uint8_t zAxis;
        // uint8_t cBtn;
        // uint8_t zBtn;
} NunchukState;

class STM32WiiController
{
public:
  enum
  {
//    BUTTON_LEFT       = 0x0800,
//    BUTTON_RIGHT      = 0x0400,
//    BUTTON_UP         = 0x0200,
//    BUTTON_DOWN       = 0x0100,
    BUTTON_A          = 0x1000,
    BUTTON_B          = 0x4000,
//    BUTTON_PLUS       = 0x1000,
    BUTTON_HOME       = 0x0008
//    BUTTON_MINUS      = 0x0010,
//    BUTTON_ONE        = 0x0002,
//    BUTTON_TWO        = 0x0001
  };

  STM32WiiController(void);

  void init(void);
  void scan(void);
  uint16_t getButtonState(void);
  NunchukState getNunchukState(void);

private:
  uint8_t initXposi;
  uint8_t initYposi;
  uint8_t initCnt;
  
  uint8_t values[8];
  
  uint8_t analogLX; // Left Side Anarog Stick X  - 6Bit
  uint8_t analogLY; // Left Side Anarog Stick Y  - 6Bit
  //uint8_t analogRX; // Right Side Anarog Stick X - 5Bit
  //uint8_t analogRY; // Right Side Anarog Stick Y - 5Bit
  //uint8_t analogLB; // Left Side Anarog Buttob   - 5Bit
  //uint8_t analogRB; // Right Side Anarog Button  - 5Bit
  uint16_t pushButton ;

  uint16_t _buttonState;

  NunchukState _nunchukState;

  void init_con(void);
  void send_zero(void);

};

#endif // __STM32_WIICONTROLLER_H__
