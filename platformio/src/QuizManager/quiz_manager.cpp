#include "quiz_manager.h"

#include <Arduino.h>
#include <cstdlib>
#include <musical_notes.h>

namespace {
const std::vector<music::NOTE> POSSIBLE_ROOT_NOTES {
  music::NOTE::C4, music::NOTE::C4S, music::NOTE::D4, music::NOTE::D4S, music::NOTE::E4, music::NOTE::F4,
      music::NOTE::F4S, music::NOTE::G4, music::NOTE::G4S, music::NOTE::A4, music::NOTE::A4S, music::NOTE::B4,
};
}// namespace

QuizManager::QuizManager() {
  GenerateNewRootTone();
}

int QuizManager::GetNrOfCorrectTones(uint32_t middle_frequency, uint32_t high_frequency) {
  Serial.println((String) "Root: " + root_tone_ + " Middle: " + middle_frequency + " High: " + high_frequency);
  auto correct_tones = 0;

  if (IsMiddleNoteCorrect(middle_frequency)) {
    Serial.println("Middle note is correct!");
    ++correct_tones;
  }

  if (IsHighNoteCorrect(high_frequency)) {
    Serial.println("High note is correct!");
    ++correct_tones;
  }

  return correct_tones;
}

bool QuizManager::IsEasterEggTriggered(uint32_t middle_frequency, uint32_t high_frequency) {
  return ((middle_frequency > 790) && (high_frequency > 790));
}

uint32_t QuizManager::GetRootFrequency() {
  return root_tone_;
}

void QuizManager::GenerateNewRootTone() {
  auto random_index = std::rand() % POSSIBLE_ROOT_NOTES.size();
  root_tone_ = POSSIBLE_ROOT_NOTES.at(random_index);
  Serial.println((String) "New root tone frequency: " + root_tone_);
}

bool QuizManager::IsMiddleNoteCorrect(uint32_t middle_frequency) {
  auto expected_frequency = root_tone_ * (5 / 4);
  return (abs((int) (expected_frequency - middle_frequency)) < FREQUENCY_TOLERANCE_);
}

bool QuizManager::IsHighNoteCorrect(uint32_t high_frequency) {
  auto expected_frequency = root_tone_ * (3 / 2);
  return (abs((int) (expected_frequency - high_frequency)) < FREQUENCY_TOLERANCE_);
}
