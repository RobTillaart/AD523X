
[![Arduino CI](https://github.com/RobTillaart/AD523X/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AD523X/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AD523X/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AD523X/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AD523X/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/AD523X.svg)](https://github.com/RobTillaart/AD523X/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD523X/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD523X.svg?maxAge=3600)](https://github.com/RobTillaart/AD523X/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/AD523X.svg)](https://registry.platformio.org/libraries/robtillaart/AD523X)


# AD523X

Arduino library for SPI AD5231 and AD5235 digital potentiometers

## Description

**Experimental**

The library is experimental as the functionality is not tested yet.

The **AD5231** is a single channel 1024 step, SPI based potentiometer, 
the **AD5235** is a dual version thereof.

The interface is straightforward, one can set a value per channels between 0..1023.


#### Related

- https://github.com/RobTillaart/AD520X
- https://github.com/RobTillaart/AD523X
- https://github.com/RobTillaart/AD524X
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5144A
- https://github.com/RobTillaart/AD5245
- https://github.com/RobTillaart/AD5263
- https://github.com/RobTillaart/X9C10X


## Interface

```cpp
#include "AD523X.h"
```

### Constructors

- **AD5231(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD5231(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD5231(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)** constructor SW SPI


- **AD5235(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClassRP2040 \* mySPI = &SPI)** constructor HW SPI (RP2040 specific)
- **AD5235(uint8_t select, uint8_t reset, uint8_t shutdown, SPIClass \* mySPI = &SPI)** constructor HW SPI
- **AD5235(uint8_t select, uint8_t reset, uint8_t shutdown, uint8_t dataOut, uint8_t clock)** constructor SW SPI

Note: 
- hardware SPI is 10+ times faster on an UNO than software SPI.
- software SPI on ESP32 is about equally fast than hardware SPI.


### Base

- **void begin(uint8_t value = 512)** value is the initial value of all potentiometer.
- **void reset(uint8_t value = 512)** resets the device and sets all potentiometers to value, default 512.


### Value

- **bool setValue(uint8_t pm = 0, uint8_t value = 512)** set a potentiometer to a value. 
Default value is middle value.  
Returns true if successful, false if not.
- **bool setValue(uint8_t pmA, uint8_t pmB, uint8_t value)** set two potentiometers to same value.
Note, no default value!
Returns true if successful, false if not.
- **void setAll(uint8_t value = 512)** set all potentiometers to the same value e.g. 0 or max or mid value.
Can typically be used for **mute**.
- **uint8_t getValue(uint8_t pm = 0)** returns the last set value of a specific potentiometer.


The library has defined **#define AD520X_MIDDLE_VALUE  512**


### Percentage

- **bool setPercentage(uint8_t pm = 0, float percentage = 50)** similar to setValue, percentage from 0..100%, default potmeter 0 and 50%. 
Returns true when successful, false if not.
- **bool setPercentage(uint8_t pmA, uint8_t pmB, float percentage)** similar to setValue, percentage from 0..100%.
Note, no default value.
Returns true when successful, false if not.
- **float getPercentage(uint8_t pm = 0)** return the value of potentiometer pm as percentage.


### Hardware SPI

To be used only if one needs a specific speed for hardware SPI.  
Has no effect on software SPI.

- **void setSPIspeed(uint32_t speed)** set SPI transfer rate.
- **uint32_t getSPIspeed()** returns SPI transfer rate.
- **bool usesHWSPI()** returns true / false depending on constructor.

### Misc

- **uint8_t pmCount()** returns the number of internal potentiometers.
- **void powerOn()** switches the module on.
- **void powerOff()** switches the module off.
- **bool isPowerOn()** returns true if on (default) or false if off.


### EEMEM


TODO
- **void storeEEMEM()** save current position as power on reset.

- investigate EEMEM support
  - WP and RDY signals. 25 ms.
  - page 14 

### AD5231 specific

TODO

- investigate O1 en O2 outputs


## Future


#### Must

- improve documentation
- get hardware to test
- TODO's in code and documentation.


#### Should

- implement read back from device 
  - SPI 
  - commands.
- magic numbers (e.g. commands 0..15)

#### Could

- command nr 3 and 9 store/read from EEMEM(address).
- optimize code
- add error code
- add parameter checking
- extend unit tests
- extent examples

#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

