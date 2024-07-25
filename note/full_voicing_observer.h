#pragma once

#include "note_observer.h"

#include "note_namer.h"

#include <memory>

namespace chordless {
  namespace note {
    class NoteState;    
    
    class FullVoicingObserver : public NoteObserver {
    public:
      explicit FullVoicingObserver(const NoteState&);

      void Observe() noexcept;

      void SetNoteNamer(std::unique_ptr<NoteNamer>&&) noexcept;
      
      FullVoicingObserver(const FullVoicingObserver&) = delete;
      FullVoicingObserver& operator=(const FullVoicingObserver&) = delete;

    private:
      const NoteState& note_state_;
      std::unique_ptr<NoteNamer> note_namer_;
    };
  }
}
