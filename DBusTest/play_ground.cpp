/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>

namespace playground {

class PlayGround : public ::testing::Test {
protected:
  PlayGround()
  {
  }

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(PlayGround, FirstTest) {
  EXPECT_TRUE(true);
}
}  // namespace playground