#include "chord_observer.h"

#include "../note/basic_note_namer.h"
#include "../note/note_constant.h"
#include "../note/note_state.h"

#include <sstream>
#include <utility>

namespace chordless::chord {
  using NoteSet = std::bitset<::chordless::note::kNumNotes>;

  ChordObserver::ChordObserver(::chordless::note::NoteState &note_state) :
    note_state_(note_state),
    note_namer_(std::make_unique<chordless::note::BasicNoteNamer>())
  {}

  NoteSet ChordObserver::UniqueNotes(const NoteSet &n) {
    constexpr auto unique_mask = 0x0fff;
    constexpr NoteSet unique_filter(unique_mask);

    NoteSet notes(n);
    NoteSet unique_notes;
    while (notes.any()) {
      unique_notes |= unique_filter & notes;
      notes >>= 12;
    }
    return unique_notes;
  }


  void ChordObserver::OnNoteChange() noexcept {
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

      const auto unique_notes = UniqueNotes(notes);
      const auto num_unique_notes = unique_notes.count();
      
      for (const auto &cm : matchers_) {
	auto chords = cm->MatchRooted(unique_notes, root_note, num_unique_notes);
	all_chords.insert(all_chords.cend(), chords.cbegin(), chords.cend());
      }

      for (auto c : all_chords) {
	ss << note_namer_->Name(c.tonic_note) << c.suffix << " ";
      }
    }
    text_ = ss.str().c_str();
    emit textChanged();
  }

  void ChordObserver::SetSharp(bool sharp) noexcept {
    note_namer_->SetSharp(sharp);
  }

  void ChordObserver::AddMatcher(std::unique_ptr<ChordMatcher> &&matcher) {
    matchers_.push_back(std::move(matcher));
  }
}
