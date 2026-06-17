# ESP32 OLED Calculator

This project is a simple calculator built using:
- ESP32
- 0.96" OLED Display (SSD1306)
- 4x4 Matrix Keypad

## Features
- Basic operations (+, -, *, /)
- Real-time input display
- Expression display
- Error handling (division by zero)

## Connections

### OLED (I2C)
- VCC → 3.3V
- GND → GND
- SDA → GPIO 21
- SCL → GPIO 22

### Keypad
- Rows → 13, 12, 14, 27
- Columns → 26, 25, 33, 32

## Libraries Used
- Adafruit SSD1306
- Adafruit GFX
- Keypad

## Author
ALBERT ALEX
