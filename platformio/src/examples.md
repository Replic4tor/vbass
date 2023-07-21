# Examples

## Digital Outputs (e.g. LED)

main:
```cpp
#include <Arduino.h>

const byte LED_GPIO = 32;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_GPIO, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_GPIO, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_GPIO, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```

## Super Mairo DAC

Depends on library `DacESP32` which must be installed with platformio.

main:
```cpp
#include <Arduino.h>
#include <DacESP32.h>

DacESP32 dac_(GPIO_NUM_25);

const int PLAY_NOTE_G4 = 392;   //G - Octave 4
const int PLAY_NOTE_C5 = 523;   //C - Octave 5
const int PLAY_NOTE_D5 = 587;   //D - Octave 5
const int PLAY_NOTE_E5 = 659;   //E - Octave 5
const int PLAY_NOTE_F5 = 698;   //F - Octave 5
const int PLAY_NOTE_G5 = 784;   //G - Octave 5
const int PLAY_NOTE_A5 = 880;   //A - Octave 5
const int PLAY_NOTE_H5 = 988;   //B - Octave 5
const int PLAY_NOTE_C6 = 1046;  //C - Octave 6

const int EIGTH_NOTE_LENGTH = 200;

void play_note(DacESP32& dac_, int freq, int length_ms) {
  dac_.enable();
  dac_.outputCW(freq);
  delay(length_ms);
  dac_.disable();
  delay(10);
}

void setup() {
  dac_.disable();
  delay(1000);
}

void loop() {
  play_note(dac_, PLAY_NOTE_E5, EIGTH_NOTE_LENGTH);
  play_note(dac_, PLAY_NOTE_E5, EIGTH_NOTE_LENGTH);
  delay(EIGTH_NOTE_LENGTH);
  play_note(dac_, PLAY_NOTE_E5, EIGTH_NOTE_LENGTH);
  delay(EIGTH_NOTE_LENGTH);
  play_note(dac_, PLAY_NOTE_C5, EIGTH_NOTE_LENGTH);
  play_note(dac_, PLAY_NOTE_E5, EIGTH_NOTE_LENGTH * 2);
  play_note(dac_, PLAY_NOTE_G5, EIGTH_NOTE_LENGTH * 2);
  delay(EIGTH_NOTE_LENGTH * 2);
  play_note(dac_, PLAY_NOTE_C5, EIGTH_NOTE_LENGTH * 2);
  delay(EIGTH_NOTE_LENGTH * 2);
}
```

## Analog Inputs

main
```cpp
#include <Arduino.h>

const int AIN_PIN = 34;
int analog_value = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  analog_value = analogRead(AIN_PIN);
  Serial.println(analog_value);
}

```
