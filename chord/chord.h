#pragma once

#include <string>

namespace chordless::chord {
  struct Chord {
    unsigned char tonic_note{0};
    std::string suffix;
  };
}
