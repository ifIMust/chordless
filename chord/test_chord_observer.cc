#include "chord_observer.h"

#include "chord.h"
#include "chord_matcher_config_factory.h"
#include "../note/note_state.h"

#include <QSignalSpy>

#include <gtest/gtest.h>

#include <memory>

class ChordObserverTest : public testing::Test {
public:
  ChordObserverTest() :
    observer(note_state),
    spy(&observer, SIGNAL(textChanged()))
  {}

protected:
  chordless::chord::ChordMatcherConfigFactory config_factory;
  
  chordless::note::NoteState note_state;
  chordless::chord::ChordObserver observer;
  QSignalSpy spy;
};

TEST_F(ChordObserverTest, ObserveNothing) {
  observer.OnNoteChange();
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(0, observer.text().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithNoMatchers) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);
  observer.OnNoteChange();
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(0, observer.text().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithNullMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  observer.AddMatcher(std::move(matcher));
  observer.OnNoteChange();

  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(0, observer.text().size());
}

TEST_F(ChordObserverTest, ObserveMajorWithMajorMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.OnNoteChange();

  const QString expected("C ");
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, ObserveMinorWithMinorMatcher) {
  note_state.NoteOn(0);
  note_state.NoteOn(3);
  note_state.NoteOn(7);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.OnNoteChange();

  const QString expected("C\u2098 ");
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, ObserveMinorWithMinorMatcherExtraC) {
  note_state.NoteOn(0);
  note_state.NoteOn(3);
  note_state.NoteOn(7);
  note_state.NoteOn(12);

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.OnNoteChange();

  const QString expected("C\u2098 ");
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, UniqueNotesCMajTriad) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);
  auto u = chordless::chord::ChordObserver::UniqueNotes(note_state.GetBits());
  EXPECT_EQ(3, u.count());
}

TEST_F(ChordObserverTest, UniqueNotesCMajCadence) {
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);
  note_state.NoteOn(12);
  auto u = chordless::chord::ChordObserver::UniqueNotes(note_state.GetBits());
  EXPECT_EQ(3, u.count());
}

TEST_F(ChordObserverTest, UniqueNotesCMajMassiveCadence) {
  note_state.NoteOn(0);
  note_state.NoteOn(7);
  note_state.NoteOn(12);
  note_state.NoteOn(16);
  note_state.NoteOn(19);
  auto u = chordless::chord::ChordObserver::UniqueNotes(note_state.GetBits());
  EXPECT_EQ(3, u.count());
}

TEST_F(ChordObserverTest, UniqueNotesCMaj7) {
  note_state.NoteOn(0);
  note_state.NoteOn(7);
  note_state.NoteOn(12);
  note_state.NoteOn(16);
  note_state.NoteOn(18);
  auto u = chordless::chord::ChordObserver::UniqueNotes(note_state.GetBits());
  EXPECT_EQ(4, u.count());
}

TEST_F(ChordObserverTest, FindRootNoteWhenLowestNoteIsNotZero) {
  // Tests the bit-shifting logic in OnNoteChange() that finds the root note
  // when the lowest active note is not MIDI note 0
  note_state.NoteOn(2);   // D (root)
  note_state.NoteOn(6);   // F#
  note_state.NoteOn(9);   // A

  auto matcher(std::make_unique<chordless::chord::ChordMatcher>());
  matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  observer.AddMatcher(std::move(matcher));
  observer.OnNoteChange();

  // Should identify D as the root and display "D major"
  const QString expected("D ");
  ASSERT_EQ(1, spy.count());
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, SelectBestChordEmpty) {
  std::vector<chordless::chord::Chord> empty_chords;
  auto best = observer.SelectBestChord(empty_chords);
  EXPECT_EQ(0, best.tonic_note);
  EXPECT_EQ("", best.suffix);
  EXPECT_EQ(0, best.num_notes);
}

TEST_F(ChordObserverTest, SelectBestChordSingle) {
  std::vector<chordless::chord::Chord> chords = {
    {0, "", 3}  // C major triad
  };
  auto best = observer.SelectBestChord(chords);
  EXPECT_EQ(0, best.tonic_note);
  EXPECT_EQ("", best.suffix);
  EXPECT_EQ(3, best.num_notes);
}

TEST_F(ChordObserverTest, SelectBestChordByNoteCount) {
  std::vector<chordless::chord::Chord> chords = {
    {0, "", 3},       // C major triad (3 notes)
    {0, "⁶", 4},      // C6 chord (4 notes)
    {0, "5", 2}       // C5 power chord (2 notes)
  };
  auto best = observer.SelectBestChord(chords);
  EXPECT_EQ(0, best.tonic_note);
  EXPECT_EQ("⁶", best.suffix);
  EXPECT_EQ(4, best.num_notes);
}

