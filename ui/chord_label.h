#pragma once

#include <QLabel>

#include <future>

namespace chordless {
  namespace alsa {
    class AlsaInput;
  }
  
  namespace ui {
    class ChordLabel : public QLabel {
      Q_OBJECT

    public:
      explicit ChordLabel(QWidget *parent, chordless::alsa::AlsaInput &alsa_input);

    public slots:
      void Teardown();

    private:
      std::future<void> read_fut_;
      chordless::alsa::AlsaInput &alsa_input_;
      std::atomic<bool> read_input_;
    };
  }
}

