#include "frequency_reader.h"

#include <musical_notes.h>

FrequencyReader::FrequencyReader(gpio_num_t gpio_num) : gpio_num_{gpio_num} {
}

uint32_t FrequencyReader::GetFrequency() {
  auto raw_value = (double) analogRead(gpio_num_);
  auto frequency = (raw_value/4096) * 538 + 262;
  return frequency;
}
