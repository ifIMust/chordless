#pragma once

#include <bitset>
#include <vector>

constexpr auto kNumNotes = 128;

namespace chordless {
  namespace note {
    class NoteState {
    public:
      // Note On/Off MIDI:
      // Status:   0x9Z (On) 0x8Z (Off) where Z is channel
      // Data:     0x00 to 0x7F for the note number. 0x3C is middle C.
      // Velocity: 0x00 to 0x7f. If 0, treat as a Note Off.

      // note is a value 0-128.
      void NoteOn(unsigned char note);
      void NoteOff(unsigned char note);

      // Number of notes that are "On". Can be 0-128.
      std::size_t NumNotesOn() const noexcept;

      void GetNotes(std::vector<unsigned char> &notes);
    
    private:
      std::bitset<kNumNotes> notes_;
    };
  }
}
