#pragma once

#include <bitset>
#include <vector>

namespace chordless {
  namespace note {
    constexpr auto kNumNotes = 128;
    
    class NoteState {
    public:
      // note is a value 0-127.
      void NoteOn(unsigned char note);
      void NoteOff(unsigned char note);

      // Number of notes that are "On". Can be 0-127.
      std::size_t NumNotesOn() const noexcept;

      void GetNotes(std::vector<unsigned char> &notes);

      const std::bitset<kNumNotes>& GetBits() const noexcept;
      
    private:
      std::bitset<kNumNotes> notes_;
    };
  }
}
