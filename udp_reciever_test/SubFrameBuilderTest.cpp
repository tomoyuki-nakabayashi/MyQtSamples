/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include "SubFrameBuilder.h"

namespace sub_data_builder_test {
using udp_reciever::SubFrameBuilder;
using udp_reciever::Frame;
using udp_reciever::FrameBuilderStatus;

class SubFrameBuilderTest : public ::testing::Test {
protected:
  SubFrameBuilderTest()
    : os_(&buffer_, QIODevice::WriteOnly), is_(&buffer_, QIODevice::ReadOnly)
  {
  }

  virtual void SetUp()
  {
    qRegisterMetaType<QSharedPointer<Frame>>();
  }

  virtual void TearDown()
  {
  }
  protected:
    SubFrameBuilder builder_;
    QByteArray buffer_;
    QDataStream os_;
    QDataStream is_;
};

TEST_F(SubFrameBuilderTest, GetInstanceByQDataStream) {
  os_ << 1 << 0x4 << 0x01020304;
  EXPECT_EQ(12, buffer_.size());
  auto actual = builder_.Build(is_, 12);
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}

TEST_F(SubFrameBuilderTest, CreateBuildAndGet) {
  Frame expect(1, 2, QByteArray::fromHex("0102"));
  os_ << expect;
  builder_.Build(is_, buffer_.size());
  auto actual = builder_.GetFrame();

  EXPECT_EQ(expect.GetFrameSize(), actual->GetFrameSize());
  EXPECT_EQ(expect, *actual);
}

TEST_F(SubFrameBuilderTest, FinishedWhenTwoFrameBuilt) {
  Frame expect(1, 2, QByteArray::fromHex("0102"));
  os_ << expect << expect;
  EXPECT_FALSE(builder_.Finished());
  builder_.Build(is_, buffer_.size());
  EXPECT_FALSE(builder_.Finished());
  builder_.Build(is_, buffer_.size() - expect.GetFrameSize());

  EXPECT_TRUE(builder_.Finished());
}
}  // sub_data_builder_test