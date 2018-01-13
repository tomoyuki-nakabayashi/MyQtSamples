/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> SubFrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus SubFrameBuilder::BuildImpl(QDataStream &ds, Frame *frame) {
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver