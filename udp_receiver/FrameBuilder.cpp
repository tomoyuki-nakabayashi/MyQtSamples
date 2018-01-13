/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> FrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus FrameBuilder::BuildImpl(QDataStream &ds, Frame *frame) {
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver