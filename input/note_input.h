#pragma once

namespace chordless {
  namespace note {
    class NoteEvent;
  }

  namespace input {
    class NoteInput {
    public:
      virtual bool IsValid() const noexcept = 0;
      virtual note::NoteEvent Read() = 0;
    };
  }
}
