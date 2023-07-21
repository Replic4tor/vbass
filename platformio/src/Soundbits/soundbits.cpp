#include "soundbits.h"

#include "musical_notes.h"

void PlaySkipSong(SpeakerManager& speaker_manager) {
  for (int i = music::NOTE::C5; i > 10; i -= 10) {
    Serial.println((String) "Frequency on Skip: " + i);
    speaker_manager.Play(i, std::chrono::milliseconds(250));
  }
}

void PlayVictorySong(SpeakerManager& speaker_manager) {
  speaker_manager.Play(music::NOTE::F5, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::F5, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::E5, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::E5, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::F5, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::F5, std::chrono::milliseconds(250));
}
