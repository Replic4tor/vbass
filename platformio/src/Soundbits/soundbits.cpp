#include "soundbits.h"

#include "musical_notes.h"

void PlaySkipSong(SpeakerManager& speaker_manager) {
  speaker_manager.Play(music::NOTE::E4, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::E4, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::D4, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::D4, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::C4, std::chrono::milliseconds(500));
  delay(250);
}

void PlayVictorySong(SpeakerManager& speaker_manager) {
  speaker_manager.Play(music::NOTE::G4, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::G4, std::chrono::milliseconds(250));
  delay(250);
  speaker_manager.Play(music::NOTE::G4, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::A4, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::B4, std::chrono::milliseconds(250));
  speaker_manager.Play(music::NOTE::C5, std::chrono::milliseconds(500));
  delay(250);
  speaker_manager.Play(music::NOTE::C5, std::chrono::milliseconds(125));
  speaker_manager.Play(music::NOTE::C5, std::chrono::milliseconds(125));
}
