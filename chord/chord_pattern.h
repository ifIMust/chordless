#pragma once

#include "../note/note_constant.h"

#include <bitset>

namespace chordless::chord {
  struct ChordPattern {
    std::bitset<::chordless::note::kNumNotes> pattern;
    std::size_t pattern_width {0};
    std::size_t num_notes{0};
  };
}
