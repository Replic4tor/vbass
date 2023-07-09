#include <Arduino.h>

#include "MusicManager/music_manager.h"

using music::NOTE;
using music::NOTE_LENGTH;

MusicManager music_manager{190};

void setup() {
}

void loop() {
  music_manager.Play(NOTE::E5, NOTE_LENGTH::EIGTH);
  music_manager.Play(NOTE::E5, NOTE_LENGTH::EIGTH);
  music_manager.Pause(NOTE_LENGTH::EIGTH);
  music_manager.Play(NOTE::E5, NOTE_LENGTH::EIGTH);
  music_manager.Pause(NOTE_LENGTH::EIGTH);
  music_manager.Play(NOTE::C5, NOTE_LENGTH::EIGTH);
  music_manager.Play(NOTE::E5, NOTE_LENGTH::QUARTER);
  music_manager.Play(NOTE::G5, NOTE_LENGTH::QUARTER);
  music_manager.Pause(NOTE_LENGTH::QUARTER);
  music_manager.Play(NOTE::C5, NOTE_LENGTH::QUARTER);
  music_manager.Pause(NOTE_LENGTH::QUARTER);
}
