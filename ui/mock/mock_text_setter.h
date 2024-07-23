#pragma once

#include "../text_setter.h"

namespace chordless::ui {
  class MockTextSetter : public chordless::ui::TextSetter {
  public:
    void SetText(const std::string &text) override { text_ = text; }
    std::string text_;
  };
}
