#include <gtest/gtest.h>
#include <QSignalSpy>
#include "ControlData.h"

namespace udp_packet_test {
  using udp_reciever::ControlData;

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
    const char mydata[12] = {0x01, 0x23, 0x45, 0x67};
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));
    QDataStream qDS(datagram);
    quint32 actual; qDS >> actual;
    
    EXPECT_EQ(expect, actual);
  }

  TEST_F(ControlDataTest, GetInstanceByQByteArray)
  {
    quint32 expectedHeader = 0x01234567;
    const char mydata[12] = {
      0x01, 0x23, 0x45, 0x67, 0x00, 0x00, 0x00, 0x04,
      0x01, 0x02, 0x03, 0x04};
    QByteArray datagram = QByteArray::fromRawData(mydata, sizeof(mydata));

    ControlData cData(datagram);
    EXPECT_EQ(expectedHeader, cData.getHeader());
  }
}