/*
 * This code is for the beamer half of a Halloween scare device. It monitors an attached switch
 * (specifically, an IR break beam sensor), and sends a message via serial when the swithc is
 * trigged.
 * 
 * In this implementation, there's a 1:1 between the input signal and the
 * output sound. However, a simple command structure could be created to
 * trigger different sounds based on the content of the signal.
 * 
 */
#include <SoftwareSerial.h>

#define BEAM 9            // the pin attached to the switch (break beam)
#define SOFT_SERIAL_RX 10
#define SOFT_SERIAL_TX 11

bool state = false;       // basis for a simple state machine (a fancy toggle, in this case)

SoftwareSerial screamer(SOFT_SERIAL_RX, SOFT_SERIAL_TX); 

void setup() {
  Serial.begin(9600);

  pinMode(SOFT_SERIAL_RX, INPUT);
  pinMode(SOFT_SERIAL_TX, OUTPUT);
  screamer.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BEAM, INPUT_PULLUP);
}

void loop() {
  if(is_beam_triggered()) {
    if (!state) {         // if the state is not already 'on'…
      Serial.println("Beam has been broken");
      send_trigger(0x01);
      state = true;       // …then set the state to 'on'
      digitalWrite(LED_BUILTIN, HIGH);
    }
  } else {
    if (state) {          // We're leaving the broken state
      Serial.println("Beam has been restored");
    }
    state = false;        // it's no big deal to set the state in the loop if it is 'off'
    digitalWrite(LED_BUILTIN, LOW);
  }
}

//---------utility functions----------
// CODE STYLE COMMENT: we COULD just shove everything in loop(), but using
// functions is cleaner and easier to modify in the future

bool is_beam_triggered() {
  if (digitalRead(BEAM) == LOW) {
    return true;
  } else {
    Serial.println("Sending message to screamer");
    return false;
  }
}

/* 
 * We'll send a short code to the screamer device
 * Note: Using a HEX number here so you can define multiple messages with a simple
 * protocol, like this:
 * 
 * 0x01 sound 1
 * 0x02 sound 2
 * 0x03 sound 3,
 * etc
 * 
 * This could also just be an integer, but HEX just looks nicer ;-)
 */
void send_trigger(byte message) {
  Serial.println("Sending message to screamer");
  screamer.write(message);
}
