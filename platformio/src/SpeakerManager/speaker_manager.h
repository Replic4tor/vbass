#pragma once

#include <chrono>
#include <cstdlib>
#include <Arduino.h>
#include <DacESP32.h>

class SpeakerManager {
 public:
  SpeakerManager(gpio_num_t gpio_num);
  void Play(uint32_t frequency, std::chrono::milliseconds length);

 private:
  gpio_num_t gpio_num_;
  DacESP32 dac_;
  const std::chrono::milliseconds NOTE_CUTOFF_{10};
};
