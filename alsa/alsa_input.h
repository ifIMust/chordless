#pragma once
#include "../note/note_event.h"
#include "../note_input.h"

#include <alsa/asoundlib.h>

namespace chordless {
  namespace alsa {
    class AlsaInput : public ::chordless::NoteInput {
    public:
      AlsaInput();
      ~AlsaInput();

      bool IsValid() const noexcept;
      chordless::note::NoteEvent Read();

    private:
      snd_seq_t *seq_handle_{nullptr};
      
      int error_{0};
    };
  }
}
