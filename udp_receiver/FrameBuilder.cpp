/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> FrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus FrameBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  QDataStream ds(ba);
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver