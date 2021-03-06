/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include <QVector>
#include "Frame.h"
#include "FrameBuilder.h"

namespace udp_packet_test {
using udp_receiver::FrameBuilder;
using udp_receiver::Frame;
using udp_receiver::FrameBuilderStatus;

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

  EXPECT_EQ(expect.header, actual_header);
  EXPECT_EQ(expect.payload_size, actual_payload_size);
  EXPECT_STREQ(expect.payload.data(), buff.data());
}


TEST_F(FrameBuilderTest, TestReadRawData) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;

  QScopedPointer<char> buff(new char[14]);
  auto res = is_.readRawData(buff.data(), 14);
  EXPECT_EQ(12, res);
}

TEST_F(FrameBuilderTest, TestOperatorRead) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;

  Frame actual;
  is_ >> actual;

  EXPECT_EQ(expect, actual);
}

TEST_F(FrameBuilderTest, FrameIsReady) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect;
  auto actual = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, actual.status);
}

TEST_F(FrameBuilderTest, CreateBuildAndGet) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  QVariant v;
  QObject::connect(&builder_, &FrameBuilder::FrameConstructed,
    [&](QVariant frame){v = frame;});
  os_ << expect;
  builder_.Build(buffer_);
  auto actual = v.value<QSharedPointer<Frame>>().data();

  EXPECT_EQ(expect, *actual);
  EXPECT_EQ(expect.GetFrameSize(), actual->GetFrameSize());
}

TEST_F(FrameBuilderTest, HeaderIsStillImcomplete) {
  os_ << (quint16)0x0123; // imcomplete header
  auto result = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::RETRY, result.status);
}

TEST_F(FrameBuilderTest, PayloadSizeIsStillImcomplete) {
  os_ << Frame::kHeaderMagic << (qint16)0; // imcomplete payloadSize
  auto result = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::RETRY, result.status);
}

TEST_F(FrameBuilderTest, PayloadIsStillImcomplete) {
  os_ << Frame::kHeaderMagic << (qint32)4 << (quint16)0x0102; // imcomplete payload
  auto result = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::RETRY, result.status);
}

TEST_F(FrameBuilderTest, InvalidHeader) {
  os_ << (quint32)0x76543210 << (qint32)4 << (quint32)0x01020304;
  auto result = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::INVALID, result.status);
}

TEST_F(FrameBuilderTest, CanCreateTwoFrame) {
  Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
  os_ << expect << expect;

  auto result = builder_.Build(buffer_);
  EXPECT_EQ(FrameBuilderStatus::READY, result.status);
  buffer_.remove(0, result.parsed_bytes);
  EXPECT_EQ(FrameBuilderStatus::READY, builder_.Build(buffer_).status);
}

}  // udp_packet_test