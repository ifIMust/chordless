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
  ASSERT_EQ(std::string("B♭"), namer.Name(0x2e, false));
}
