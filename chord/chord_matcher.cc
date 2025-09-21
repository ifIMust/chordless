#include "chord_matcher.h"

#include "chord_matcher_config.h"
#include "../note/note_state.h"

namespace chordless::chord {
  using NoteSet = std::bitset<::chordless::note::kNumNotes>;
  
  ChordMatcher::ChordMatcher() :
    config_(std::make_unique<ChordMatcherConfig>())
  {}
  
  std::vector<Chord> ChordMatcher::MatchRooted(const std::bitset<::chordless::note::kNumNotes> &rooted_notes,
					       unsigned char root_note, unsigned char num_notes) noexcept {
    const unsigned char tonic_note = root_note + config_->tonic;
    std::vector<Chord> chords;
    
    // If any pattern matches, that is sufficient
    for (const auto chord_pattern : config_->patterns) {
      if ((num_notes == chord_pattern.num_notes) &&
	  (rooted_notes & chord_pattern.pattern) == chord_pattern.pattern) {
	chords.push_back(Chord{tonic_note, config_->suffix, chord_pattern.num_notes});
	break;
      }
    }
    return chords;
  }

  void ChordMatcher::SetConfig(std::unique_ptr<ChordMatcherConfig> &&config) {
    config_ = std::move(config);
  }
}
