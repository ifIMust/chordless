#pragma once

#include <string>

namespace chordless::note {
  class NoteNamer {
  public:
    virtual std::string Name(unsigned char note, bool sharp = true) noexcept = 0;
  };
}
