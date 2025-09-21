#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

#include <string>

namespace chordless::settings {
  class Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool sharp READ Sharp WRITE SetSharp NOTIFY SharpChanged)
    Q_PROPERTY(bool bestChordOnly READ BestChordOnly WRITE SetBestChordOnly NOTIFY BestChordOnlyChanged)

  public:
    int ReadConfiguration(int argc, char **argv);

    const std::string& ChordsFile() const noexcept;

    bool Sharp() const noexcept;
    void SetSharp(bool sharp) noexcept;

    bool BestChordOnly() const noexcept;
    void SetBestChordOnly(bool best_chord_only) noexcept;

  signals:
    void SharpChanged(bool);
    void BestChordOnlyChanged(bool);
      
  private:
    bool sharp_ {true};
    bool best_chord_only_ {false};
    std::string chords_file_;
  };
}
