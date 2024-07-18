#include "note_event.h"

namespace chordless {
  NoteEvent::NoteEvent() {}
  
  NoteEvent::NoteEvent(bool on, unsigned char note, unsigned char velocity) :
    on_(on), note_(note), velocity_(velocity)
  {
    if (velocity == 0) {
      on_ = false;
    }
  }

  NoteEvent& NoteEvent::operator=(NoteEvent&& rhs) {
    on_ = rhs.on_;
    note_ = rhs.note_;
    velocity_ = rhs.velocity_;
    return *this;
  }
}
