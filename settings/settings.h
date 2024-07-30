#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

#include <string>

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool sharp READ sharp WRITE setSharp NOTIFY sharpChanged)

  public:
    int ReadConfiguration(int argc, char **argv);

    const std::string& ChordsFile() const noexcept;
    
    bool sharp() const noexcept;
    void setSharp(bool sharp) noexcept;
	       
  signals:
    void sharpChanged(bool);
      
  private:
    bool sharp_ {true};
    std::string chords_file_;
  };
}