TEST_F(ChordObserverTest, SelectBestChordTieBreaker) {
  // When multiple chords have same note count, first one wins
  std::vector<chordless::chord::Chord> chords = {
    {0, "", 3},       // C major triad (3 notes) - first
    {0, "ₘ", 3},      // C minor triad (3 notes) - second
    {0, "sus", 3}     // C sus chord (3 notes) - third
  };
  auto best = observer.SelectBestChord(chords);
  EXPECT_EQ(0, best.tonic_note);
  EXPECT_EQ("", best.suffix);
  EXPECT_EQ(3, best.num_notes);
}

TEST_F(ChordObserverTest, SetBestChordOnlyDefault) {
  // Test that default is false (show all chords)
  note_state.NoteOn(0);
  note_state.NoteOn(4);
  note_state.NoteOn(7);

  // Add two matchers that will both match
  auto major_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  major_matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD));
  observer.AddMatcher(std::move(major_matcher));

  auto minor_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  minor_matcher->SetConfig(config_factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD));
  observer.AddMatcher(std::move(minor_matcher));

  observer.OnNoteChange();

  // Should show only the major chord since minor won't match C-E-G
  const QString expected("C ");
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, SetBestChordOnlyEnabled) {
  observer.SetBestChordOnly(true);

  note_state.NoteOn(0);  // C
  note_state.NoteOn(4);  // E
  note_state.NoteOn(7);  // G
  note_state.NoteOn(9);  // A (makes it C6)

  // Create custom configs to simulate C major and C6
  auto major_config = std::make_unique<chordless::chord::ChordMatcherConfig>();
  major_config->name = "Major";
  major_config->suffix = "";
  chordless::chord::ChordPattern major_pattern;
  major_pattern.num_notes = 3;
  major_pattern.pattern.set(0);  // C
  major_pattern.pattern.set(4);  // E
  major_pattern.pattern.set(7);  // G
  major_config->patterns.push_back(std::move(major_pattern));

  auto c6_config = std::make_unique<chordless::chord::ChordMatcherConfig>();
  c6_config->name = "Major 6th";
  c6_config->suffix = "⁶";
  chordless::chord::ChordPattern c6_pattern;
  c6_pattern.num_notes = 4;
  c6_pattern.pattern.set(0);  // C
  c6_pattern.pattern.set(4);  // E
  c6_pattern.pattern.set(7);  // G
  c6_pattern.pattern.set(9);  // A
  c6_config->patterns.push_back(std::move(c6_pattern));

  auto major_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  major_matcher->SetConfig(std::move(major_config));
  observer.AddMatcher(std::move(major_matcher));

  auto c6_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  c6_matcher->SetConfig(std::move(c6_config));
  observer.AddMatcher(std::move(c6_matcher));

  observer.OnNoteChange();

  // Should show only C6 (4 notes) not C major (3 notes)
  const QString expected("C⁶ ");
  EXPECT_EQ(expected, observer.text());
}

TEST_F(ChordObserverTest, SetBestChordOnlyDisabled) {
  observer.SetBestChordOnly(false);

  note_state.NoteOn(0);  // C
  note_state.NoteOn(4);  // E
  note_state.NoteOn(7);  // G
  note_state.NoteOn(9);  // A (makes it C6)

  // Create the same configs as above
  auto major_config = std::make_unique<chordless::chord::ChordMatcherConfig>();
  major_config->name = "Major";
  major_config->suffix = "";
  chordless::chord::ChordPattern major_pattern;
  major_pattern.num_notes = 3;
  major_pattern.pattern.set(0);
  major_pattern.pattern.set(4);
  major_pattern.pattern.set(7);
  major_config->patterns.push_back(std::move(major_pattern));

  auto c6_config = std::make_unique<chordless::chord::ChordMatcherConfig>();
  c6_config->name = "Major 6th";
  c6_config->suffix = "⁶";
  chordless::chord::ChordPattern c6_pattern;
  c6_pattern.num_notes = 4;
  c6_pattern.pattern.set(0);
  c6_pattern.pattern.set(4);
  c6_pattern.pattern.set(7);
  c6_pattern.pattern.set(9);
  c6_config->patterns.push_back(std::move(c6_pattern));

  auto major_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  major_matcher->SetConfig(std::move(major_config));
  observer.AddMatcher(std::move(major_matcher));

  auto c6_matcher(std::make_unique<chordless::chord::ChordMatcher>());
  c6_matcher->SetConfig(std::move(c6_config));
  observer.AddMatcher(std::move(c6_matcher));

  observer.OnNoteChange();

  // Should show both chords
  QString result = observer.text();
  // Debug: print the actual result
  ASSERT_FALSE(result.isEmpty()) << "Result is empty!";
  EXPECT_TRUE(result.contains("C")) << "Result: " << result.toStdString();
  EXPECT_TRUE(result.contains("⁶")) << "Result: " << result.toStdString();
}

