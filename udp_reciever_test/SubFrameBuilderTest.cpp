#include <gtest/gtest.h>
#include "SubFrameBuilder.h"

namespace sub_data_builder_test {
  using udp_reciever::SubFrameBuilder;
  using udp_reciever::SubFrame;

  class SubFrameBuilderTest : public ::testing::Test {
  protected:
    SubFrameBuilderTest()
      : os(&buffer, QIODevice::WriteOnly), is(&buffer, QIODevice::ReadOnly)
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    protected:
      SubFrameBuilder builder;
      QByteArray buffer;
      QDataStream os;
      QDataStream is;
  };

  TEST_F(SubFrameBuilderTest, FirstTest)
  {
    EXPECT_TRUE(true);
  }
}