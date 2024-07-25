#include "chord_observer.h"

#include "chord_matcher_config_factory.h"
#include "../note/note_state.h"

#include <QSignalSpy>

#include <gtest/gtest.h>

#include <memory>

class ChordObserverTest : public testing::Test {
public:
  ChordObserverTest() :
    observer(note_state),
    spy(&observer, SIGNAL(textChanged(const QString&)))
  {}

protected:
  chordless::chord::ChordMatcherConfigFactory config_factory;
  
  chordless::note::NoteState note_state;
  chordless::chord::ChordObserver observer;
  QSignalSpy spy;
};

TEST_F(ChordObserverTest, ObserveNothing) {
  observer.Observe();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(0, arguments.at(0).toString().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithNoMatchers) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);
  observer.Observe();
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(0, arguments.at(0).toString().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithNullMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  observer.AddMatcher(std::move(matcher));
  observer.Observe();

  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(0, arguments.at(0).toString().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithMajorMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.Observe();

  const QString expected("C ");
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(expected, arguments.at(0).toString());
}

TEST_F(ChordObserverTest, ObserveMinorWithMinorMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(3);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.Observe();

  const QString expected("C\u2098 ");
  ASSERT_EQ(1, spy.count());
  QList<QVariant> arguments = spy.takeFirst();
  EXPECT_EQ(expected, arguments.at(0).toString());
}
