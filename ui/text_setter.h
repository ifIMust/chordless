#pragma once

#include <string>

namespace chordless {
  namespace ui {
    class TextSetter {
    public:
      virtual void SetText(const std::string &) = 0;
    };
  }
}
