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
  auto chords = cm.Match(ns);
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
  EXPECT_EQ(chords[0].name, "C");
}

TEST_F(MajorTriadTest, DMajorTriadMatchRooted) {
  ns.NoteOn(2);
  ns.NoteOn(6);
  ns.NoteOn(9);
  auto notes = ns.GetBits();
  notes >>= 2;
  auto chords = cm.MatchRooted(notes, 2, notes.count());
  ASSERT_FALSE(chords.empty());
  EXPECT_EQ(chords[0].name, "D");
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

