#include "scientific_note_namer.h"

namespace chordless::note {
  std::string ScientificNoteNamer::Name(unsigned char note, bool sharp) noexcept {
    const auto octave = static_cast<int>(note / 12) - 1;
    auto name = base_namer_.Name(note, sharp);
    switch (octave) {
    case -1:
      name.append("\u208B\u2081");
      break;
    case 0:
      name.append("\u2080");
      break;
    case 1:
      name.append("\u2081");
      break;
    case 2:
      name.append("\u2082");
      break;
    case 3:
      name.append("\u2083");
      break;
    case 4:
      name.append("\u2084");
      break;
    case 5:
      name.append("\u2085");
      break;
    case 6:
      name.append("\u2086");
      break;
    case 7:
      name.append("\u2087");
      break;
    case 8:
      name.append("\u2088");
      break;
    case 9:
      name.append("\u2089");
      break;
    default:
      name.append("?");
    }
    return name;
  }
}
