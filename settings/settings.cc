#include "settings.h"

#include <QQuickItem>

#include <iostream>

namespace chordless::settings {
  void Settings::ConnectToGui(QQuickItem &item) {
    auto sharpCombo = item.findChild<QQuickItem*>("sharpsComboBox");
    if (sharpCombo == nullptr) {
      std::cout << "failed to find sharpsComboBox\n";
    } else {
      sharpCombo->setProperty("currentIndex",(sharp_ ? 0 : 1));
      connect(sharpCombo, SIGNAL(activated(int)), this, SLOT(SetSharp(int)));
      emit SharpSettingChanged(sharp_);
    }

    auto octave = item.findChild<QQuickItem*>("octaveCheckBox", Qt::FindChildrenRecursively);
    if (octave == nullptr) {
      std::cout << "can't find it\n";
    } else {
      std::cout << "found it\n";
    }
  }

  void Settings::SetSharp(int index) {
    sharp_ = (index == 0);
    emit SharpSettingChanged(sharp_);
  }
}
