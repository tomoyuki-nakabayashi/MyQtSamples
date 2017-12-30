#include <gtest/gtest.h>
#include "UdpReciever.h"

namespace udp_reciever_test {
  using namespace testing;
  using namespace udp_reciever;

  class UdpRecieverTest : public ::testing::Test {
  protected:
    virtual void SetUp()
    {
    // Do nothing
    }

    virtual void TearDown()
    {

    }
  };

  TEST_F(UdpRecieverTest, FirstTest)
  {
    EXPECT_TRUE(true);
  }

}