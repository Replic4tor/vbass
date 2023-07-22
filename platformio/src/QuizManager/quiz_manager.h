#pragma once

#include <cstdint>
#include <musical_notes.h>
#include <vector>

class QuizManager {
public:
 QuizManager();

  int GetNrOfCorrectTones(uint32_t middle_frequency, uint32_t high_frequency);
  bool IsEasterEggTriggered(uint32_t middle_frequency, uint32_t high_frequency);

  uint32_t GetRootFrequency();
  void GenerateNewRootTone();

 private:
  music::NOTE root_tone_;
  double FREQUENCY_TOLERANCE_ = 30;

  bool IsMiddleNoteCorrect(uint32_t middle_frequency);
  bool IsHighNoteCorrect(uint32_t high_frequency);
};
