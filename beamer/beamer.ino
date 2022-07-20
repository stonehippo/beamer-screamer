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

#define BEAM 9            // the pin attached to the switch (break beam)
bool state = false;       // basis for a simple state machine (a fancy toggle, in this case)

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BEAM, INPUT_PULLUP);
}

void loop() {
  if(is_beam_triggered()) {
    if (!state) {         // if the state is not already 'on'…
      send_trigger();
      state = true;       // …then set the state to 'on'
      digitalWrite(LED_BUILTIN, HIGH);
    }
  } else {
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
void send_trigger() {
  Serial.write(0x01);
}
