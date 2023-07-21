#include "playback_speed_reader.h"

PlaybackSpeedReader::PlaybackSpeedReader(gpio_num_t gpio_num) : gpio_num_{gpio_num} {}

std::chrono::milliseconds PlaybackSpeedReader::GetNoteLength() {
  // TODO Use actual code once third and fourth poti are available
  //  auto raw_value = (double) analogRead(gpio_num_);
  //  auto speed_ms = (raw_value/4096) * 900 + 100;
  //  Serial.println((String)"[Speed] Raw value: " + raw_value);
  //  Serial.println((String)"Playback speed (ms): " + speed_ms);
  //
  //  return std::chrono::milliseconds((int)speed_ms);

  return std::chrono::milliseconds(1000);
}
