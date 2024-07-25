#include "chord_observer.h"

#include "../note/note_constant.h"
#include "../note/note_state.h"

#include <sstream>
#include <utility>

namespace chordless::chord {
  ChordObserver::ChordObserver(::chordless::note::NoteState &note_state) :
    note_state_(note_state)
  {}

  void ChordObserver::OnNoteChange() noexcept {
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
      }
      
      for (const auto &cm : matchers_) {
	auto chords = cm->MatchRooted(notes, root_note, num_notes);
	all_chords.insert(all_chords.cend(), chords.cbegin(), chords.cend());
      }

      for (auto c : all_chords) {
	ss << c.name << " ";
      }
    }
    emit textChanged(QString(ss.str().c_str()));
  }

  void ChordObserver::AddMatcher(std::unique_ptr<ChordMatcher> &&matcher) {
    matchers_.push_back(std::move(matcher));
  }
}
