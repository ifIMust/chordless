#include "settings.h"

namespace chordless::settings {
  bool Settings::sharp() const noexcept {
    return sharp_;
  }

  void Settings::setSharp(bool sharp) noexcept {
    sharp_ = sharp;
    emit sharpChanged(sharp_);
  }
}
