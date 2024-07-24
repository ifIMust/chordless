#pragma once

#include <memory>

namespace chordless::chord {
  struct ChordMatcherConfig;
  
  enum class ChordType {
    MAJOR_TRIAD,
      MINOR_TRIAD
  };
  
  class ChordMatcherConfigFactory {
  public:
    std::unique_ptr<ChordMatcherConfig> MakeConfig(ChordType);
  };
  
}
