#pragma once
//
//    FILE: AD523X.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-11-21
// VERSION: 0.1.0
// PURPOSE: Arduino library for SPI AD5231 and AD5235 digital potentiometers.
//     URL: https://github.com/RobTillaart/AD523X


#include "Arduino.h"
#include "SPI.h"


#define AD523X_LIB_VERSION              (F("0.1.0"))

#ifndef AD523X_MIDDLE_VALUE
#define AD523X_MIDDLE_VALUE             512
#endif


#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif


class AD523X
{
public:
  //  HARDWARE SPI
  AD523X(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  //  SOFTWARE SPI
  AD523X(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);

  void     begin(uint16_t value = AD523X_MIDDLE_VALUE);
  void     reset(uint16_t value = AD523X_MIDDLE_VALUE);

  //  SINGLE CHANNEL
  bool     setValue(uint8_t pm = 0, uint16_t value = AD523X_MIDDLE_VALUE);
  uint16_t getValue(uint8_t pm = 0);
  bool     setPercentage(uint8_t pm = 0, float percentage = 50);
  float    getPercentage(uint8_t pm = 0);

  //  DUAL CHANNEL AD5235 only TODO move?
  bool     setAll(uint16_t value);
  bool     setPercentageAll(float percentage = 0);

  //  incr/decr interface here TODO
  

  //       SPI - speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();
  bool     usesHWSPI();

  //       MISC
  uint8_t  pmCount();


  //  TODO include in readme.md

  //       EEMEM
  void     NOP();  //  needed by some commands.
  
  void     loadWiperEEMEM(uint8_t pm = 0);
  //  store current wiper position.
  void     storeWiperEEMEM(uint8_t pm = 0);

  uint16_t     loadEEMEM(uint8_t address, uint16_t value);
  //  store address 0 from value iso wiper position (AD5231/5)
  //  store address 1 from value iso wiper position (AD5235)
  //  store address 1 from value to write O1, O2    (AD5231) P08
  void     storeEEMEM(uint8_t address, uint16_t value);


  void     reset();

  //  incr/decr interface
  //  void     decrement6DB(uint8_t pm = 0);
  //  void     decrementOne(uint8_t pm = 0);
  //  void     increment6DB(uint8_t pm = 0);
  //  void     incrementOne(uint8_t pm = 0);


protected:
  uint8_t  _dataIn;
  uint8_t  _dataOut;
  uint8_t  _clock;
  uint8_t  _select;
  uint8_t  _reset;
  bool     _hwSPI;
  uint32_t _SPIspeed = 16000000;

  uint16_t _value[2];
  uint8_t  _pmCount = 2;

  void     updateDevice(uint8_t pm, uint16_t value);
  void     swSPI_transfer(uint8_t value);

  __SPI_CLASS__ * _mySPI;
  SPISettings   _spi_settings;
};


/////////////////////////////////////////////////////////////////////////////
//
// DERIVED CLASSES
//
class AD5231 : public AD523X
{
public:
  AD5231(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  AD5231(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


class AD5235 : public AD523X
{
public:
  AD5235(uint8_t select, uint8_t reset, __SPI_CLASS__ * mySPI = &SPI);
  AD5235(uint8_t select, uint8_t reset, uint8_t dataIn, uint8_t dataOut, uint8_t clock);
};


//  -- END OF FILE --
