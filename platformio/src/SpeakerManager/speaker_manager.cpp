#include "speaker_manager.h"

SpeakerManager::SpeakerManager(gpio_num_t gpio_num) : gpio_num_{gpio_num} {

}

void SpeakerManager::Play(uint32_t frequency, std::chrono::milliseconds length) {
  // TODO
}
