#include <gtest/gtest.h>
#include "FrameBuilder.h"

namespace udp_packet_test {
  using udp_reciever::FrameBuilder;
  using udp_reciever::Frame;
  using udp_reciever::FrameBuilderStatus;

  class FrameTest : public ::testing::Test {
  protected:
    FrameTest()
      : os(&buffer, QIODevice::WriteOnly), is(&buffer, QIODevice::ReadOnly)
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    protected:
      FrameBuilder builder;
      QByteArray buffer;
      QDataStream os;
      QDataStream is;
  };

  TEST_F(FrameTest, TestQByteStream)
  {
    os << Frame::kHeaderMagic << 0x4 << 0x01020304;

    quint32 header;
    qint32 payloadSize;

    is >> header;
    is >> payloadSize;
    auto buf = new char[payloadSize];
    is.readRawData(buf, payloadSize);
    EXPECT_EQ(0x01, buf[0]);
    delete[] buf;

    auto expect = Frame::kHeaderMagic;
    EXPECT_EQ(expect, header);
    EXPECT_EQ(4, payloadSize);
  }

  TEST_F(FrameTest, GetInstanceByQDataStream)
  {
    os << Frame::kHeaderMagic << 0x4 << 0x01020304;
    auto data = builder.build(is);
    auto expect = Frame::kHeaderMagic;
    EXPECT_EQ(expect, data.getHeader());
    EXPECT_EQ(4, data.getPayloadSize());
    EXPECT_EQ(4, data.getPayload().size());
  }

  TEST_F(FrameTest, isReadyToBuild)
  {
    os << Frame::kHeaderMagic << (qint32)0 << (quint32)0;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::READY, result);
  }

  TEST_F(FrameTest, HeaderIsStillImcomplete)
  {
    os << (quint16)0x0123; // imcomplete header
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::RETRY, result);
  }

  TEST_F(FrameTest, PayloadSizeIsStillImcomplete)
  {
    os << Frame::kHeaderMagic << (qint16)0; // imcomplete payloadSize
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::RETRY, result);
  }

  TEST_F(FrameTest, PayloadIsStillImcomplete)
  {
    os << Frame::kHeaderMagic << (qint32)4 << (quint16)0x0102; // imcomplete payload
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::RETRY, result);
  }

  TEST_F(FrameTest, InvalidHeader)
  {
    os << (quint32)0x76543210 << (qint32)4 << (quint32)0x01020304;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::INVALID, result);
  }

  TEST_F(FrameTest, CanCreateTwoFrame)
  {
    os << Frame::kHeaderMagic << (qint32)4 << (quint32)0x01020304
       << Frame::kHeaderMagic << (qint32)4 << (quint32)0x01020304;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(FrameBuilderStatus::READY, result);

    result = builder.isReadyToBuild(is, buffer.size()-12);
    EXPECT_EQ(FrameBuilderStatus::READY, result);
  }
}