#include "note_reader.h"

#include "note_event.h"
#include "note_observer.h"
#include "note_state.h"
#include "../input/note_input.h"

#include <thread>

namespace chordless::note {
  NoteReader::NoteReader(input::NoteInput &input, NoteState &state) :
    note_input_(input), note_state_(state)
  {}

  void NoteReader::run() {
    read_input_.store(true);

    while (this->read_input_.load()) {
      // Non-blocking read, so the app can shut down cleanly.
      // Sleep if we haven't seen note action, to keep CPU usage down.
      auto event = this->note_input_.Read();
      if (event.type_ == NoteEventType::NONE) {
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(50ms);
      } else {
	if (event.type_ == NoteEventType::NOTE_ON) {
	  this->note_state_.NoteOn(event.note_);
	} else {
	  this->note_state_.NoteOff(event.note_);
	}

	for (auto o : observers_) {
	  o.get().Observe();
	}
      }
    }
  }

  void NoteReader::Stop() {
    read_input_.store(false);
    wait();
  }

  void NoteReader::AddObserver(NoteObserver &o) {
    observers_.push_back(std::ref(o));
  }
}
