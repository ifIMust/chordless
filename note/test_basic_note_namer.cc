#include "basic_note_namer.h"

#include <gtest/gtest.h>
#include <string>

class NoteNameTest : public testing::Test {
protected:
  chordless::note::BasicNoteNamer namer;
};

TEST_F(NoteNameTest, NameMiddleC) {
  ASSERT_EQ(std::string("C"), namer.Name(0x3c));
}

TEST_F(NoteNameTest, NameBassC) {
  ASSERT_EQ(std::string("C"), namer.Name(0x30));
}

TEST_F(NoteNameTest, NameSubA) {
  ASSERT_EQ(std::string("A"), namer.Name(0x15));
}

TEST_F(NoteNameTest, NameZero) {
  ASSERT_EQ(std::string("C"), namer.Name(0));
}

TEST_F(NoteNameTest, NameLowA) {
  ASSERT_EQ(std::string("A"), namer.Name(0x2d));
}

TEST_F(NoteNameTest, NameLowASh) {
  ASSERT_EQ(std::string("A♯"), namer.Name(0x2e));
}

TEST_F(NoteNameTest, NameLowBFl) {
  namer.SetSharp(false);
  ASSERT_EQ(std::string("B♭"), namer.Name(0x2e, false));
}

TEST_F(NoteNameTest, NameB) {
  ASSERT_EQ(std::string("B"), namer.Name(0x47));  // MIDI note 71 (71 % 12 = 11)
}

TEST_F(NoteNameTest, NameFSharp) {
  namer.SetSharp(true);
  ASSERT_EQ(std::string("F♯"), namer.Name(0x42));  // MIDI note 66 (66 % 12 = 6)
}

TEST_F(NoteNameTest, NameGFlat) {
  namer.SetSharp(false);
  ASSERT_EQ(std::string("G♭"), namer.Name(0x42));  // MIDI note 66 (66 % 12 = 6)
}
