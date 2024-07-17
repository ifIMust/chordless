#include "note_state.h"

namespace chordless {
  void NoteState::NoteOn(unsigned char note) {
    notes_.set(note, true);
  }

  void NoteState::NoteOff(unsigned char note) {
    notes_.set(note, false);
  }
  
  std::size_t NoteState::NumNotesOn() const noexcept {
    return notes_.count();
  }
}
