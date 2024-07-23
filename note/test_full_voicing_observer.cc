#include "full_voicing_observer.h"

#include "note_state.h"
#include "../ui/text_setter.h"

#include <gtest/gtest.h>
#include <string>

class MockTextSetter : public chordless::ui::TextSetter {
public:
  void SetText(const std::string &text) override { text_ = text; }
  std::string text_;
};

TEST(FullVoicingObserverTest, Empty) {
  MockTextSetter text_setter;
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver o(note_state,text_setter);
  o.Observe();
  EXPECT_TRUE(text_setter.text_.empty());
}

TEST(FullVoicingObserverTest, OneNote) {
  MockTextSetter text_setter;
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver o(note_state,text_setter);
  std::string expected("C ");
  note_state.NoteOn(0);
  o.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}

TEST(FullVoicingObserverTest, ThreeNote) {
  MockTextSetter text_setter;
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver o(note_state,text_setter);
  std::string expected("C E G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  o.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}


TEST(FullVoicingObserverTest, Reobserve) {
  MockTextSetter text_setter;
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver o(note_state,text_setter);
  std::string expected("C G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  o.Observe();

  note_state.NoteOff(16);
  o.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}
