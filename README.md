# AVR Embedded Systems
Register-level embedded C programs for the ATmega328P microcontroller, written without the Arduino framework. All GPIO, ADC, UART, I2C, and timer operations are implemented by directly manipulating hardware registers — no HAL, no abstraction layer.
# Hardware
- ATmega328P (AVR 8-bit microcontroller, 16 MHz)
- avr-gcc toolchain, avrdude for flashing
- Peripherals: RGB LEDs, push buttons, SSD1306 OLED display, TMP36 temperature sensor, HC-SR04 ultrasonic sensor, 4-digit 7-segment display
# Labs

Lab 6—RGB LED Button Control

Three push buttons independently toggle a red, green, and blue LED with 125ms blink timing. Pin modes, pull-up resistors, and LED states are all set via direct `DDRC`, `PORTC`, `PORTD`, and `PIND` register writes.

Key concepts:`DDRx`/`PORTx`/`PINx` register manipulation, active-low button logic, `_delay_ms`

Lab 7—Temperature Monitor with OLED and UART

Reads ambient temperature from a TMP36 sensor via the ADC, converts to Celsius and Fahrenheit, displays the reading on an SSD1306 OLED screen over I2C, and streams data over UART serial. A button toggles between unit display. An LED warning activates when temperature exceeds 80°F.

Key concepts:ADC sampling, voltage-to-temperature conversion, I2C master communication, UART TX, `dtostrf`, threshold logic

Libraries used:`my_adc_lib`, `my_uart_lib`, `SSD1306`, `i2c`—all interfacing hardware at the register level.

Lab 8—Ultrasonic Distance Meter with 7-Segment Display

Measures distance using an HC-SR04 ultrasonic sensor by timing the echo pulse with Timer1, then displays the result in centimeters on a 4-digit multiplexed 7-segment display. Out-of-range readings (outside 5–50 cm) display dashes.

Key concepts:Timer1 for pulse-width measurement, 7-segment digit multiplexing, GPIO trigger/echo timing, lookup table for segment patterns
# Building
```bash
make
avrdude -c usbtiny -p m328p -U flash:w:main.hex
```
Precompiled `main.hex` and `main.elf` are included.
# Concepts Covered
|Concept|Labs|
|---|---|
|Direct register I/O(`DDRx`, `PORTx`, `PINx`)|6,7,8|
|ADC sampling|7|
|I2C master driver|7|
|UART serial transmission|7|
|SSD1306 OLED display|7|
|Timer1 pulse-width measurement|8|
|7-segment multiplexing|8|
|HC-SR04 ultrasonic ranging|8|
