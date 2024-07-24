#include "chord_observer.h"

#include "chord_matcher_config_factory.h"
#include "../note/note_state.h"
#include "../ui/mock/mock_text_setter.h"

#include <memory>
#include <gtest/gtest.h>

class ChordObserverTest : public testing::Test {
public:
  ChordObserverTest() : observer(note_state, text_setter) {}

protected:
  chordless::chord::ChordMatcherConfigFactory config_factory;
  
  chordless::note::NoteState note_state;
  chordless::ui::MockTextSetter text_setter;
  chordless::chord::ChordObserver observer;
};

TEST_F(ChordObserverTest, ObserveNothing) {
  observer.Observe();
  EXPECT_TRUE(text_setter.text_.empty());
}

TEST_F(ChordObserverTest, ObserveMajorWithNoMatchers) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);
  observer.Observe();
  EXPECT_TRUE(text_setter.text_.empty());
}

TEST_F(ChordObserverTest, ObserveMajorWithNullMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  observer.AddMatcher(std::move(matcher));
  observer.Observe();
  EXPECT_TRUE(text_setter.text_.empty());
}

TEST_F(ChordObserverTest, ObserveMajorWithMajorMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.Observe();

  const std::string expected("C ");
  EXPECT_EQ(expected, text_setter.text_);
}
