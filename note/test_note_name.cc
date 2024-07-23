#include "note_name.h"

#include <gtest/gtest.h>
#include <string>

TEST(NoteNameTest, NameMiddleC) {
  ASSERT_EQ(std::string("C"), chordless::note::NoteName::Name(0x3c));
}

TEST(NoteNameTest, NameBassC) {
  ASSERT_EQ(std::string("C"), chordless::note::NoteName::Name(0x30));
}

TEST(NoteNameTest, NameSubA) {
  ASSERT_EQ(std::string("A"), chordless::note::NoteName::Name(0x15));
}

TEST(NoteNameTest, NameZero) {
  ASSERT_EQ(std::string("C"), chordless::note::NoteName::Name(0));
}

TEST(NoteNameTest, NameLowA) {
  ASSERT_EQ(std::string("A"), chordless::note::NoteName::Name(0x2d));
}

TEST(NoteNameTest, NameLowASh) {
  ASSERT_EQ(std::string("A♯"), chordless::note::NoteName::Name(0x2e));
}

TEST(NoteNameTest, NameLowBFl) {
  ASSERT_EQ(std::string("B♭"), chordless::note::NoteName::Name(0x2e, false));
}
