/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>

namespace recovery_builder_test {
using udp_receiver::Frame;
using udp_receiver::FrameBuilderStatus;

class RecoveryBuilderTest : public ::testing::Test {
protected:
  RecoveryBuilderTest()
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
    QByteArray buffer_;
    QDataStream os_;
    QDataStream is_;
};

TEST_F(FrameBuilderTest, TestQByteArray) {
}