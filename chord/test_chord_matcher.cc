#include "chord_matcher.h"

#include "chord_matcher_config.h"
#include "chord_matcher_config_factory.h"

#include "../note/note_state.h"

#include <gtest/gtest.h>

class ChordMatcherTest : public ::testing::Test {
protected:
  chordless::chord::ChordMatcher cm;
  chordless::note::NoteState ns;
  chordless::chord::ChordMatcherConfigFactory cf;
};

class MajorTriadTest : public ChordMatcherTest {
public:
  MajorTriadTest() {
    auto config = cf.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
    cm.SetConfig(std::move(config));
  }
};

TEST_F(ChordMatcherTest, NullConfig) {
  auto notes = ns.GetBits();
  auto chords = cm.MatchRooted(notes, 0, notes.count());
  EXPECT_TRUE(chords.empty());
}

TEST_F(MajorTriadTest, MajorTriadEmpty) {
  auto notes = ns.GetBits();
  auto chords = cm.MatchRooted(notes, 0, notes.count());
  EXPECT_TRUE(chords.empty());
}

TEST_F(MajorTriadTest, CMajorTriadMatchRooted) {
  ns.NoteOn(0);
  ns.NoteOn(4);
  ns.NoteOn(7);
  auto notes = ns.GetBits();
  auto chords = cm.MatchRooted(notes, 0, notes.count());
  ASSERT_FALSE(chords.empty());
  EXPECT_EQ(chords[0].tonic_note, 0);
}

TEST_F(MajorTriadTest, DMajorTriadMatchRooted) {
  ns.NoteOn(2);
  ns.NoteOn(6);
  ns.NoteOn(9);
  auto notes = ns.GetBits();
  notes >>= 2;
  auto chords = cm.MatchRooted(notes, 2, notes.count());
  ASSERT_FALSE(chords.empty());
  EXPECT_EQ(chords[0].tonic_note, 2);
}

TEST_F(MajorTriadTest, CMajorTriadExtraNoteMatchRooted) {
  ns.NoteOn(0);
  ns.NoteOn(3);
  ns.NoteOn(4);
  ns.NoteOn(7);
  auto notes = ns.GetBits();
  auto chords = cm.MatchRooted(notes, 0, notes.count());
  ASSERT_TRUE(chords.empty());
}

TEST_F(MajorTriadTest, ChordNumNotesField) {
  // Test that the num_notes field is correctly populated
  ns.NoteOn(0);
  ns.NoteOn(4);
  ns.NoteOn(7);
  auto notes = ns.GetBits();
  auto chords = cm.MatchRooted(notes, 0, notes.count());
  ASSERT_FALSE(chords.empty());
  EXPECT_EQ(3, chords[0].num_notes);
}

TEST_F(ChordMatcherTest, MultiplePatternMatching) {
  // Test a config with multiple patterns of different sizes
  auto config = std::make_unique<chordless::chord::ChordMatcherConfig>();
  config->suffix = "test";

  // Add a 2-note pattern
  chordless::chord::ChordPattern pattern2;
  pattern2.num_notes = 2;
  pattern2.pattern.set(0);
  pattern2.pattern.set(4);
  config->patterns.push_back(pattern2);

  // Add a 3-note pattern
  chordless::chord::ChordPattern pattern3;
  pattern3.num_notes = 3;
  pattern3.pattern.set(0);
  pattern3.pattern.set(4);
  pattern3.pattern.set(7);
  config->patterns.push_back(pattern3);

  cm.SetConfig(std::move(config));

  // Test with 2 notes - should match first pattern
  ns.NoteOn(0);
  ns.NoteOn(4);
  auto notes2 = ns.GetBits();
  auto chords2 = cm.MatchRooted(notes2, 0, notes2.count());
  ASSERT_FALSE(chords2.empty());
  EXPECT_EQ(2, chords2[0].num_notes);

  // Test with 3 notes - should match second pattern
  ns.NoteOn(7);
  auto notes3 = ns.GetBits();
  auto chords3 = cm.MatchRooted(notes3, 0, notes3.count());
  ASSERT_FALSE(chords3.empty());
  EXPECT_EQ(3, chords3[0].num_notes);
}

