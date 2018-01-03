#include <gtest/gtest.h>
#include <QObject>
#include <QtNetwork>
#include <QTest>
#include <QSignalSpy>
#include "UdpReciever.h"
#include "ControlDataBuilder.h"

namespace udp_reciever_test {
  using udp_reciever::UdpReciever;
  using udp_reciever::ControlData;

  class UdpRecieverInitTest : public ::testing::Test {
  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    protected:
      UdpReciever udpReciever;
  };

  TEST_F(UdpRecieverInitTest, InitScoket)
  {
    EXPECT_TRUE(udpReciever.initSocket(QHostAddress::LocalHost, 45454));
    EXPECT_DEATH(udpReciever.initSocket(QHostAddress("1.1.1.1"), 0), "");
  }

  TEST_F(UdpRecieverInitTest, SocketReadReady)
  {
    QUdpSocket reciever;
    reciever.bind(QHostAddress::LocalHost, 45454);
    QSignalSpy spy(&reciever, SIGNAL(readyRead()));

    QUdpSocket sender;
    QByteArray datagram = "message";
    sender.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    EXPECT_TRUE(spy.wait(33));
    EXPECT_EQ(1, spy.count());
  }

  class UdpRecieverTest : public ::testing::Test {
  protected:
    UdpRecieverTest(): ds(&datagram, QIODevice::WriteOnly) {}

    virtual void SetUp()
    {
      udpReciever.initSocket(QHostAddress::LocalHost, 45454);
    }

    virtual void TearDown()
    {
    }
    protected:
      UdpReciever udpReciever;
      QByteArray datagram;
      QDataStream ds;
      QUdpSocket socket;
  };

  TEST_F(UdpRecieverTest, ControlDataRecieved)
  {
    ControlData *p = nullptr;
    QObject::connect(&udpReciever, &UdpReciever::dataRecieved,
      [&](const ControlData &data){p = new ControlData(data);});
    ds << ControlData::kHeaderMagic << 0x4 << 0x01020304;
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(10);
    ASSERT_TRUE(p != nullptr);
    auto expect = ControlData::kHeaderMagic;
    EXPECT_EQ(expect, p->getHeader());
    EXPECT_EQ(4, p->getPayloadSize());

    delete p;
  }

  TEST_F(UdpRecieverTest, TwoControlDataRecieved)
  {
    ControlData *p = nullptr;
    qint32 count = 0;
    QObject::connect(&udpReciever, &UdpReciever::dataRecieved,
      [&](const ControlData &data){p = new ControlData(data); count++;});
    ds << ControlData::kHeaderMagic << 0x4 << 0x01020304
       << ControlData::kHeaderMagic << 0x4 << 0x01020304;
    EXPECT_EQ(24, datagram.size());
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(20);
    EXPECT_EQ(2, count);
    EXPECT_EQ(4, p->getPayload().size());
    delete p;
  }
}