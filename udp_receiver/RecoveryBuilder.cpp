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
  QDataStream ds(ba);
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver