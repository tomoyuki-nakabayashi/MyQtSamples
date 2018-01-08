/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

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
    qRegisterMetaType<QSharedPointer<Frame>>();
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

TEST_F(FrameBuilderTest, TestQByteStream) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;

  quint32 actual_header;
  is_ >> actual_header;
  qint32 actual_payload_size;
  is_ >> actual_payload_size;
  
  QScopedPointer<char> buff(new char[actual_payload_size]);
  is_.readRawData(buff.data(), actual_payload_size);

  EXPECT_EQ(expect.GetHeader(), actual_header);
  EXPECT_EQ(expect.GetPayloadSize(), actual_payload_size);
  EXPECT_STREQ(expect.GetPayload().data(), buff.data());
}

TEST_F(FrameBuilderTest, FrameIsReady) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;
  auto actual = builder_.Build(is_, buffer_.size());
  EXPECT_EQ(FrameBuilderStatus::READY, actual);
}

TEST_F(FrameBuilderTest, CreateBuildAndGet) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;
  builder_.Build(is_, buffer_.size());
  auto actual = builder_.GetFrame();

  EXPECT_EQ(expect, *actual);
  EXPECT_EQ(expect.GetFrameSize(), actual->GetFrameSize());
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
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect << expect;

  auto remaining_data = buffer_.size();
  EXPECT_EQ(FrameBuilderStatus::READY, builder_.Build(is_, remaining_data));
  auto actual = builder_.GetFrame();
  EXPECT_EQ(expect, *actual);

  remaining_data -= actual->GetFrameSize();
  EXPECT_EQ(FrameBuilderStatus::READY, builder_.Build(is_, remaining_data));
  actual = builder_.GetFrame();
  EXPECT_EQ(expect, *actual);
}
}  // udp_packet_test