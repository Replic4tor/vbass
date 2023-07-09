#pragma once

#include <DacESP32.h>
#include <Arduino.h>
#include <chrono>

#include "musical_notes.h"

using music::NOTE;
using music::NOTE_LENGTH;

class MusicManager {
public:
  MusicManager();
  explicit MusicManager(int bpm);

  void Play(NOTE note, NOTE_LENGTH length);
  void Pause(NOTE_LENGTH length);


private:
  const double BPMS_ = (120.0/60)/1000;  // amount of quarter notes ("beats") each millisecond
  const std::chrono::milliseconds NOTE_CUTOFF_{10};
  std::chrono::milliseconds NoteLengthToMs(NOTE_LENGTH length);

  DacESP32 dac{GPIO_NUM_25};
};
