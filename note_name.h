#pragma once

#include <string>

namespace chordless {
  class NoteName {
  public:
    static std::string Name(unsigned char note, bool sharp = true);

  };
}
