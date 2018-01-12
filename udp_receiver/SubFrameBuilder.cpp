/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_receiver {
QSharedPointer<Frame> SubFrameBuilder::CreateNewFrame() {
  return QSharedPointer<Frame>(new Frame());
}

FrameBuilderStatus SubFrameBuilder::BuildImpl(QDataStream &ds, QSharedPointer<Frame> frame) {
  ds >> *(frame.data());
  return frame_->status;
}

QSharedPointer<Frame> SubFrameBuilder::GetFrame() {
  return frame_;
}
}  // namespace udp_receiver