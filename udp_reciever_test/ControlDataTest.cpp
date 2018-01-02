#include <gtest/gtest.h>
#include <QSignalSpy>
#include "ControlData.h"

namespace udp_packet_test {
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

    ControlData cData(datagram);
    EXPECT_EQ(expectedHeader, cData.getHeader());
  }

  TEST_F(ControlDataTest, canBuildControlData)
  {
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));
    QDataStream ds(datagram);
    auto result = ControlData::canBuildControlData(ds, datagram.size());
    EXPECT_TRUE(result);
  }

  TEST_F(ControlDataTest, cannotBuildControlData)
  {
    const char lackdata[2] = {
      0x01, 0x23 // header
    };
    QByteArray datagram = QByteArray::fromRawData(lackdata, sizeof(lackdata));
    QDataStream ds(datagram);
    auto result = ControlData::canBuildControlData(ds, datagram.size());
    EXPECT_FALSE(result);
  }
}