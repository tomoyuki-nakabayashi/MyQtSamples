#include <gtest/gtest.h>
#include <QObject>
#include <QtNetwork>
#include <QTest>
#include <QSignalSpy>
#include "UdpReciever.h"
#include "FrameBuilder.h"

udp_reciever::TestClass* udp_reciever::TestClass::self;

namespace udp_reciever_test {
  using udp_reciever::UdpReciever;
  using udp_reciever::Frame;

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
    EXPECT_TRUE(udpReciever.InitSocket(QHostAddress::LocalHost, 45454));
    EXPECT_DEATH(udpReciever.InitSocket(QHostAddress("1.1.1.1"), 0), "");
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
      udpReciever.InitSocket(QHostAddress::LocalHost, 45454);
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

  TEST_F(UdpRecieverTest, FrameRecieved)
  {
    QSharedPointer<Frame> p = nullptr;
    QObject::connect(&udpReciever, &UdpReciever::DataRecieved,
      [&](QSharedPointer<Frame> frame){p = frame;});
    ds << Frame::kHeaderMagic << 0x4 << 0x01020304;
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(10);
    ASSERT_TRUE(p != nullptr);
    auto expect = Frame::kHeaderMagic;
    EXPECT_EQ(expect, p->GetHeader());
    EXPECT_EQ(4, p->GetPayloadSize());
  }

  TEST_F(UdpRecieverTest, TwoFrameRecieved)
  {
    qint32 count = 0;
    QObject::connect(&udpReciever, &UdpReciever::DataRecieved,
      [&](QSharedPointer<Frame> frame){count++;});
    ds << Frame::kHeaderMagic << 0x4 << 0x01020304
       << Frame::kHeaderMagic << 0x4 << 0x01020304;
    EXPECT_EQ(24, datagram.size());
    socket.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(20);
    EXPECT_EQ(2, count);
  }

  using udp_reciever::TestClass;
  class TestClassTest : public ::testing::Test {
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
  };

  TEST_F(TestClassTest, GetInstance)
  {
    TestClass::self = new TestClass(4);
    auto instance = TestClass::GetInstance();
    EXPECT_EQ(4, instance->test);
  }
}