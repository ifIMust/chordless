#include "chord_matcher_config_factory.h"

#include "chord_matcher_config.h"
#include "chord_pattern.h"

namespace chordless::chord {
  std::unique_ptr<ChordMatcherConfig> makeMajorTriad() {
    auto config = std::make_unique<ChordMatcherConfig>();
    config->name = "Major Triad";
    ChordPattern root_position;
    root_position.num_notes = 3;
    root_position.pattern_width = 8;
    root_position.pattern.set(0);
    root_position.pattern.set(4);
    root_position.pattern.set(7);
    config->patterns.push_back(std::move(root_position));
    return config;
  }

  std::unique_ptr<ChordMatcherConfig> makeMinorTriad() {
    auto config = std::make_unique<ChordMatcherConfig>();
    config->name = "Minor Triad";
    config->suffix = "\u2098";
    ChordPattern root_position;
    root_position.num_notes = 3;
    root_position.pattern_width = 8;
    root_position.pattern.set(0);
    root_position.pattern.set(3);
    root_position.pattern.set(7);
    config->patterns.push_back(std::move(root_position));
    return config;
  }

  
  std::unique_ptr<ChordMatcherConfig> ChordMatcherConfigFactory::MakeConfig(ChordType chord_type) {
    switch (chord_type) {
    case ChordType::MAJOR_TRIAD:
      return makeMajorTriad();

    case ChordType::MINOR_TRIAD:
      return makeMinorTriad();

    default:
      return std::make_unique<ChordMatcherConfig>();
    }
  }
}
