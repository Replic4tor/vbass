#include "music_manager.h"

MusicManager::MusicManager() {
  dac.disable();
}

MusicManager::MusicManager(int bpm) : BPMS_{(static_cast<double>(bpm)/60)/1000} {
  dac.disable();
}

void MusicManager::Play(NOTE note, NOTE_LENGTH length) {
  dac.enable();
  dac.outputCW(note);
  delay(NoteLengthToMs(length).count());
  dac.disable();
  delay(NOTE_CUTOFF_.count());
}

void MusicManager::Pause(NOTE_LENGTH length) {
  delay(NoteLengthToMs(length).count());
}

std::chrono::milliseconds MusicManager::NoteLengthToMs(NOTE_LENGTH length) {
  return std::chrono::milliseconds (static_cast<int>(1/ BPMS_ * 4/length));
}
