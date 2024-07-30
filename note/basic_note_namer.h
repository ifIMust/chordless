#pragma once

#include "note_namer.h"

#include <string>

namespace chordless::note {
  class BasicNoteNamer : public NoteNamer {
  public:
    std::string Name(unsigned char note, bool sharp = true) noexcept override;
    void SetSharp(bool) noexcept override;

  private:
    bool sharp_ {true};
  };
}
