/**
 * Copyright <2017> <Tomoyuki Nakabayashi>
 * This software is released under the MIT License, see LICENSE.
 */

#include "SubFrameBuilder.h"

namespace udp_receiver {
QVariant SubFrameBuilder::CreateNewFrame() {
  QVariant v = QVariant::fromValue(QSharedPointer<Frame>(new Frame()));
  return v;
}

BuilderResult SubFrameBuilder::BuildImpl(QByteArray &ba, QVariant frame_ptr) {
  auto frame = frame_ptr.value<QSharedPointer<Frame>>();
  BuilderResult result;
  QDataStream ds(ba);
  ds >> *frame;

  result.status = frame->status;
  result.parsed_bytes = frame->GetFrameSize();
  return result;
}
}  // namespace udp_receiver