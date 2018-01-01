#include <gtest/gtest.h>
#include <QDataStream>
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
    protected:
      ControlData controlData;
  };

  TEST_F(ControlDataTest, TestQByteArray)
  {
    const char mydata[] = {
        0x01, 0x23, 0x45, 0x67, 0x00, 0x00, 0x00, 0x04,
        0x01, 0x02, 0x03, 0x04};
    QByteArray data = QByteArray::fromRawData(mydata, sizeof(mydata));

    QDataStream qDS(data);
    quint32 header; qDS >> header;
    quint32 size; qDS >> size;
    quint32 payload; qDS >> payload;
    
    EXPECT_EQ(0x01234567, header);
    EXPECT_EQ(4, size);
    EXPECT_EQ(0x01020304, payload);
  }
}