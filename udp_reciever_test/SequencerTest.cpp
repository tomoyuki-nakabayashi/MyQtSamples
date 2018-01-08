/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include <gtest/gtest.h>
#include <QObject>
#include <QVector>
#include "Sequencer.h"
#include "FrameBuilder.h"
#include "SubFrameBuilder.h"

namespace sequencer_test {
using udp_reciever::Sequencer;
using udp_reciever::BaseFrameBuilder;
using udp_reciever::FrameBuilder;
using udp_reciever::SubFrameBuilder;
using udp_reciever::Frame;

class SequencerTest : public ::testing::Test {
protected:
  SequencerTest()
    : ds_(&buffer_, QIODevice::WriteOnly),
      kFrame(Frame::kHeaderMagic, 4, QByteArray::fromHex("01020304")),
      kSubFrame(1, 4, QByteArray::fromHex("01020304")) {}
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
  protected:
    Sequencer seq_;
    QDataStream ds_;
    QByteArray buffer_;
    const Frame kFrame, kSubFrame;
};

TEST_F(SequencerTest, AppendDatagram) {
  QByteArray x("free");
  QByteArray y("dom");

  seq_.AppendPendingData(x);
  auto res = seq_.AppendPendingData(y);

  EXPECT_EQ(QByteArray("freedom"), res);
  EXPECT_EQ(7, res.size());
}

TEST_F(SequencerTest, FrameConstructed) {
  QSharedPointer<Frame> p = nullptr;
  QObject::connect(&seq_, &Sequencer::FrameConstructed,
    [&](QSharedPointer<Frame> frame){p = frame;});
  ds_ << kFrame;
  
  seq_.AppendPendingData(buffer_);
  seq_.ConstructFrame();

  ASSERT_TRUE(p != nullptr);
  EXPECT_EQ(kFrame, *p);
  auto res = seq_.AppendPendingData(QByteArray());
  EXPECT_EQ(0, res.size());
}

TEST_F(SequencerTest, RecieveFrameAfterSubFrames) {
  QVector<QSharedPointer<Frame>> pframe;
  QObject::connect(&seq_, &Sequencer::FrameConstructed,
    [&](QSharedPointer<Frame> frame){pframe.append(frame);});
  ds_ << kFrame << kSubFrame << kFrame;

  seq_.AppendPendingData(buffer_);
  seq_.ConstructFrame();

  EXPECT_EQ(3, pframe.size());
}
}  // namespace sequencer_test