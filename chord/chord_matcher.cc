#include "chord_matcher.h"

#include "chord_matcher_config.h"
#include "../note/basic_note_namer.h"
#include "../note/note_state.h"

namespace chordless::chord {
  using NoteSet = std::bitset<::chordless::note::kNumNotes>;
  
  ChordMatcher::ChordMatcher() :
    config_(std::make_unique<ChordMatcherConfig>()),
    note_namer_(std::make_unique<chordless::note::BasicNoteNamer>())
  {}
  
  std::vector<Chord> ChordMatcher::MatchRooted(const std::bitset<::chordless::note::kNumNotes> &rooted_notes,
					       unsigned char root_note, unsigned char num_notes) noexcept {
    std::vector<Chord> chords;
    // If any pattern matches, that is sufficient
    for (const auto chord_pattern : config_->patterns) {
      if ((num_notes == chord_pattern.num_notes) &&
	  (rooted_notes & chord_pattern.pattern) == chord_pattern.pattern) {
	auto chord_name = note_namer_->Name(root_note) + config_->suffix;
	chords.push_back(Chord{chord_name});
	break;
      }
    }
    return chords;
  }

  void ChordMatcher::SetConfig(std::unique_ptr<ChordMatcherConfig> &&config) {
    config_ = std::move(config);
  }
}
