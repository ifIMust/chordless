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

TEST_F(NoteNameTest, NameD) {
  ASSERT_EQ(std::string("D"), namer.Name(0x3e));  // MIDI note 62 (62 % 12 = 2)
}

TEST_F(NoteNameTest, NameE) {
  ASSERT_EQ(std::string("E"), namer.Name(0x40));  // MIDI note 64 (64 % 12 = 4)
}

TEST_F(NoteNameTest, NameF) {
  ASSERT_EQ(std::string("F"), namer.Name(0x41));  // MIDI note 65 (65 % 12 = 5)
}

TEST_F(NoteNameTest, NameG) {
  ASSERT_EQ(std::string("G"), namer.Name(0x43));  // MIDI note 67 (67 % 12 = 7)
}

TEST_F(NoteNameTest, NameCSharp) {
  namer.SetSharp(true);
  ASSERT_EQ(std::string("C♯"), namer.Name(0x3d));  // MIDI note 61 (61 % 12 = 1)
}

TEST_F(NoteNameTest, NameDFlat) {
  namer.SetSharp(false);
  ASSERT_EQ(std::string("D♭"), namer.Name(0x3d));  // MIDI note 61 (61 % 12 = 1)
}

TEST_F(NoteNameTest, NameDSharp) {
  namer.SetSharp(true);
  ASSERT_EQ(std::string("D♯"), namer.Name(0x3f));  // MIDI note 63 (63 % 12 = 3)
}

TEST_F(NoteNameTest, NameEFlat) {
  namer.SetSharp(false);
  ASSERT_EQ(std::string("E♭"), namer.Name(0x3f));  // MIDI note 63 (63 % 12 = 3)
}

TEST_F(NoteNameTest, NameGSharp) {
  namer.SetSharp(true);
  ASSERT_EQ(std::string("G♯"), namer.Name(0x44));  // MIDI note 68 (68 % 12 = 8)
}

TEST_F(NoteNameTest, NameAFlat) {
  namer.SetSharp(false);
  ASSERT_EQ(std::string("A♭"), namer.Name(0x44));  // MIDI note 68 (68 % 12 = 8)
}
