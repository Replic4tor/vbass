#include <Arduino.h>

#include "FrequencyReader/frequency_reader.h"
#include "LedManager/led_manager.h"
#include "PlaybackSpeedReader/playback_speed_reader.h"
#include "QuizManager/quiz_manager.h"
#include "SpeakerManager/speaker_manager.h"
#include "Soundbits/soundbits.h"

enum GameState {
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
GameState game_state = GameState::OFF;
bool button_event = false;
QuizManager quiz_manager{};
FrequencyReader middle_poti{GPIO_NUM_32};
FrequencyReader high_poti{GPIO_NUM_33};
led::LedManager status_led{GPIO_NUM_0};    // TODO GPIO num
SpeakerManager speaker{GPIO_NUM_25};
PlaybackSpeedReader speed_poti{GPIO_NUM_0};// TODO GPIO num
float octave_offset = 2;                   // TODO Make adjustable with rotary switch, e.g. 0.5, 2

void IRAM_ATTR IsrOnSkipButton() {
  // TODO debouncing
  Serial.println("IsrOnSkipButton");   // TODO rm debug
  game_state = GameState::SKIP;
  button_event = true;
}

void IRAM_ATTR IsrOnPlayButton() {
  // TODO debouncing
  Serial.println("IsrOnPlayButton");  // TODO rm debug
  // Turns game on or off, depending on its previous state
  if (game_state == GameState::OFF) {
    game_state = GameState::SETUP;
  } else {
    game_state = GameState::OFF;
  }
  button_event = true;
}

void SwitchStateTo(GameState next_game_state) {
  if (button_event) {
    // Do not switch state because play button decision has priority
    button_event = false;
  } else {
    game_state = next_game_state;
  }
}

// TODO ISR for rotary switch turn events

void setup() {
  Serial.begin(115200);
  // TODO Hardware setup, e.g. GPIO direction
  attachInterrupt(GPIO_NUM_35, IsrOnSkipButton,
                  RISING);// TODO GPIO num and mode
  attachInterrupt(GPIO_NUM_34, IsrOnPlayButton,
                  RISING);// TODO GPIO num and mode
  game_state = GameState::OFF;
}

void loop() {
  switch (game_state) {
    case GameState::OFF: {
      status_led.SetColor(led::Color::RED);
      delay(1000);
      break;
      // TODO
    }
    case GameState::SETUP:
      // TODO
      status_led.SetColor(led::Color::RED);
      quiz_manager.GenerateNewRootTone();
      SwitchStateTo(GameState::EVALUATE_QUIZ);
      break;
    case GameState::EVALUATE_QUIZ: {
      delay(2000); // TODO remove?
      auto middle_frequency = middle_poti.GetFrequency();
      auto high_frequency = high_poti.GetFrequency();

      // 1 == One out of two correct |  2 == Two out of two correct -> solved
      auto correct_tones = quiz_manager.GetNrOfCorrectTones(middle_frequency, high_frequency);
      if (1 == correct_tones) {
        status_led.SetColor(led::Color::YELLOW);
        break;
      } else if (2 == correct_tones) {
        SwitchStateTo(GameState::VICTORY);
        break;
      } else if (quiz_manager.IsEasterEggTriggered(middle_frequency, high_frequency)) {
        SwitchStateTo(GameState::EASTER_EGG);
        break;
      }
      SwitchStateTo(GameState::PLAYBACK_ROOT);
      break;
    }
    case GameState::PLAYBACK_ROOT:
      speaker.Play(quiz_manager.GetRootFrequency() * octave_offset, speed_poti.GetNoteLength());
      SwitchStateTo(GameState::PLAYBACK_MIDDLE);
      break;
    case GameState::PLAYBACK_MIDDLE:
      speaker.Play(middle_poti.GetFrequency() * octave_offset, speed_poti.GetNoteLength());
      SwitchStateTo(GameState::PLAYBACK_HIGH);
      break;
    case GameState::PLAYBACK_HIGH:
      speaker.Play(high_poti.GetFrequency() * octave_offset, speed_poti.GetNoteLength());
      SwitchStateTo(GameState::EVALUATE_QUIZ);
      break;
    case GameState::VICTORY:
      status_led.SetColor(led::Color::GREEN);
      speaker.Play(quiz_manager.GetRootFrequency() * octave_offset, speed_poti.GetNoteLength());
      speaker.Play(middle_poti.GetFrequency() * octave_offset, speed_poti.GetNoteLength());
      speaker.Play(high_poti.GetFrequency() * octave_offset, speed_poti.GetNoteLength());
      delay(500);
      PlayVictorySong(speaker);
      SwitchStateTo(GameState::SETUP);
      break;
    case GameState::SKIP:
      PlaySkipSong(speaker);
      SwitchStateTo(game_state = GameState::SETUP);
      break;
    case GameState::EASTER_EGG:
      // TODO play easter egg melody
      SwitchStateTo(GameState::SETUP);
      break;
    default:
      // This should never happen
      break;
  }

  Serial.println(game_state);
}
