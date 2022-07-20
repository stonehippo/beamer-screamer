# beamer-screamer

A break beam triggered sound effect system.

This code should work without modifcation on any ATMEGA328-based Arduino board, like the Uno, Nano, or Arduino Pro Mini. It might need some modification for other Arduino-compatible boards. I developed and tested this code on a pair of Duemilanove boards.

## Components

- 2 x [Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us) or similar Arduino-compabtible boards, like this [Adafruit Feather 328P](https://www.adafruit.com/product/3458)
- [Adafruit IR Break Beam Sensor](https://www.adafruit.com/product/2168)
- [Adafruit Audio FX Sound Board](https://www.adafruit.com/product/2220) 

## The Beamer

The beamer is an Arduino device that monitors an [IR break beam sensor](https://www.adafruit.com/product/2168). When the beam is broken, the beamer sets a boolean state to 'true' and sends a message via UART. The state stays 'true' until the beam is cleared.

## The Screamer

The screamer is an Arduino device that monitors its UART, listening for a trigger message. When the message is received, the device triggers an attached [audio FX board](https://www.adafruit.com/product/2220) to play a sound.