#include <gtest/gtest.h>
#include "SubDataBuilder.h"

namespace sub_data_builder_test {
  using udp_reciever::SubDataBuilder;
  using udp_reciever::SubData;

  class SubDataBuilderTest : public ::testing::Test {
  protected:
    SubDataBuilderTest()
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
      SubDataBuilder builder;
      QByteArray buffer;
      QDataStream os;
      QDataStream is;
  };

  TEST_F(SubDataBuilderTest, FirstTest)
  {
    EXPECT_TRUE(true);
  }
}