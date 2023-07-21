#pragma once

#include <Arduino.h>
#include <chrono>

class PlaybackSpeedReader {
public:
  PlaybackSpeedReader(gpio_num_t gpio_num);
  std::chrono::milliseconds GetNoteLength();

private:
  gpio_num_t  gpio_num_;
};
