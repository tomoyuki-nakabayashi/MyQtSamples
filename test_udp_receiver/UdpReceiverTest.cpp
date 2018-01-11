/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include <QObject>
#include <QtNetwork>
#include <QTest>
#include <QSignalSpy>
#include <QVector>
#include "UdpReceiver.h"
#include "FrameBuilder.h"

namespace udp_receiver_test {
  using udp_receiver::UdpReceiver;
  using udp_receiver::Frame;

  class UdpReceiverInitTest : public ::testing::Test {
  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    protected:
      UdpReceiver udp_receiver_;
  };

  TEST_F(UdpReceiverInitTest, InitScoket)
  {
    EXPECT_TRUE(udp_receiver_.InitSocket(QHostAddress::LocalHost, 45454));
    EXPECT_DEATH(udp_receiver_.InitSocket(QHostAddress("1.1.1.1"), 0), "");
  }

  TEST_F(UdpReceiverInitTest, SocketReadReady)
  {
    QUdpSocket receiver;
    receiver.bind(QHostAddress::LocalHost, 45454);
    QSignalSpy spy(&receiver, SIGNAL(readyRead()));

    QUdpSocket sender;
    QByteArray datagram = "message";
    sender.writeDatagram(datagram.data(), datagram.size(),
                         QHostAddress::LocalHost, 45454);

    EXPECT_TRUE(spy.wait(33));
    EXPECT_EQ(1, spy.count());
  }

  class UdpReceiverTest : public ::testing::Test {
  protected:
    UdpReceiverTest(): ds_(&datagram_, QIODevice::WriteOnly) {}

    virtual void SetUp()
    {
      qRegisterMetaType<QSharedPointer<Frame>>();
      udp_receiver_.InitSocket(QHostAddress::LocalHost, 45454);
    }

    virtual void TearDown()
    {
    }
    protected:
      UdpReceiver udp_receiver_;
      QByteArray datagram_;
      QDataStream ds_;
      QUdpSocket socket_;
  };

  TEST_F(UdpReceiverTest, FrameRecieved) {
    QSharedPointer<Frame> p = nullptr;
    QObject::connect(&udp_receiver_, &UdpReceiver::DataRecieved,
      [&](QSharedPointer<Frame> frame){p = frame;});
    Frame expect(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
    ds_ << expect;
    socket_.writeDatagram(datagram_.data(), datagram_.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(10);
    ASSERT_TRUE(p != nullptr);
    EXPECT_EQ(expect, *p);
  }

  TEST_F(UdpReceiverTest, RecieveSubFrameAfterOneFrame) {
    QVector<QSharedPointer<Frame>> pframe;
    QObject::connect(&udp_receiver_, &UdpReceiver::DataRecieved,
      [&](QSharedPointer<Frame> frame){pframe.append(frame);});
    ds_ << Frame::kHeaderMagic << 0x4 << 0x01020304
        << 1 << 0x4 << 0x04030201;
    socket_.writeDatagram(datagram_.data(), datagram_.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(20);
    EXPECT_EQ(2, pframe.size());
    // must check the data
  }

  TEST_F(UdpReceiverTest, RecieveFrameAfterSubFrames) {
    QVector<QSharedPointer<Frame>> pframe;
    QObject::connect(&udp_receiver_, &UdpReceiver::DataRecieved,
      [&](QSharedPointer<Frame> frame){pframe.append(frame);});
    Frame frame(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304"));
    Frame subframe(1, 4, QByteArray::fromHex("01020304"));
    ds_ << frame << subframe << frame;
    socket_.writeDatagram(datagram_.data(), datagram_.size(),
                         QHostAddress::LocalHost, 45454);

    QTest::qWait(20);
    EXPECT_EQ(3, pframe.size());
  }
}