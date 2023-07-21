#include "quiz_manager.h"

#include <cstdlib>
#include <musical_notes.h>

int QuizManager::GetNrOfCorrectTones(uint32_t middle_frequency,
                               uint32_t high_frequency) {
  // TODO
  if (middle_frequency < high_frequency) {
    return 2;
  } else {
    return 0;
  }
}

bool QuizManager::IsEasterEggTriggered(uint32_t middle_frequency,
                                       uint32_t high_frequency) {
  // TODO
  return false;
}

uint32_t QuizManager::GetRootFrequency() {
  // TODO
  return music::NOTE::C4;
}

void QuizManager::GenerateNewRootTone() {
  // TODO
  if (root_tone_ == music::C4) {
    root_tone_ = music::F4;
  } else {
    root_tone_ = music::C4;
  }
}
