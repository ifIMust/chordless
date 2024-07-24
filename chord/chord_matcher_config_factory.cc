#include "chord_matcher_config_factory.h"

#include "chord_matcher_config.h"

namespace chordless::chord {
  std::unique_ptr<ChordMatcherConfig> ChordMatcherConfigFactory::MakeConfig(ChordType chord_type) {
    auto config = std::make_unique<ChordMatcherConfig>();
    
    switch (chord_type) {
    case ChordType::MAJOR_TRIAD:
      config->name = "Major Triad";
      config->num_notes = 3;
      config->pattern_width = 8;
      config->pattern.set(0);
      config->pattern.set(4);
      config->pattern.set(7);
      break;

    case ChordType::MINOR_TRIAD:
      config->name = "Minor Triad";
      config->suffix = "\u2098";
      config->num_notes = 3;
      config->pattern_width = 8;
      config->pattern.set(0);
      config->pattern.set(3);
      config->pattern.set(7);
      break;
    }
    return config;
  }
}
