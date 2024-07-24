#pragma once

#include "../note/note_observer.h"

#include "chord_matcher.h"

#include <memory>
#include <vector>

namespace chordless {
  namespace note {
    class NoteState;
  }
  namespace ui {
    class TextSetter;
  }
  
  namespace chord {
    class ChordObserver : public ::chordless::note::NoteObserver
    {
    public:
      explicit ChordObserver(::chordless::note::NoteState &note_state,
			     ::chordless::ui::TextSetter &text_setter);
    
      void Observe() noexcept override;

      void AddMatcher(std::unique_ptr<ChordMatcher> &&matcher);
      
      ChordObserver(const ChordObserver&) = delete;
      ChordObserver& operator=(const ChordObserver&) = delete;
    
    private:
      std::vector<std::unique_ptr<ChordMatcher>> matchers_;
      const ::chordless::note::NoteState &note_state_;
      chordless::ui::TextSetter &text_setter_;
    };
  }
}
