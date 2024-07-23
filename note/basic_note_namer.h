#pragma once

#include "note_namer.h"

#include <string>

namespace chordless::note {
  class BasicNoteNamer : public NoteNamer {
  public:
    std::string Name(unsigned char note, bool sharp = true) noexcept override;
  };
}
