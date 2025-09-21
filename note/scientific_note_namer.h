#pragma once

#include "note_namer.h"

#include "basic_note_namer.h"

#include <string>

namespace chordless::note {
  class ScientificNoteNamer : public NoteNamer {
  public:
    std::string Name(unsigned char note, bool sharp) noexcept override;
    void SetSharp(bool) noexcept override;
    bool GetSharp() const noexcept override;

  private:
    BasicNoteNamer base_namer_;
    std::string OctaveToSubscript(int octave) noexcept;
  };
}
