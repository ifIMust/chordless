#include "chord_observer.h"

#include "../ui/text_setter.h"

#include <sstream>
#include <utility>

namespace chordless::chord {
  ChordObserver::ChordObserver(::chordless::note::NoteState &note_state,
			       ::chordless::ui::TextSetter &text_setter) :
    note_state_(note_state), text_setter_(text_setter)
  {}

  void ChordObserver::Observe() noexcept {
    std::vector<Chord> all_chords;
    
    for (const auto &cm : matchers_) {
      auto chords = cm->Match(note_state_);
      
      // I don't have C++23 library support yet :(
      // all_chords.append_range(std::move(chords));

      all_chords.insert(all_chords.cend(), chords.cbegin(), chords.cend());
    }

    std::ostringstream ss;
    for (auto c : all_chords) {
      ss << c.name << "\n";
    }
    text_setter_.SetText(ss.str());
  }

  void ChordObserver::AddMatcher(std::unique_ptr<ChordMatcher> &&matcher) {
    matchers_.push_back(std::move(matcher));
  }
}
