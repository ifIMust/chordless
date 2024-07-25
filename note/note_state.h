#pragma once

#include "note_constant.h"

#include <bitset>
#include <vector>

namespace chordless::note {
  class NoteState {
  public:
    // note is a value 0-127.
    void NoteOn(unsigned char note);
    void NoteOff(unsigned char note);

    // Number of notes that are "On". Can be 0-127.
    std::size_t NumNotesOn() const noexcept;

    // Write the notes that are On as numeric values into the vector
    void GetNotes(std::vector<unsigned char> &notes) const;

    // Access the internal bitset. Make a copy if using during application runtime.
    const std::bitset<kNumNotes>& GetBits() const noexcept;
      
  private:
    std::bitset<kNumNotes> notes_;
  };
}
