#pragma once

namespace chordless {
  namespace note {
    class NoteEvent;
  }
  
  class NoteInput {
  public:
    virtual bool IsValid() = 0;
    virtual NoteEvent Read() = 0;
  };
}
