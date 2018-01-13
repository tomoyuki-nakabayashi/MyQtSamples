/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "FrameBuilder.h"

namespace udp_receiver {
QVariant FrameBuilder::CreateNewFrame() {
  QVariant v = QVariant::fromValue(QSharedPointer<Frame>(new Frame()));
  return v;
}

FrameBuilderStatus FrameBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  QDataStream ds(ba);
  ds >> *frame;
  return frame->status;
}
}  // namespace udp_receiver