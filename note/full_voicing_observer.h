#pragma once

#include "note_observer.h"

namespace chordless {
  namespace ui {
    class TextSetter;
  }

  namespace note {
    class NoteState;    
    
    class FullVoicingObserver : public NoteObserver {
    public:
      explicit FullVoicingObserver(NoteState&, chordless::ui::TextSetter&);

      void Observe() noexcept;
      
      FullVoicingObserver(const FullVoicingObserver&) = delete;
      FullVoicingObserver& operator=(const FullVoicingObserver&) = delete;

    private:
      NoteState& note_state_;
      chordless::ui::TextSetter &text_setter_;
    };
  }
}
