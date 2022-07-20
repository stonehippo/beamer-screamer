/*
 * This is the screamer half of a Halloween scare device. It listens
 * for a signal on it's serial UART, and once received, it triggers an
 * attached sound FX board to play a sound.
 * 
 * In this implementation, there's a 1:1 between the input signal and the
 * output sound. However, a simple command structure could be created to
 * trigger different sounds based on the content of the signal.
 */

#define SOUND_TRIGGER 9 // the pin attached to a trigger on the sound FX board
 
void setup() {
  Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

  // set up the pin for the sound trigger, including pulling it high
  pinMode(SOUND_TRIGGER, OUTPUT);
  digitalWrite(SOUND_TRIGGER, HIGH);
}

void loop() {
  // listen for the signal on serial, and act if we have a message
  if(Serial.available() > 0) {
    byte message = Serial.read();
    if(parse_trigger(message)) {
      digitalWrite(LED_BUILTIN, HIGH);
      trigger_sound();
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

//---------utility functions----------
// CODE STYLE COMMENT: we COULD just shove everything in loop(), but using
// functions is cleaner and easier to modify in the future

/* 
 * We'll receive a short code from the beamer device
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
bool parse_trigger(byte message) {
  if (message == 0x01) {
    return true;
  }
  return false;
}

// fire off the sound
void trigger_sound() {
  digitalWrite(SOUND_TRIGGER, LOW);
  delay(100);
  digitalWrite(SOUND_TRIGGER, HIGH);
}
