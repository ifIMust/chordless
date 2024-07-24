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

    // Special cases: Null config or no notes played
    if (config_->num_notes == 0 || note_state.NumNotesOn() == 0) {
      return chords;
    }

    NoteSet notes(note_state.GetBits());

    // Find the lowest "on" note. Bitshift until we find it.
    // There must be at least one note, confirmed by checking above.
    auto root_note = 0;
    NoteSet rooted_notes(notes);
    while (!rooted_notes.test(0)) {
      rooted_notes >>= 1;
      ++root_note;
    }

    if ((rooted_notes & config_->pattern) == config_->pattern) {
      chords.push_back(Chord{note_namer_->Name(root_note)});
    }
    return chords;
  }

  void ChordMatcher::SetConfig(std::unique_ptr<ChordMatcherConfig> &&config) {
    config_ = std::move(config);
  }
}
