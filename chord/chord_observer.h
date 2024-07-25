#pragma once

#include "../note/note_observer.h"

#include "chord_matcher.h"

#include <memory>
#include <vector>

namespace chordless {
  namespace note {
    class NoteState;
  }

  namespace chord {
    class ChordObserver : public ::chordless::note::NoteObserver
    {
    public:
      explicit ChordObserver(::chordless::note::NoteState &note_state);
    
      void OnNoteChange() noexcept override;
      
      void AddMatcher(std::unique_ptr<ChordMatcher> &&matcher);

      static std::bitset<::chordless::note::kNumNotes> UniqueNotes(const std::bitset<::chordless::note::kNumNotes> &n);
      
      ChordObserver(const ChordObserver&) = delete;
      ChordObserver& operator=(const ChordObserver&) = delete;
    
    private:
      std::vector<std::unique_ptr<ChordMatcher>> matchers_;
      const ::chordless::note::NoteState &note_state_;
    };
  }
}
