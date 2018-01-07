#include <gtest/gtest.h>
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace frame_builder_interface_test {
using udp_reciever::BaseFrameBuilder;
using udp_reciever::FrameBuilder;
using udp_reciever::SubFrameBuilder;
using udp_reciever::Frame;
using udp_reciever::FrameBuilderStatus;

class FrameBuilderInterfaceTest : public ::testing::Test {
protected:
  FrameBuilderInterfaceTest()
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
    BaseFrameBuilder *builder_;
    FrameBuilder frame_builder_;
    SubFrameBuilder sub_frame_builder_;
    QByteArray buffer_;
    QDataStream os_;
    QDataStream is_;
};

TEST_F(FrameBuilderInterfaceTest, BuildFrameFromInterface) {
  os_ << 0x01234567 << 0x4 << 0x01020304;
  builder_ = &frame_builder_;
  auto actual = builder_->Build(is_, 12);
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}
}  // namespace frame_builder_interface_test