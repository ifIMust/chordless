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

      if (best_chord_only_ && !all_chords.empty()) {
        auto best_chord = SelectBestChord(all_chords);
        ss << note_namer_->Name(best_chord.tonic_note) << best_chord.suffix << " ";
      } else {
        for (auto c : all_chords) {
          ss << note_namer_->Name(c.tonic_note) << c.suffix << " ";
        }
      }
    }
    text_ = ss.str().c_str();
    emit textChanged();
  }

  void ChordObserver::SetSharp(bool sharp) noexcept {
    note_namer_->SetSharp(sharp);
  }

  void ChordObserver::SetBestChordOnly(bool best_chord_only) noexcept {
    best_chord_only_ = best_chord_only;
  }

  Chord ChordObserver::SelectBestChord(const std::vector<Chord>& chords) const {
    if (chords.empty()) return {0, "", 0};

    Chord best_chord = chords[0];
    for (const auto& chord : chords) {
      if (chord.num_notes > best_chord.num_notes) {
        best_chord = chord;
      }
    }

    return best_chord;
  }

  void ChordObserver::AddMatcher(std::unique_ptr<ChordMatcher> &&matcher) {
    matchers_.push_back(std::move(matcher));
  }
}
