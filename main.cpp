#include "note_event.h"
#include "note_name.h"
#include "note_state.h"
#include "alsa/alsa_input.h"
#include <iostream>
#include <vector>

constexpr auto buffer_size {64};

int main() {
  chordless::NoteState note_state;
  
  chordless::alsa::AlsaInput input;
  if (!input.IsValid()) {
    std::cout << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  chordless::NoteEvent event;
  std::vector<unsigned char> notes;
  
  while (true) {
    auto had_event = input.Read(event);
    if (had_event) {
      auto &note = event.note_;
      event.on_ ? note_state.NoteOn(note) : note_state.NoteOff(note);
      notes.clear();
      note_state.GetNotes(notes);
      for (auto n : notes) {
	auto note_str(chordless::NoteName::Name(n, false));
	std::cout << note_str;
	if (note_str.size() == 1) {
	  std::cout << ' ';
	}
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
