#pragma once

#include <cstdint>

class QuizManager {
public:
  int GetNrOfCorrectTones(uint32_t middle_frequency, uint32_t high_frequency);
  bool IsEasterEggTriggered(uint32_t middle_frequency, uint32_t high_frequency);

  uint32_t GetRootFrequency();
  void GenerateNewRootTone();

 private:
  // TODO Tone root_tone_;
  // TODO map<Tone, frequency>
};
