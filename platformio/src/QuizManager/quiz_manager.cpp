#include "quiz_manager.h"

#include <Arduino.h>
#include <cstdlib>
#include <musical_notes.h>

int QuizManager::GetNrOfCorrectTones(uint32_t middle_frequency,
                               uint32_t high_frequency) {
  Serial.println((String)"Middle: " + middle_frequency + " High: " + high_frequency);
  // TODO
  if (middle_frequency < (high_frequency - 50)) {
    Serial.println("CORRECT!");
    return 2;
  } else {
    Serial.println("Keep trying.");
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
