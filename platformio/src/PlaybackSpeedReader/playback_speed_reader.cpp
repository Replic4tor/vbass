#include "playback_speed_reader.h"

PlaybackSpeedReader::PlaybackSpeedReader(gpio_num_t gpio_num) : gpio_num_{gpio_num}{}

std::chrono::milliseconds PlaybackSpeedReader::GetNoteLength() {
  // TODO
  return std::chrono::milliseconds(1000);
}
