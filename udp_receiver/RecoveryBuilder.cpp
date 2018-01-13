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

BuilderResult RecoveryBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  BuilderResult result;
  qint32 restart_point = ba.indexOf(QByteArray::fromHex("01234567"));
  if (restart_point == -1) {
    result.status = FrameBuilderStatus::RETRY;
    return result;
  }
  auto buff = ba.mid(restart_point);

  QDataStream ds(buff);
  ds >> *frame;
  result.parsed_bytes = restart_point + frame->GetFrameSize();
  return result;
}
}  // namespace udp_receiver