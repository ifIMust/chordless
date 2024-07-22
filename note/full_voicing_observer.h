#pragma once

#include "../note_observer.h"

namespace chordless {
  class NoteState;

  namespace ui {
    class TextSetter;
  }

  namespace note {
    class FullVoicingObserver : public NoteObserver {
    public:
      explicit FullVoicingObserver(chordless::NoteState&, chordless::ui::TextSetter&);

      void Observe() noexcept;
      
      FullVoicingObserver(const FullVoicingObserver&) = delete;
      FullVoicingObserver& operator=(const FullVoicingObserver&) = delete;

    private:
      chordless::NoteState& note_state_;
      chordless::ui::TextSetter &text_setter_;
    };
  }
}
