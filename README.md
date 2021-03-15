# samhain

## Target Chips

  - SAMD11 (planned)
  - SAMC2x (planned)
  - SAMD21 (in-progress)
  - SAMD51 (planned)

## Plan

  - Implement baseline on SAMD21:
    - clock
    - power manager
    - delay
    - GPIO
    - delay
    - timer
    - SERCOM
    - Drivers
      - UART
      - SPI master
      - I2C master
      - I2C slave
      - PWM
      - Timer
  - Porting

## TODO

  - SERCOM helper functions for UART
  - UART driver - look at nRF UART driver
  - UART driver - enable, disable
  - UART driver - enable, disable transmitter
  - UART driver - error handler
  - UART driver - ability to set new callback on transmit/receive calls
  - UART driver - do we need blocking mode in same driver?
