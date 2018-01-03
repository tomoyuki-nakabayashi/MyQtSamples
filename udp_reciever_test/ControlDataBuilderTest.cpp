#include <gtest/gtest.h>
#include "ControlDataBuilder.h"

namespace udp_packet_test {
  using udp_reciever::ControlDataBuilder;
  using udp_reciever::ControlData;
  using udp_reciever::DataBuilderStatus;

  class ControlDataTest : public ::testing::Test {
  protected:
    ControlDataTest()
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
      ControlDataBuilder builder;
      QByteArray buffer;
      QDataStream os;
      QDataStream is;
  };

  TEST_F(ControlDataTest, TestQByteStream)
  {
    os << ControlData::kHeaderMagic << 0x4 << 0x01020304;

    quint32 header;
    qint32 payloadSize;

    is >> header;
    is >> payloadSize;
    auto buf = new char[payloadSize];
    is.readRawData(buf, payloadSize);
    EXPECT_EQ(0x01, buf[0]);
    delete[] buf;

    auto expect = ControlData::kHeaderMagic;
    EXPECT_EQ(expect, header);
    EXPECT_EQ(4, payloadSize);
  }

  TEST_F(ControlDataTest, GetInstanceByQDataStream)
  {
    os << ControlData::kHeaderMagic << 0x4 << 0x01020304;
    auto data = builder.build(is);
    auto expect = ControlData::kHeaderMagic;
    EXPECT_EQ(expect, data.getHeader());
    EXPECT_EQ(4, data.getPayloadSize());
    EXPECT_EQ(4, data.getPayload().size());
  }

  TEST_F(ControlDataTest, isReadyToBuild)
  {
    os << ControlData::kHeaderMagic << (qint32)0 << (quint32)0;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::READY, result);
  }

  TEST_F(ControlDataTest, HeaderIsStillImcomplete)
  {
    os << (quint16)0x0123; // imcomplete header
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::RETRY, result);
  }

  TEST_F(ControlDataTest, PayloadSizeIsStillImcomplete)
  {
    os << ControlData::kHeaderMagic << (qint16)0; // imcomplete payloadSize
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::RETRY, result);
  }

  TEST_F(ControlDataTest, PayloadIsStillImcomplete)
  {
    os << ControlData::kHeaderMagic << (qint32)4 << (quint16)0x0102; // imcomplete payload
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::RETRY, result);
  }

  TEST_F(ControlDataTest, InvalidHeader)
  {
    os << (quint32)0x76543210 << (qint32)4 << (quint32)0x01020304;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::INVALID, result);
  }

  TEST_F(ControlDataTest, CanCreateTwoControlData)
  {
    os << ControlData::kHeaderMagic << (qint32)4 << (quint32)0x01020304
       << ControlData::kHeaderMagic << (qint32)4 << (quint32)0x01020304;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_EQ(DataBuilderStatus::READY, result);

    result = builder.isReadyToBuild(is, buffer.size()-12);
    EXPECT_EQ(DataBuilderStatus::READY, result);
  }
}