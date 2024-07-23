#include "note_name.h"

namespace chordless {
  namespace note {
    std::string NoteName::Name(unsigned char note, bool sharp) {
      auto pitch_class = static_cast<int>(note) % 12;
      switch (pitch_class) {
      case 0:
	return std::string("C");
      case 1:
	return sharp ? std::string("C♯") : std::string("D♭");
      case 2:
	return std::string("D");
      case 3:
	return sharp ? std::string("D♯") : std::string("E♭");
      case 4:
	return std::string("E");
      case 5:
	return std::string("F");
      case 6:
	return sharp ? std::string("F♯") : std::string("G♭");
      case 7:
	return std::string("G");
      case 8:
	return sharp ? std::string("G♯") : std::string("A♭");
      case 9:
	return std::string("A");
      case 10:
	return sharp ? std::string("A♯") : std::string("B♭");
      case 11:
	return std::string("B");
      };
      return std::string("Impossible pitch");
    }
  }
}
