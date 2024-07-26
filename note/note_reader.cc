#include "note_reader.h"

#include "note_event.h"
#include "note_observer.h"
#include "note_state.h"
#include "../input/note_input.h"

namespace chordless::note {
  NoteReader::NoteReader(input::NoteInput &input, NoteState &state) :
    note_input_(input), note_state_(state)
  {}

  NoteReader::~NoteReader() {
    read_input_.store(false);
    wait();
  }

  void NoteReader::run() {
    read_input_.store(true);

    while (this->read_input_.load()) {
      // There doesn't seem to be a way to break the ALSA sequencer out
      // of a block read operation.
      // Thus, use a non-blocking read, so the app can shut down cleanly.
      // Sleep if we haven't seen note action, to keep CPU usage down.
      auto event = this->note_input_.Read();
      if (event.type_ == NoteEventType::NONE) {
	// 50 ms
	msleep(50);
      } else {
	if (event.type_ == NoteEventType::NOTE_ON) {
	  this->note_state_.NoteOn(event.note_);
	} else {
	  this->note_state_.NoteOff(event.note_);
	}

	emit noteChange();
      }
    }
  }

  void NoteReader::AddObserver(NoteObserver &o) {
    connect(this, SIGNAL(noteChange()), &o, SLOT(OnNoteChange()));
    observers_.push_back(std::ref(o));
  }
}
