#include "full_voicing_observer.h"

#include "note_state.h"
#include "../ui/mock/mock_text_setter.h"

#include <gtest/gtest.h>
#include <string>

class FullVoicingObserverTest : public testing::Test {
public:
  FullVoicingObserverTest() : observer(note_state, text_setter) {}
  
protected:
  chordless::ui::MockTextSetter text_setter;
  chordless::note::NoteState note_state;
  chordless::note::FullVoicingObserver observer;
};

TEST_F(FullVoicingObserverTest, Empty) {
  observer.Observe();
  EXPECT_TRUE(text_setter.text_.empty());
}

TEST_F(FullVoicingObserverTest, OneNote) {
  std::string expected("C ");
  note_state.NoteOn(0);
  observer.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}

TEST_F(FullVoicingObserverTest, ThreeNote) {
  std::string expected("C E G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}

TEST_F(FullVoicingObserverTest, Reobserve) {
  std::string expected("C G ");
  note_state.NoteOn(0);
  note_state.NoteOn(16);
  note_state.NoteOn(31);
  observer.Observe();

  note_state.NoteOff(16);
  observer.Observe();
  EXPECT_EQ(expected, text_setter.text_);
}
