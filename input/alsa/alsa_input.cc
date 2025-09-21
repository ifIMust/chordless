#include "alsa_input.h"
#include "../../logging.h"
#include <utility>

namespace chordless {
  namespace alsa {
    AlsaInput::AlsaInput() {
      error_ = snd_seq_open(&seq_handle_, "default", SND_SEQ_OPEN_INPUT, SND_SEQ_NONBLOCK);
      if (error_ < 0) {
        LOG_ERROR(alsaCategory, "Failed to open sequencer: ", snd_strerror(error_));
        return;
      }

      // Set client name
      int name_result = snd_seq_set_client_name(seq_handle_, "chordless");
      if (name_result < 0) {
        LOG_WARNING(alsaCategory, "Failed to set client name: ", snd_strerror(name_result));
        // Continue anyway, this is not fatal
      }

      // Create port
      error_ = snd_seq_create_simple_port(seq_handle_, "Input MIDI",
                                          SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
                                          SND_SEQ_PORT_TYPE_MIDI_GENERIC);
      if (error_ < 0) {
        LOG_ERROR(alsaCategory, "Failed to create MIDI port: ", snd_strerror(error_));
        snd_seq_close(seq_handle_);
        seq_handle_ = nullptr;
        return;
      }

      LOG_INFO(alsaCategory, "ALSA initialized successfully (client: ",
               snd_seq_client_id(seq_handle_), ", port: ", error_, ")");
    }

    AlsaInput::~AlsaInput() {
      if (seq_handle_) {
	snd_seq_close(seq_handle_);
      }
      seq_handle_ = nullptr;
    }

    bool AlsaInput::IsValid() const noexcept {
      return error_ == 0;
    }

    chordless::note::NoteEvent AlsaInput::Read() {
      snd_seq_event_t *ev_in {nullptr};
      auto result = snd_seq_event_input(seq_handle_, &ev_in);

      if (result == -EAGAIN || result == -ENOSPC) {
	return chordless::note::NoteEvent();
      }

      if (ev_in->type == SND_SEQ_EVENT_NOTEON ||
	  ev_in->type == SND_SEQ_EVENT_NOTEOFF) {
	return chordless::note::NoteEvent((ev_in->type == SND_SEQ_EVENT_NOTEON),
					  ev_in->data.note.note,
					  ev_in->data.note.velocity);
      }
      return chordless::note::NoteEvent();
    }
  }
}
