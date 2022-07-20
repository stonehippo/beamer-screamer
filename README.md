# beamer-screamer

A break beam triggered sound effect system.

This code should work without modifcation on any ATMEGA328-based Arduino board, like the Uno, Nano, or Arduino Pro Mini. It might need some modification for other Arduino-compatible boards. I developed and tested this code on a pair of Duemilanove boards.

## The Beamer

The beamer is a Arduino device that monitors an IR break beam sensor. When the beam is broken, the beamer sets a boolean state to 'true' and sends a message via UART. The state stays 'true' until the beam is cleared.

## The Screamer

The screamer is an Arduino device that monitors it's UART, listening for a trigger message. When the message is received, the device triggers an attached sound FX board to play a sound.