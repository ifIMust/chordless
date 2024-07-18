#pragma once
#include "../note_event.h"

#include <alsa/asoundlib.h>

namespace chordless {
  namespace alsa {
    class AlsaInput {
    public:
      AlsaInput();
      ~AlsaInput();

      bool IsValid() const noexcept;
      
      bool Read(NoteEvent &event);

    private:
      snd_seq_t *seq_handle_{nullptr};
      
      int error_{0};
    };
  }
}
