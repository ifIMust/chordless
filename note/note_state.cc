#include "note_state.h"

namespace chordless {
  namespace note {
    void NoteState::NoteOn(unsigned char note) {
      notes_.set(note, true);
    }

    void NoteState::NoteOff(unsigned char note) {
      notes_.set(note, false);
    }
  
    std::size_t NoteState::NumNotesOn() const noexcept {
      return notes_.count();
    }

    void NoteState::GetNotes(std::vector<unsigned char> &notes) {
      for (unsigned char i = 0; i < kNumNotes; ++i) {
	if (notes_.test(i)) {
	  notes.push_back(i);
	}
      }
    }
  }
}
