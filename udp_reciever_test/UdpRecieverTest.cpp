#include <gtest/gtest.h>
#include <QtNetwork>
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
    QUdpSocket *socket = new QUdpSocket();
    QByteArray datagram = "message";
    socket->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress::LocalHost, 45454);

    delete socket;
  }

}