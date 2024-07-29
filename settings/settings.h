#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

class QQuickItem;

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT

  public:
    void ConnectToGui(QQuickItem &view);

  public slots:
      void SetSharp(int index);

  signals:
      void SharpSettingChanged(bool);
      
  private:
      bool sharp_ {true};
      
  };
}
