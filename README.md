# beamer-screamer

A break beam triggered sound effect system.

## The Beamer

The beamer is a Arduino device that monitors an IR break beam sensor. When the beam is broken, the beamer sets a boolean state to 'true' and sends a message via UART. The state stays 'true' until the beam is cleared.

## The Screamer

The screamer is an Arduino device that monitors it's UART, listening for a trigger message. When the message is received, the device triggers an attached sound FX board to play a sound.