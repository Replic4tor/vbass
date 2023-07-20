#pragma once

#include <Arduino.h>

namespace led {
enum class Color {
  RED,
  YELLOW,
  GREEN
};

class LedManager {
 public:
  LedManager(gpio_num_t gpio_num);
  void SetColor(Color color);

 private:
  gpio_num_t gpio_num_;
};
}
