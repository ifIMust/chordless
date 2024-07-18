#pragma once

namespace chordless {
  class NoteEvent {
  public:
    NoteEvent();
    NoteEvent(bool on, unsigned char note, unsigned char velocity);
    NoteEvent& operator=(NoteEvent&& rhs);
    
    bool on_ {false};
    unsigned char note_ {0};
    unsigned char velocity_ {0};
  };
}
