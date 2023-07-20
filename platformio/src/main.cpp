#include <Arduino.h>

#include "FrequencyReader/frequency_reader.h"
#include "LedManager/led_manager.h"
#include "QuizManager/quiz_manager.h"
#include "SpeakerManager/speaker_manager.h"

enum class GameState {
  OFF,
  SETUP,
  EVALUATE_QUIZ,
  PLAYBACK_ROOT,
  PLAYBACK_MIDDLE,
  PLAYBACK_HIGH,
  VICTORY,
  SKIP,
  EASTER_EGG
};

// THE GLOBAL STUFF
GameState game_state = GameState::SETUP;
QuizManager quiz_manager{};
FrequencyReader middle_poti{GPIO_NUM_0}; // TODO GPIO num
FrequencyReader high_poti{GPIO_NUM_0};   // TODO GPIO num
led::LedManager status_led{GPIO_NUM_0};  // TODO GPIO num
SpeakerManager speaker{GPIO_NUM_0};      // TODO GPIO num

void IRAM_ATTR IsrOnSkipButton() {
  game_state = GameState::SETUP;
}

void IRAM_ATTR IsrOnPlayButton() {
  // Turns game on or off, depending on its previous state
  if (game_state == GameState::OFF) {
    game_state = GameState::SETUP;
  } else {
    game_state = GameState::OFF;
  }
}

void setup() {
  // TODO Hardware setup
  attachInterrupt(GPIO_NUM_0, IsrOnSkipButton, RISING);  // TODO GPIO num and mode
  attachInterrupt(GPIO_NUM_0, IsrOnPlayButton, RISING);  // TODO GPIO num and mode
}

void loop() {
  switch (game_state) {
  case GameState::OFF: {
    // TODO
  }
  case GameState::SETUP:
    // TODO
    status_led.SetColor(led::Color::RED);
    quiz_manager.GenerateNewRootTone();
    break;
  case GameState::EVALUATE_QUIZ: {
    auto middle_frequency = middle_poti.GetFrequency();
    auto high_frequency = high_poti.GetFrequency();

    // 1 == One out of two correct |  2 == Two out of two correct -> solved
    auto correct_tones =
        quiz_manager.GetNrOfCorrectTones(middle_frequency, high_frequency);
    if (1 == correct_tones) {
      status_led.SetColor(led::Color::YELLOW);
      break;
    } else if (2 == correct_tones) {
      game_state = GameState::VICTORY;
    } else if (quiz_manager.IsEasterEggTriggered(middle_frequency,
                                                 high_frequency)) {
      game_state = GameState::EASTER_EGG;
      break;
    }
    game_state = GameState::PLAYBACK_ROOT;
    break;
  }
  case GameState::PLAYBACK_ROOT:
    // TODO get frequency from poti (probably new class)
    speaker.Play(quiz_manager.GetRootFrequency(), std::chrono::milliseconds(1000));
    game_state = GameState::PLAYBACK_MIDDLE;
    break;
  case GameState::PLAYBACK_MIDDLE:
    speaker.Play(middle_poti.GetFrequency(), std::chrono::milliseconds(1000));
    game_state = GameState::PLAYBACK_HIGH;
    break;
  case GameState::PLAYBACK_HIGH:
    speaker.Play(high_poti.GetFrequency(), std::chrono::milliseconds(1000));
    game_state = GameState::EVALUATE_QUIZ;
    break;
  case GameState::VICTORY:
    status_led.SetColor(led::Color::GREEN);
    // TODO play melody
    game_state = GameState::SETUP;
    break;
  case GameState::SKIP:
    // TODO play sad melody
    game_state = GameState::SETUP;
    break;
  case GameState::EASTER_EGG:
    // TODO play easter egg melody
    game_state = GameState::SETUP;
    break;
  default:
    // This should never happen
    break;
  }
}
