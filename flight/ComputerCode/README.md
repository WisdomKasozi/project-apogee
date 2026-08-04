# Project Apogee — Flight Computer Firmware

Arduino sketch that logs altitude, acceleration, and rotation to a MicroSD
card during flight. Written for Project Apogee, a scratch-built model rocket.

## Hardware
- Arduino Nano (ATmega328P)
- BMP388 barometric altimeter (I2C)
- MPU-6050 accelerometer + gyroscope (I2C)
- MicroSD module (SPI)

## Wiring

| Component | Pin | Nano |
|---|---|---|
| BMP388 / MPU-6050 | SDA | A4 |
| BMP388 / MPU-6050 | SCL | A5 |
| MicroSD | CS | D4 |
| MicroSD | MOSI | D11 |
| MicroSD | MISO | D12 |
| MicroSD | SCK | D13 |

Both sensors share the I2C bus. SD module runs on SPI.

## What it does
1. Tares barometric altitude to ground level at startup
2. Logs time, altitude, 3-axis acceleration, and 3-axis rotation
   to `data.csv` at ~21 Hz
3. Flushes to the card every 500 ms so data survives if power cuts

## Libraries
- Adafruit BMP3XX
- Adafruit MPU6050
- SD (built-in)
