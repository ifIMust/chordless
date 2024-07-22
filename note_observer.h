#pragma once

namespace chordless {
  class NoteObserver {
  public:
    virtual void Observe() noexcept = 0;
  };
}
