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

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadWidth) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  EXPECT_EQ(c->pattern_width, 8);
}

TEST_F(ChordMatcherConfigFactoryTest, MajorTriadPatternBits) {
  auto c = factory.MakeConfig(chordless::chord::ChordType::MAJOR_TRIAD);
  
  EXPECT_TRUE(c->pattern.test(0));
  EXPECT_TRUE(c->pattern.test(4));
  EXPECT_TRUE(c->pattern.test(7));
}
