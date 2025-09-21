#pragma once

#include <string>

namespace chordless::chord {
  class ChordObserver;

  void ConfigureChordObserver(ChordObserver&, const std::string &file_name);
}
