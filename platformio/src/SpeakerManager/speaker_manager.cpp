#include "speaker_manager.h"

SpeakerManager::SpeakerManager(gpio_num_t gpio_num) : gpio_num_{gpio_num}, dac_{gpio_num_} {
  dac_.disable();
}

void SpeakerManager::Play(uint32_t frequency, std::chrono::milliseconds length) {
  dac_.enable();
  dac_.outputCW(frequency);
  delay(length.count());
  dac_.disable();
  delay(NOTE_CUTOFF_.count());
}
