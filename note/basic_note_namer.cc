#include "basic_note_namer.h"

namespace chordless::note {
  std::string BasicNoteNamer::Name(unsigned char note, bool) noexcept {
    auto pitch_class = static_cast<int>(note) % 12;
    switch (pitch_class) {
    case 0:
      return std::string("C");
    case 1:
      return sharp_ ? std::string("C♯") : std::string("D♭");
    case 2:
      return std::string("D");
    case 3:
      return sharp_ ? std::string("D♯") : std::string("E♭");
    case 4:
      return std::string("E");
    case 5:
      return std::string("F");
    case 6:
      return sharp_ ? std::string("F♯") : std::string("G♭");
    case 7:
      return std::string("G");
    case 8:
      return sharp_ ? std::string("G♯") : std::string("A♭");
    case 9:
      return std::string("A");
    case 10:
      return sharp_ ? std::string("A♯") : std::string("B♭");
    case 11:
    default:
      return std::string("B");
    }
  }

  void BasicNoteNamer::SetSharp(bool sharp) noexcept {
    sharp_ = sharp;
  }

  bool BasicNoteNamer::GetSharp() const noexcept {
    return sharp_;
  }
}
