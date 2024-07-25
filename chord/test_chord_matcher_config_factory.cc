#include "chord_matcher_config_factory.h"

#include "chord_matcher_config.h"

#include <gtest/gtest.h>

class ChordMatcherConfigFactoryTest : public ::testing::Test {
protected:
  chordless::chord::ChordMatcherConfigFactory factory;
};

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadName) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  EXPECT_EQ(c->name, "Major Triad");
}

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadSuffix) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  EXPECT_EQ(c->suffix, "");
}

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadWidth) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  ASSERT_EQ(c->patterns.size(), 1);
  EXPECT_EQ(c->patterns[0].pattern_width, 8);
}

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadPatternBits) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  ASSERT_EQ(c->patterns.size(), 1);
  EXPECT_TRUE(c->patterns[0].pattern.test(0));
  EXPECT_TRUE(c->patterns[0].pattern.test(4));
  EXPECT_TRUE(c->patterns[0].pattern.test(7));
}

TEST_F(ChordMatcherConfigFactoryTest, MinorTriadName) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD);
  EXPECT_EQ(c->name, "Minor Triad");
}

TEST_F(ChordMatcherConfigFactoryTest, MinorTriadWidth) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD);
  EXPECT_EQ(c->patterns[0].pattern_width, 8);
}

TEST_F(ChordMatcherConfigFactoryTest, MinorTriadPatternBits) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD);
  ASSERT_EQ(c->patterns.size(), 1);
  EXPECT_TRUE(c->patterns[0].pattern.test(0));
  EXPECT_TRUE(c->patterns[0].pattern.test(3));
  EXPECT_TRUE(c->patterns[0].pattern.test(7));
}

TEST_F(ChordMatcherConfigFactoryTest, MinorTriadSuffix) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MINOR_TRIAD);
  EXPECT_EQ(c->suffix, "\u2098");
}
