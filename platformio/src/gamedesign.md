# Game Design

## Summary

### Hardware

Analog-In:
* 4x Poti

Analog-Out:
* 1x Speaker

Digital-In:
* 1x Rotary Switch/Button
* 1x Button

Digital-Out:
* 1x (RGB) LED

### Gameplay

* Start/stop the game: Press rotary switch
* Frequency middle tone: Poti #1
* Frequency high tone: Poti #2
* Playback speed: Poti #3
* Volume: Poti #4
* Octave: Turn rotary switch
* Skip to next quiz: Button
* Progress: LED | red (wrong), yellow (one tone correct), green (solved)

### Easter Eggs / Goodies

* Victory melody on solved quiz
* R2D2 sad beep on skip/reset
* "Swing Life Away" if all potis are turned to max

## Software Design

Brainstorming (what do we need?):

* Poti interfacing
  * Reading analog values
  * Converting analog values to frequency
  * => Own class for that. Returns frequency based on read Poti value.
* Speaker interfacing
  * DAC
  * "Play" frequency on speaker
  * => Own class for that
* Button interfacing
  * ISR
  * Debouncing
* Rotary button interfacing
  * Detect turn signals
  * Detect button press
* LED interfacing
  * Set color of LED
  * => Own class for that
* Interrupt handlers for button presses (game start/stop & skip)
* Easter egg melodies

Example game loop, based on state machine:
* Setup
  * Choose new base tone
  * Reset variables etc.
* EvaluateQuiz
  * Read analog input frequencies
  * Determine if frequencies have been set correctly (or half correct)
  * Determine if easter egg has been activated
* PlaybackBase
  * Read analog input playback speed and octave
  * Play base tone + break based on speed
* PlaybackMiddle
  * Read analog input playback speed and octave
  * Play middle tone + break based on speed
* PlaybackHigh
  * Read analog input playback speed and octave
  * Play high tone + break based on speed
* Victory
  * Turn LED green
  * Play correct sequence again
  * Play victory melody
  * Return to "Setup"
* Skip
  * Turn LED red (blinking?)
  * Play sad melody
* EasterEgg
  * Play easter egg melody
