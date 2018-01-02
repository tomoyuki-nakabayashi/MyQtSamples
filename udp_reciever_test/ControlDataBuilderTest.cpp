#include <gtest/gtest.h>
#include <QSignalSpy>
#include "ControlDataBuilder.h"

namespace udp_packet_test {
  using udp_reciever::ControlDataBuilder;
  using udp_reciever::ControlData;

  static const char mydata[12] = {
    0x01, 0x23, 0x45, 0x67, // header
    0x00, 0x00, 0x00, 0x04, // data length
    0x01, 0x02, 0x03, 0x04  // payload
  };
  class ControlDataTest : public ::testing::Test {
  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    protected:
      ControlDataBuilder builder;
  };

  TEST_F(ControlDataTest, TestQByteArray)
  {
    const quint32 expect = 0x01234567;
    const char mydata[4] = {0x01, 0x23, 0x45, 0x67};
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));
    QDataStream qDS(datagram);
    quint32 actual; qDS >> actual;
    
    EXPECT_EQ(expect, actual);
  }

  TEST_F(ControlDataTest, GetInstanceByQByteArray)
  {
    const quint32 expectedHeader = 0x01234567;
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));

    QDataStream ds(datagram);
    auto data = builder.build(ds);
    EXPECT_EQ(expectedHeader, data.header);
  }

  TEST_F(ControlDataTest, isReadyToBuild)
  {
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));
    QDataStream ds(datagram);
    auto result = builder.isReadyToBuild(ds, datagram.size());
    EXPECT_TRUE(result);
  }

  TEST_F(ControlDataTest, CannotBuildDueToLackingHeader)
  {
    const char lackdata[2] = {
      0x01, 0x23 // header
    };
    QByteArray datagram = QByteArray::fromRawData(lackdata, sizeof(lackdata));
    QDataStream ds(datagram);
    auto result = builder.isReadyToBuild(ds, datagram.size());
    EXPECT_FALSE(result);
  }

  TEST_F(ControlDataTest, CannotBuildDueToLackingDataSize)
  {
    const char lackdata[5] = {
      0x01, 0x23, 0x45, 0x67, // header
      0x00                    // data length
    };
    QByteArray datagram = QByteArray::fromRawData(lackdata, sizeof(lackdata));
    QDataStream ds(datagram);
    auto result = builder.isReadyToBuild(ds, datagram.size());
    EXPECT_FALSE(result);
  }
}