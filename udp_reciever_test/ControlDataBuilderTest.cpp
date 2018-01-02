#include <gtest/gtest.h>
#include <QSignalSpy>
#include "ControlDataBuilder.h"

namespace udp_packet_test {
  using udp_reciever::ControlDataBuilder;
  using udp_reciever::ControlData;

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

  TEST_F(ControlDataTest, GetInstanceByQDataStream)
  {
    const quint32 expectedHeader = 0x01234567;
    os << expectedHeader << 0x4 << 0x01020304;
    auto data = builder.build(is);
    EXPECT_EQ(expectedHeader, data.header);
  }

  TEST_F(ControlDataTest, isReadyToBuild)
  {
    os << (quint32)0x0 << (qint32)0 << (quint32)0;
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_TRUE(result);
  }

  TEST_F(ControlDataTest, HeaderIsStillImcomplete)
  {
    os << (quint16)0x0123; // imcomplete header
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_FALSE(result);
  }

  TEST_F(ControlDataTest, PayloadSizeIsStillImcomplete)
  {
    os << (quint32)0x01234567 << (qint16)0; // imcomplete payloadSize
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_FALSE(result);
  }

  TEST_F(ControlDataTest, PayloadIsStillImcomplete)
  {
    os << (quint32)0x01234567 << (qint32)4 << (quint16)0x0102; // imcomplete payload
    auto result = builder.isReadyToBuild(is, buffer.size());
    EXPECT_FALSE(result);
  }
}