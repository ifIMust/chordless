#pragma once

#include "note_observer.h"

#include "note_namer.h"

#include <memory>

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

      void SetNoteNamer(std::unique_ptr<NoteNamer>&&) noexcept;
      
      FullVoicingObserver(const FullVoicingObserver&) = delete;
      FullVoicingObserver& operator=(const FullVoicingObserver&) = delete;

    private:
      NoteState& note_state_;
      chordless::ui::TextSetter &text_setter_;
      std::unique_ptr<NoteNamer> note_namer_;
    };
  }
}
