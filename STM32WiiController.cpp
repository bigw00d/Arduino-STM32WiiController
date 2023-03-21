// Copyright (c) 2023 Daiki Yasuda

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include <Wire.h>

#include "STM32WiiController.h"

STM32WiiController::STM32WiiController(void)
{
  initCnt = 0;
  initXposi = 0;
  initYposi = 0;
  
  analogLX = 0;
  analogLY = 0;
  pushButton = 0;
}

void STM32WiiController::init(void)
{
  Wire.begin();
  delay(2000);
  init_con();
}

void STM32WiiController::init_con() 
{
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);  
}

void STM32WiiController::send_zero() 
{
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
}

void STM32WiiController::scan(void)
{
  int count = 0;
  int readLen = Wire.requestFrom(CONTROLLER_ADDRESS, 8);
  
  while(Wire.available()) {
    values[count] = Wire.read();
    delay(2);
    count++;
    if (count >= 8) {
      break;
    }
  }
  send_zero();

  if(count > 0){

    if (readLen == 8 && count == 8) {
      if (initCnt < STABILIZE_COUNT)
      {
        initCnt++;
      }
      else {
        if (initXposi == 0) {
          initXposi = analogLX;
          initYposi  = analogLY;
        }
        analogLX = values[0] & 0b00111111 ;
        analogLX = values[0] & 0b00111111 ;
        analogLY = values[1] & 0b00111111 ;
        ((uint8_t *)&pushButton)[0] = ~values[4] ;
        ((uint8_t *)&pushButton)[1] = ~values[5] ;
      }
    }
  }
  _nunchukState.analogLX = ((signed char)(analogLX - initXposi)/2)*2;
  _nunchukState.analogLY = ((signed char)(initYposi - analogLY)/2)*2;
  _buttonState = pushButton;
}

uint16_t STM32WiiController::getButtonState(void)
{
  return _buttonState;
}

NunchukState STM32WiiController::getNunchukState(void)
{
  return _nunchukState;
}
