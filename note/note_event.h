#pragma once

namespace chordless {
  namespace note {

    enum class NoteEventType {
      NONE,
      NOTE_ON,
      NOTE_OFF
    };
    
    class NoteEvent {
    public:
      NoteEvent();
      NoteEvent(NoteEvent&& rhs);
      NoteEvent(bool on, unsigned char note, unsigned char velocity);
      NoteEvent& operator=(NoteEvent&& rhs);

      NoteEventType type_;
      unsigned char note_;
    };
  }
}
