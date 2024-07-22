#include "chord_label.h"
#include "../note_input.h"
#include "../note_name.h"
#include "../note_state.h"
#include "../note/note_event.h"

#include <chrono>
#include <sstream>
#include <thread>

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
