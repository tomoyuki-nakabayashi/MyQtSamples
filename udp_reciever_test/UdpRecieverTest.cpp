#include <gtest/gtest.h>
#include <QtNetwork>
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
      qRegisterMetaType<ControlData*>();
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
    QSignalSpy spy(&udpReciever, SIGNAL(DataRecieved(ControlData*)));
    ds << ControlData::kHeaderMagic << 0x4 << 0x01020304;
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    EXPECT_TRUE(spy.wait(33));
    EXPECT_EQ(1, spy.count());

    EXPECT_TRUE(spy.at(0).at(0).canConvert<ControlData*>());
    //ControlData result = qvariant_cast<ControlData>(spy.at(0).at(0));
    //auto expect = ControlData::kHeaderMagic;
    //EXPECT_EQ(expect, result.GetHeader());
  }

  TEST_F(UdpRecieverTest, DISABLED_TwoControlDataRecieved)
  {
    QSignalSpy spy(&udpReciever, SIGNAL(DataRecieved(ControlData&)));
    ds << ControlData::kHeaderMagic << 0x4 << 0x01020304
       << ControlData::kHeaderMagic << 0x4 << 0x01020304;
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    EXPECT_TRUE(spy.wait(33));
    EXPECT_EQ(2, spy.count());
  }
}