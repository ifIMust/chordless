#pragma once
#include "../note/note_event.h"

#include <alsa/asoundlib.h>

namespace chordless {
  namespace alsa {
    class AlsaInput {
    public:
      AlsaInput();
      ~AlsaInput();

      bool IsValid() const noexcept;
      chordless::note::NoteEvent Read();
      
      bool ReadNote(chordless::note::NoteEvent &event);

    private:
      snd_seq_t *seq_handle_{nullptr};
      
      int error_{0};
    };
  }
}
