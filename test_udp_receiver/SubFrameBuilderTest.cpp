/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include "SubFrameBuilder.h"

namespace sub_data_builder_test {
using udp_receiver::SubFrameBuilder;
using udp_receiver::Frame;
using udp_receiver::FrameBuilderStatus;

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

TEST_F(SubFrameBuilderTest, FrameIsReady) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;
  EXPECT_EQ(12, buffer_.size());
  auto actual = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}

TEST_F(SubFrameBuilderTest, CreateBuildAndGet) {
  Frame expect(Frame::kHeaderMagic, 2, QByteArray::fromHex("0102"));
  QVariant v;
  QObject::connect(&builder_, &SubFrameBuilder::FrameConstructed,
    [&](QVariant frame){v = frame;});
  os_ << expect;
  builder_.Build(is_, buffer_.size());
  auto actual = v.value<QSharedPointer<Frame>>().data();

  EXPECT_EQ(expect.GetFrameSize(), actual->GetFrameSize());
  EXPECT_EQ(expect, *actual);
}
}  // sub_data_builder_test