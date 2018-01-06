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

Frame* CreateExpectFrame(quint32 header, qint32 size, QByteArray payload) {
  return new Frame(header, size, payload);
}

TEST_F(SubFrameBuilderTest, FirstTest)
{
  EXPECT_TRUE(true);
}

TEST_F(SubFrameBuilderTest, GetInstanceByQDataStream) {
  os_ << 1 << 0x4 << 0x01020304;
  auto actual = builder_.Build(is_, 12);
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}

TEST_F(SubFrameBuilderTest, CreateBuildAndGet) {
  os_ << 1 << 0x2 << (quint16)0x0102;
  builder_.Build(is_, 10);
  auto frame = builder_.GetFrame();

  auto expect = CreateExpectFrame(1, 2, QByteArray::fromHex("0102"));
  EXPECT_EQ(*expect, *frame);
  EXPECT_EQ(10, frame->GetFrameSize());
}

}  // sub_data_builder_test