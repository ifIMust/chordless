#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

#include <string>

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool sharp READ Sharp WRITE SetSharp NOTIFY SharpChanged)

  public:
    int ReadConfiguration(int argc, char **argv);

    const std::string& ChordsFile() const noexcept;

    bool Sharp() const noexcept;
    void SetSharp(bool sharp) noexcept;

  signals:
    void SharpChanged(bool);
      
  private:
    bool sharp_ {true};
    std::string chords_file_;
  };
}
