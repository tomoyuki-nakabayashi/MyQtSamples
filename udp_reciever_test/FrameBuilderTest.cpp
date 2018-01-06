#include <memory>
#include <gtest/gtest.h>
#include "FrameBuilder.h"

namespace udp_packet_test {
using udp_reciever::FrameBuilder;
using udp_reciever::Frame;
using udp_reciever::FrameBuilderStatus;

class FrameBuilderTest : public ::testing::Test {
protected:
  FrameBuilderTest()
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
    FrameBuilder builder_;
    QByteArray buffer_;
    QDataStream os_;
    QDataStream is_;
};

Frame* CreateExpectFrame(quint32 header, qint32 size, QByteArray payload) {
  return new Frame(header, size, payload);
}

TEST_F(FrameBuilderTest, TestQByteStream) {
  os_ << Frame::kHeaderMagic << 0x4 << 0x01020304;

  quint32 header;
  qint32 payload_size;

  is_ >> header;
  is_ >> payload_size;
  std::unique_ptr<char> buff(new char[payload_size]);
  is_.readRawData(buff.get(), payload_size);
  EXPECT_EQ(0x01, buff.get()[0]);

  auto expect = Frame::kHeaderMagic;
  EXPECT_EQ(expect, header);
  EXPECT_EQ(4, payload_size);
}

TEST_F(FrameBuilderTest, TestQByteStreamDoesNotHaveEnoughData) {
  os_ << 0x0123;

  quint32 header;
  is_ >> header;
  //is_ >> header >> test; // This makes stream error

  EXPECT_EQ(QDataStream::Ok, is_.status());
  EXPECT_EQ(0x0123, header);
}

TEST_F(FrameBuilderTest, GetInstanceByQDataStream) {
  os_ << Frame::kHeaderMagic << 0x4 << 0x01020304;
  auto actual = builder_.Build(is_, 12);
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}

TEST_F(FrameBuilderTest, CreateBuildAndGet) {
  os_ << Frame::kHeaderMagic << 0x4 << 0x01020304;
  builder_.Build(is_, 12);
  auto frame = builder_.GetFrame();

  auto expect = CreateExpectFrame(0x01234567, 4, QByteArray::fromHex("01020304"));
  EXPECT_EQ(*expect, *frame);
  EXPECT_EQ(12, frame->GetFrameSize());
}

TEST_F(FrameBuilderTest, IsReadyToBuild) {
  os_ << Frame::kHeaderMagic << (qint32)0 << (quint32)0;
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::READY, result);
}

TEST_F(FrameBuilderTest, HeaderIsStillImcomplete) {
  os_ << (quint16)0x0123; // imcomplete header
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::RETRY, result);
}

TEST_F(FrameBuilderTest, PayloadSizeIsStillImcomplete) {
  os_ << Frame::kHeaderMagic << (qint16)0; // imcomplete payloadSize
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::RETRY, result);
}

TEST_F(FrameBuilderTest, PayloadIsStillImcomplete) {
  os_ << Frame::kHeaderMagic << (qint32)4 << (quint16)0x0102; // imcomplete payload
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::RETRY, result);
}

TEST_F(FrameBuilderTest, InvalidHeader) {
  os_ << (quint32)0x76543210 << (qint32)4 << (quint32)0x01020304;
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::INVALID, result);
}

TEST_F(FrameBuilderTest, CanCreateTwoFrame) {
  os_ << Frame::kHeaderMagic << (qint32)4 << (quint32)0x01020304
      << Frame::kHeaderMagic << (qint32)4 << (quint32)0x01020304;
  auto result = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::READY, result);

  result = builder_.Build(is_, buffer_.size()-12);
  EXPECT_EQ(FrameBuilderStatus::READY, result);
}
}  // udp_packet_test