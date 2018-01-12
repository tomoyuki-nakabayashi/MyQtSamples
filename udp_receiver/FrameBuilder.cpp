/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> FrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus FrameBuilder::BuildImpl(QDataStream &ds, QSharedPointer<Frame> frame) {
  ds >> *(frame.data());
  return frame->status;
}

QSharedPointer<Frame> FrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_receiver