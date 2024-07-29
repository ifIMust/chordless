#include "settings.h"

#include <QQuickItem>

#include <iostream>

namespace chordless::settings {
  void Settings::ConnectToGui(QQuickItem &) {
  }

  bool Settings::sharp() const noexcept {
    std::cout << "sharp\n";
    return sharp_;
  }

  void Settings::setSharp(bool sharp) noexcept {
    std::cout << "setSharp\n";
    sharp_ = sharp;
    emit sharpChanged();
    emit SharpSettingChanged(sharp_);
  }
}
