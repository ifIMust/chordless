#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool sharp READ sharp WRITE setSharp NOTIFY sharpChanged)

  public:
    bool sharp() const noexcept;
    void setSharp(bool sharp) noexcept;
	       
  signals:
    void sharpChanged(bool);
      
  private:
    int sharp_combo_index_ {0};
    bool sharp_ {true};
  };
}
