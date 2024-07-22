#pragma once

#include <functional>
#include <future>
#include <vector>

namespace chordless {
  class NoteInput;
  class NoteObserver;

  namespace note {
    class NoteState;
  }
  
  class NoteReader {
  public:
    NoteReader(NoteInput &, note::NoteState &);

    void Run();
    void Stop();

    void AddObserver(NoteObserver&);
    
  private:
    NoteInput &note_input_;
    note::NoteState &note_state_;

    std::atomic<bool> read_input_;
    std::future<void> read_fut_;

    std::vector<std::reference_wrapper<NoteObserver>> observers_;
  };
}
