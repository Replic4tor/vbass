#pragma once

#include <cstdint>
#include <musical_notes.h>

class QuizManager {
public:
  int GetNrOfCorrectTones(uint32_t middle_frequency, uint32_t high_frequency);
  bool IsEasterEggTriggered(uint32_t middle_frequency, uint32_t high_frequency);

  uint32_t GetRootFrequency();
  void GenerateNewRootTone();

 private:
  music::NOTE root_tone_ = music::C4;  // TODO randomize initial tone
  // TODO map<Tone, frequency>
};
