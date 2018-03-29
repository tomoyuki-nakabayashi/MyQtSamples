/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include "Frame.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace frame_builder_interface_test {
using udp_receiver::BaseFrameBuilder;
using udp_receiver::FrameBuilder;
using udp_receiver::SubFrameBuilder;
using udp_receiver::Frame;
using udp_receiver::FrameBuilderStatus;

class FrameBuilderInterfaceTest : public ::testing::Test {
protected:
  FrameBuilderInterfaceTest()
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
    BaseFrameBuilder *builder_;
    FrameBuilder frame_builder_;
    SubFrameBuilder sub_frame_builder_;
    QByteArray buffer_;
    QDataStream os_;
};

TEST_F(FrameBuilderInterfaceTest, BuildFrameFromInterface) {
  os_ << 0x01234567 << 0x4 << 0x01020304;
  builder_ = &frame_builder_;
  auto actual = builder_->Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, actual.status);
}

TEST_F(FrameBuilderInterfaceTest, BuildSubFrameFromInterface) {
  os_ << 0x01234567 << 0x4 << 0x01020304;
  builder_ = &sub_frame_builder_;
  auto actual = builder_->Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, actual.status);
}

TEST_F(FrameBuilderInterfaceTest, SwitchBuilder) {
  os_ << 0x01234567 << 0x4 << 0x01020304;
  builder_ = &frame_builder_;
  auto actual1 = builder_->Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, actual1.status);

  os_ << 0x01234567 << 0x4 << 0x01020304;
  builder_ = &sub_frame_builder_;
  auto actual2 = builder_->Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, actual2.status);
}


}  // namespace frame_builder_interface_test