#include "note_event.h"
#include "note_state.h"
#include "alsa/alsa_input.h"
#include <iostream>
#include <unistd.h>

constexpr auto buffer_size {64};
constexpr auto sleep_duration {1};

int main() {
  chordless::NoteState note_state;
  
  chordless::alsa::AlsaInput input;
  if (!input.IsValid()) {
    std::cout << "Failed to open ALSA sequencer/port" << std::endl;
    exit(EXIT_FAILURE);
  }

  chordless::NoteEvent event;
  
  while (true) {
    auto had_event = input.Read(event);
    if (had_event) {
      std::cout << "Note " << std::hex << static_cast<int>(event.note_)
		<< " Vel " << static_cast<int>(event.velocity_) << std::endl;
    }
  }
  
  return 0;
}
