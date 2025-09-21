#include "scientific_note_namer.h"

namespace chordless::note {
  std::string ScientificNoteNamer::OctaveToSubscript(int octave) noexcept {
    std::string result;

    if (octave < 0) {
      result.append("\u208B");  // subscript minus
      octave = -octave;
    }

    if (octave == 0) {
      result.append("\u2080");  // subscript 0
    } else {
      std::string digits;
      while (octave > 0) {
        digits = static_cast<char>('0' + (octave % 10)) + digits;
        octave /= 10;
      }

      for (char digit : digits) {
        // Convert '0'-'9' to Unicode subscript characters \u2080-\u2089
        switch (digit) {
          case '0': result.append("\u2080"); break;
          case '1': result.append("\u2081"); break;
          case '2': result.append("\u2082"); break;
          case '3': result.append("\u2083"); break;
          case '4': result.append("\u2084"); break;
          case '5': result.append("\u2085"); break;
          case '6': result.append("\u2086"); break;
          case '7': result.append("\u2087"); break;
          case '8': result.append("\u2088"); break;
          case '9': result.append("\u2089"); break;
        }
      }
    }

    return result;
  }

  std::string ScientificNoteNamer::Name(unsigned char note, bool sharp) noexcept {
    const auto octave = static_cast<int>(note / 12) - 1;
    auto name = base_namer_.Name(note, sharp);
    name.append(OctaveToSubscript(octave));
    return name;
  }

  void ScientificNoteNamer::SetSharp(bool sharp) noexcept {
    base_namer_.SetSharp(sharp);
  }

  bool ScientificNoteNamer::GetSharp() const noexcept {
    return base_namer_.GetSharp();
  }
}
