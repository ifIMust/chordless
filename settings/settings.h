#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

class QQuickItem;

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int sharp_combo_index READ SharpComboIndex WRITE SetSharpComboIndex NOTIFY SharpComboIndexChanged)

  public:
    void ConnectToGui(QQuickItem &view);

    int SharpComboIndex() const noexcept;
    void SetSharpComboIndex(int idx) noexcept;
	       
  public slots:
    void SetSharp(int index);

  signals:
    void SharpSettingChanged(bool);
    void SharpComboIndexChanged();
      
  private:
    int sharp_combo_index_ {0};
    bool sharp_ {true};
  };
}
