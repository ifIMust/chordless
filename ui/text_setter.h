#pragma once

#include <string>

namespace chordless::ui {
  class TextSetter {
  public:
    virtual void SetText(const std::string &) = 0;
  };
}
