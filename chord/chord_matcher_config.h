#pragma once

#include "chord_pattern.h"

#include <string>
#include <vector>

namespace chordless::chord {
  struct ChordMatcherConfig {
    std::string name;
    std::string suffix;
    std::vector<ChordPattern> patterns;
  };
}
