/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "RecoveryBuilder.h"

namespace udp_receiver {
QVariant RecoveryBuilder::CreateNewFrame() {
  QVariant v = QVariant::fromValue(QSharedPointer<Frame>(new Frame()));
  return v;
}

FrameBuilderStatus RecoveryBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  BuilderResult result;
  qint32 begin = ba.indexOf(QByteArray::fromHex("01234567"));
  if (begin == -1) {
    result.status = FrameBuilderStatus::RETRY;
    return FrameBuilderStatus::RETRY;
  }
  auto buff = ba.mid(begin);

  QDataStream ds(buff);
  ds >> *frame;
  result.parsed_bytes = frame->GetFrameSize() + begin;
  frame->skipped = begin;
  return frame->status;
}
}  // namespace udp_receiver