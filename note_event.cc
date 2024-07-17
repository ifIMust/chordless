#include "note_event.h"

namespace chordless {
  NoteEvent::NoteEvent() {}
  
  NoteEvent::NoteEvent(bool on, unsigned char note, unsigned char velocity) :
    on_(on), note_(note), velocity_(velocity)
  {}

}
