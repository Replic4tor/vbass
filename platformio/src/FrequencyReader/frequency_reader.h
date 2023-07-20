#pragma once

#include <Arduino.h>

class FrequencyReader {
public:
  FrequencyReader(gpio_num_t gpio_num);
  uint32_t GetFrequency();

private:
  gpio_num_t  gpio_num_;
};
