#include "led_manager.h"

led::LedManager::LedManager(gpio_num_t gpio_num) : gpio_num_{gpio_num} {
  pinMode(gpio_num_, OUTPUT);
}

void led::LedManager::SetColor(led::Color color) {
  // TODO proper implementation for RGB LED
  if (color == Color::GREEN) {
    digitalWrite(gpio_num_, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(gpio_num_, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}
