#include "chord_matcher.h"

#include "chord_matcher_config.h"
#include "../note/basic_note_namer.h"
#include "../note/note_state.h"

// remove, debug
#include <iostream>

namespace chordless::chord {
  using NoteSet = std::bitset<::chordless::note::kNumNotes>;
  
  ChordMatcher::ChordMatcher() :
    config_(std::make_unique<ChordMatcherConfig>()),
    note_namer_(std::make_unique<chordless::note::BasicNoteNamer>())
  {}
  
  //  NoteSet getUniqueNotes(const NoteSet&) {}
  
  std::vector<Chord> ChordMatcher::Match(const note::NoteState &note_state) noexcept {
    std::vector<Chord> chords;
    NoteSet notes(note_state.GetBits());

    // Special cases: Null config or no notes played
    if (config_->patterns.empty() || notes.count() == 0) {
      return chords;
    }

    // Find the lowest "on" note. Bitshift until we find it.
    // There must be at least one note, confirmed by checking above.
    auto root_note = 0;
    NoteSet rooted_notes(notes);
    while (!rooted_notes.test(0)) {
      rooted_notes >>= 1;
      ++root_note;
    }

    // If any pattern matches, we have a match and stop
    for (const auto chord_pattern : config_->patterns) {
      if ((rooted_notes & chord_pattern.pattern) == chord_pattern.pattern) {
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
