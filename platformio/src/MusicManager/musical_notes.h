#pragma once

namespace music {

enum NOTE {
  C4 = 262,
  D4 = 294,
  E4 = 330,
  F4 = 349,
  G4 = 392,
  A4 = 440,
  B4 = 494,
  C5 = 523,
  D5 = 587,
  E5 = 659,
  F5 = 698,
  G5 = 784,
  A5 = 880,
  B5 = 988,
  C6 = 1046
};

enum NOTE_LENGTH { FULL = 1, HALF = 2, QUARTER = 4, EIGTH = 8, SIXTEENTH = 16 };
} // namespace music
