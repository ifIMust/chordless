#include "chord_label.h"

#include "../note/note_event.h"
#include "../note_name.h"
#include "../note_state.h"
#include "../alsa/alsa_input.h"

#include <chrono>
#include <sstream>
#include <thread>

namespace chordless {
  namespace ui {
    ChordLabel::ChordLabel(QWidget *parent, chordless::alsa::AlsaInput &alsa_input) :
      QLabel(parent), alsa_input_(alsa_input) {
      using namespace std::chrono_literals;
      
      read_input_.store(true);
      
      this->setText("Play to begin");

      read_fut_ = std::async(std::launch::async, [this](){
	chordless::NoteState note_state;
	chordless::note::NoteEvent event;
	std::vector<unsigned char> notes;

	while (this->read_input_.load()) {
	  // Non-blocking read, so the app can shut down cleanly.
	  // Sleep if we haven't seen note action, to keep CPU usage down.
	  auto had_event = this->alsa_input_.ReadNote(event);
	  if (had_event && event.type_ != chordless::note::NoteEventType::NONE) {
	    auto &note = event.note_;
	    event.type_ == chordless::note::NoteEventType::NOTE_ON ? note_state.NoteOn(note) : note_state.NoteOff(note);
	    notes.clear();
	    note_state.GetNotes(notes);

	    std::ostringstream ss;
	    for (auto n : notes) {
	      ss << chordless::NoteName::Name(n, false) << " ";
	    }
	    this->setText(QString(ss.str().c_str()));
	  } else {
	    std::this_thread::sleep_for(50ms);
	  }
	}
      });
    }

    void ChordLabel::Teardown() {
      read_input_.store(false);
      read_fut_.wait();
    }
  }
}
