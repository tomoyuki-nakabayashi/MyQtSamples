/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> SubFrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus SubFrameBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  QDataStream ds(ba);
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver