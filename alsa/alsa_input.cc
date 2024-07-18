#include "alsa_input.h"

namespace chordless {
  namespace alsa {
    AlsaInput::AlsaInput() {
      error_ = snd_seq_open(&seq_handle_, "default", SND_SEQ_OPEN_INPUT, 0);
      if (error_ != 0) {
	return;
      }

      error_ = snd_seq_create_simple_port(seq_handle_, "Input",
					  SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
					  SND_SEQ_PORT_TYPE_MIDI_GENERIC );
    }

    AlsaInput::~AlsaInput() {
      if (seq_handle_) {
	snd_seq_close(seq_handle_);
      }
    }

    bool AlsaInput::IsValid() const noexcept {
      return error_ == 0;
    }

    bool AlsaInput::Read(NoteEvent &event) {
      snd_seq_event_t *ev_in {nullptr};
      error_ = snd_seq_event_input(seq_handle_, &ev_in);

      if (ev_in->type == SND_SEQ_EVENT_NOTEON ||
	  ev_in->type == SND_SEQ_EVENT_NOTEOFF) {

	NoteEvent out((ev_in->type == SND_SEQ_EVENT_NOTEON), ev_in->data.note.note, ev_in->data.note.velocity);
	event = std::move(out);
	return true;
      }
      return false;
    }
  }
}
