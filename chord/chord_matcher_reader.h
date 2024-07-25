#pragma once

#include <string>

namespace chordless::chord {
  class ChordObserver;
  
  void configureChordObserver(ChordObserver&, const std::string &file_name);
}
