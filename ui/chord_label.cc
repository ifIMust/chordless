#include "chord_label.h"

namespace chordless {
  namespace ui {
    ChordLabel::ChordLabel(QWidget *parent) :
      QLabel(parent) {
      setText("Play to begin");
    }

    void ChordLabel::SetText(const std::string &text) {
      this->setText(QString(text.c_str()));
    }
  }
}
