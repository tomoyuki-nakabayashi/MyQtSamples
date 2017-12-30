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
      udpReciever = new UdpReciever();
    }

    virtual void TearDown()
    {
      delete udpReciever;
    }
    protected:
      UdpReciever *udpReciever;
  };

  TEST_F(UdpRecieverTest, InitScoketSuccess)
  {
    EXPECT_TRUE(udpReciever->initSocket());
  }

  TEST_F(UdpRecieverTest, SendDatagram)
  {
    udpReciever->initSocket();
    auto socket = new QUdpSocket();
    QByteArray datagram = "message";
    socket->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress::LocalHost, 45454);

    delete socket;
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

    EXPECT_TRUE(spy.wait(1000));
    EXPECT_EQ(1, spy.count());
  }
}