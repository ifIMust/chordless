#include "note_event.h"

namespace chordless {
  namespace note {
    NoteEvent::NoteEvent() : type_(NoteEventType::NONE) {}

    NoteEvent::NoteEvent(NoteEvent&& rhs) {
      type_ = rhs.type_;
      note_ = rhs.note_;
    }
  
    NoteEvent::NoteEvent(bool on, unsigned char note, unsigned char velocity) :
      type_(NoteEventType::NOTE_ON), note_(note)
    {
      if (velocity == 0 || !on) {
	type_ = NoteEventType::NOTE_OFF;
      }
    }

    NoteEvent& NoteEvent::operator=(NoteEvent&& rhs) {
      type_ = rhs.type_;
      note_ = rhs.note_;
      return *this;
    }
  }
}
