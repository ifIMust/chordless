#include "settings.h"

#include <QQuickItem>

#include <iostream>

namespace chordless::settings {
  void Settings::ConnectToGui(QQuickItem &) {
  }

  int Settings::SharpComboIndex() const noexcept {
    std::cout << "SharpComboIndex\n";
    return sharp_combo_index_;
  }

  void Settings::SetSharpComboIndex(int idx) noexcept {
    std::cout << "SetSharpComboIndex\n";
    sharp_combo_index_ = idx;
    sharp_ = (idx == 0);
    emit SharpComboIndexChanged();
    emit SharpSettingChanged(sharp_);
  }
  
  void Settings::SetSharp(int index) {
    sharp_ = (index == 0);
    emit SharpSettingChanged(sharp_);
  }
}
