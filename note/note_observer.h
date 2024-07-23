#pragma once

namespace chordless::note {
  class NoteObserver {
  public:
    virtual void Observe() noexcept = 0;
  };
}
