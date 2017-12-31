#include <gtest/gtest.h>
#include <QtNetwork>
#include <QSignalSpy>
#include "UdpReciever.h"

namespace udp_reciever_test {
  using namespace testing;
  using udp_reciever::UdpReciever;

  class UdpRecieverTest : public ::testing::Test {
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

  TEST_F(UdpRecieverTest, InitScoket)
  {
    EXPECT_TRUE(udpReciever.initSocket(QHostAddress::LocalHost, 45454));
    EXPECT_DEATH(udpReciever.initSocket(QHostAddress("1.1.1.1"), 0), "");
  }

  TEST_F(UdpRecieverTest, SendDatagram)
  {
    udpReciever.initSocket(QHostAddress::LocalHost, 45454);
    QUdpSocket socket;
    QByteArray datagram = "message";
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);
  }

  TEST_F(UdpRecieverTest, SocketReadReady)
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
}