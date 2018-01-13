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

BuilderResult FrameBuilder::BuildImpl(QByteArray &ba, Frame *frame) {
  BuilderResult result;
  QDataStream ds(ba);
  ds >> *frame;

  result.status = frame->status;
  result.parsed_bytes = frame->GetFrameSize();
  return result;
}
}  // namespace udp_receiver