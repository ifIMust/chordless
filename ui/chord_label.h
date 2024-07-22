#pragma once

#include "text_setter.h"

#include <QLabel>

#include <future>
#include <string>

namespace chordless {
  class NoteInput;
  
  namespace ui {
    class ChordLabel : public QLabel, public TextSetter {
      Q_OBJECT

    public:
      explicit ChordLabel(QWidget *parent);

      void SetText(const std::string &);
    };
  }
}

