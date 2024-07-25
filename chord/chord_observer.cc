#include "chord_observer.h"

#include "../note/note_constant.h"
#include "../note/note_state.h"
#include "../ui/text_setter.h"

#include <sstream>
#include <utility>

#include <iostream>

namespace chordless::chord {
  ChordObserver::ChordObserver(::chordless::note::NoteState &note_state,
			       ::chordless::ui::TextSetter &text_setter) :
    note_state_(note_state), text_setter_(text_setter)
  {}

  void ChordObserver::Observe() noexcept {
    using NoteSet = std::bitset<::chordless::note::kNumNotes>;
    std::ostringstream ss;
    std::vector<Chord> all_chords;

    NoteSet notes(note_state_.GetBits());
    const auto num_notes = notes.count();
    if (num_notes > 0) {
      // Find the lowest "on" note. Bitshift until we find it.
      auto root_note = 0;
      while (!notes.test(0)) {
	notes >>= 1;
	++root_note;
	if (root_note > ::chordless::note::kNumNotes) {
	  std::cerr << "Would have looped forever! Broke the cycle.\n";
	  break;
	}
      }
      
      for (const auto &cm : matchers_) {
	auto chords = cm->MatchRooted(notes, root_note, num_notes);
	all_chords.insert(all_chords.cend(), chords.cbegin(), chords.cend());
      }

      for (auto c : all_chords) {
	ss << c.name << " ";
      }
    }
    text_setter_.SetText(ss.str());
  }

  void ChordObserver::AddMatcher(std::unique_ptr<ChordMatcher> &&matcher) {
    matchers_.push_back(std::move(matcher));
  }
}
