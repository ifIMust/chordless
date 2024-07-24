#include "chord_matcher_config_factory.h"

#include "chord_matcher_config.h"

namespace chordless::chord {
  std::unique_ptr<ChordMatcherConfig> ChordMatcherConfigFactory::MakeConfig(ChordType) {
    auto config = std::make_unique<ChordMatcherConfig>();
    config->name = "Major Triad";
    config->num_notes = 3;
    config->pattern_width = 8;
    config->pattern.set(0);
    config->pattern.set(4);
    config->pattern.set(7);
    return config;
  }
}
