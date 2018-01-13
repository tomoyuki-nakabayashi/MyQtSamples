/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "RecoveryBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> RecoveryBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus RecoveryBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  qint32 begin = ba.indexOf(QByteArray::fromHex("01234567"));
  if (begin == -1) return FrameBuilderStatus::RETRY;
  auto buff = ba.mid(begin);

  QDataStream ds(buff);
  ds >> *frame;
  frame->skipped = begin;
  return frame->status;
}
}  // namespace udp_receiver