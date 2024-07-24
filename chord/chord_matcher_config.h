#pragma once

#include <bitset>
#include <string>

namespace chordless::chord {
  constexpr auto kPatternMaxWidth = 128;

  struct ChordMatcherConfig {
    std::bitset<kPatternMaxWidth> pattern;
    std::size_t pattern_width {0};
    std::size_t num_notes{0};
    std::string name;
  };
}
