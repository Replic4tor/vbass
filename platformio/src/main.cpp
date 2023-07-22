#include <AiEsp32RotaryEncoder.h>
#include <Arduino.h>
#include <map>

#include "FrequencyReader/frequency_reader.h"
#include "LedManager/led_manager.h"
#include "PlaybackSpeedReader/playback_speed_reader.h"
#include "QuizManager/quiz_manager.h"
#include "Soundbits/soundbits.h"
#include "SpeakerManager/speaker_manager.h"

enum GameState { OFF, SETUP, EVALUATE_QUIZ, PLAYBACK_ROOT, PLAYBACK_MIDDLE, PLAYBACK_HIGH, VICTORY, SKIP, EASTER_EGG };

namespace {
String ToString(GameState game_state) {
  switch (game_state) {
    case OFF:
      return "OFF";
    case SETUP:
      return "SETUP";
    case EVALUATE_QUIZ:
      return "EVALUATE_QUIZ";
    case PLAYBACK_ROOT:
      return "PLAYBACK_ROOT";
    case PLAYBACK_MIDDLE:
      return "PLAYBACK_MIDDLE";
    case PLAYBACK_HIGH:
      return "PLAYBACK_HIGH";
    case VICTORY:
      return "VICTORY";
    case SKIP:
      return "SKIP";
    case EASTER_EGG:
      return "EASTER_EGG";
  }
}
}

// Rotary Encoder
#define ROTARY_ENCODER_A_PIN 23
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 21
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

// THE GLOBAL STUFF
GameState game_state = GameState::OFF;
bool button_event = false;
QuizManager quiz_manager{};
FrequencyReader middle_poti{GPIO_NUM_32};
FrequencyReader high_poti{GPIO_NUM_33};
led::LedManager status_led{GPIO_NUM_0};// TODO GPIO num
SpeakerManager speaker{GPIO_NUM_25};
PlaybackSpeedReader speed_poti{GPIO_NUM_0};// TODO GPIO num
AiEsp32RotaryEncoder rotary_encoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
float octave_offset = 2;                   // TODO Make adjustable with rotary switch, e.g. 0.5, 2

void IRAM_ATTR IsrOnSkipButton() {
  Serial.println("IsrOnSkipButton");

  static unsigned long last_interrupt_time = 0;

  if (millis() - last_interrupt_time > 200) {
    Serial.println("Skip!");
    game_state = GameState::SKIP;
    button_event = true;
    last_interrupt_time = millis();
  }
}

void IRAM_ATTR IsrOnPlayButton() {
  Serial.println("IsrOnPlayButton");

  static unsigned long last_interrupt_time = 0;

  if (millis() - last_interrupt_time > 200) {
    // Turns game on or off, depending on its previous state
    if (game_state == GameState::OFF) {
      Serial.println("Start!");
      game_state = GameState::SETUP;
    } else {
      Serial.println("Stop!");
      game_state = GameState::OFF;
    }

    button_event = true;
    last_interrupt_time = millis();
  }
}

// Encoder value can range between -2 and 2 (inclusive)
std::map<int, float> ocatve_offset_mapping {
    {-2, 0.25},
    {-1, 0.5},
    {0, 1},
    {1, 2},
    {2, 4}
};

void RotaryEncoderLoop()
{
  if (rotary_encoder.encoderChanged())
  {
    auto encoder_value = rotary_encoder.readEncoder();
    Serial.println((String)"Encoder value: " + encoder_value);
    if (ocatve_offset_mapping.find(encoder_value) != ocatve_offset_mapping.end()) {
      octave_offset = ocatve_offset_mapping.at(encoder_value);
    } else {
      octave_offset = 2;
    }
  }
}

void IRAM_ATTR ReadEncoderISR()
{
  rotary_encoder.readEncoder_ISR();
}

void SwitchStateTo(GameState next_game_state) {
  if (button_event) {
    // Do not switch state because play button decision has priority
    button_event = false;
  } else {
    game_state = next_game_state;
  }
}

void setup() {
  Serial.begin(115200);
  // TODO Hardware setup, e.g. GPIO direction
  attachInterrupt(GPIO_NUM_35, IsrOnSkipButton, RISING);
  attachInterrupt(GPIO_NUM_34, IsrOnPlayButton, RISING);
  game_state = GameState::OFF;

  // Rotary Encoder
  rotary_encoder.begin();
  rotary_encoder.setup(ReadEncoderISR);
  rotary_encoder.setBoundaries(-2, 2, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotary_encoder.disableAcceleration();
}

void loop() {
  RotaryEncoderLoop();

  switch (game_state) {
    case GameState::OFF: {
      status_led.SetColor(led::Color::RED);
      delay(500);
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
      delay(500);// TODO remove?
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

  Serial.println(ToString(game_state));
}
