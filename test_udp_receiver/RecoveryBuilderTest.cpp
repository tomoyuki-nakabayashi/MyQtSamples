/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include "RecoveryBuilder.h"

namespace recovery_builder_test {
using udp_receiver::RecoveryBuilder;
using udp_receiver::FrameBuilderStatus;
using udp_receiver::Frame;

class RecoveryBuilderTest : public ::testing::Test {
protected:
  RecoveryBuilderTest()
    : os_(&buffer_, QIODevice::WriteOnly)
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
    RecoveryBuilder builder_;
    QByteArray buffer_;
    QDataStream os_;
};

TEST_F(RecoveryBuilderTest, TestContainsQByteArray) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << "this is a test string" << expect;

  EXPECT_TRUE(buffer_.contains(QByteArray::fromHex("01234567")));
}

TEST_F(RecoveryBuilderTest, TestIndexOfQByteArray) {
  Frame invalid(0x76543210, 4, QByteArray::fromHex("01020304"));
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << invalid << expect;

  EXPECT_EQ(12, buffer_.indexOf(QByteArray::fromHex("01234567")));
}

TEST_F(RecoveryBuilderTest, ABSTRACT_USE) {
  Frame invalid(0x76543210, 4, QByteArray::fromHex("01020304"));
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << invalid << expect;

  QVariant v;
  QObject::connect(&builder_, &RecoveryBuilder::FrameConstructed,
    [&](QVariant frame){v = frame;});
//  auto frame = v.value<QSharedPointer<Frame>>().data();
  auto status = builder_.Build(buffer_);
  auto result = builder_.LastResult();

//  EXPECT_EQ(expect, *frame);
  EXPECT_EQ(FrameBuilderStatus::READY, status);
  EXPECT_EQ(24, result.size);
}
}  // namespace recovery_builder_test